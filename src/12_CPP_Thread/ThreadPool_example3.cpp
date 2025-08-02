#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace ThreadPool {
class ThreadPool {
private:
    size_t num_threads_;
    std::vector<std::thread> worker_threads_;
    std::queue<std::function<void()>> jobs_;
    bool stop_all;
    void WorkerThread();
    std::condition_variable cv_job_q_;
    std::mutex m_job_q_;

public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    
    template <class F, class... Args>
    std::future<typename std::invoke_result_t<F, Args...>> EnqueueJob(F&& f, Args&&... args);
};

ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false) {
    worker_threads_.reserve(num_threads_);
    for (size_t i = 0; i < num_threads_; ++i) {
        worker_threads_.emplace_back([this](){ this->WorkerThread(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(m_job_q_);
        stop_all = true;
    }
    
    cv_job_q_.notify_all();
    
    for (auto& t : worker_threads_) {
        t.join();
    }
}

void ThreadPool::WorkerThread() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_job_q_);
        cv_job_q_.wait(lock, [this](){ return !jobs_.empty() || stop_all; });

        if (stop_all && jobs_.empty()) return;

        std::function<void()> job = std::move(jobs_.front());
        jobs_.pop();
        lock.unlock();

        job();
    }
}

template <class F, class... Args>
std::future<typename std::invoke_result_t<F, Args...>> ThreadPool::EnqueueJob(F&& f, Args&&... args) {
    if (stop_all) throw std::runtime_error("ThreadPool 사용 중지됨");
    using return_type = typename std::invoke_result_t<F, Args...>;
    auto job = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> job_result_future = job->get_future();

    {
        std::lock_guard<std::mutex> lock(m_job_q_);
        jobs_.push([job](){ (*job)(); });
    }
    cv_job_q_.notify_one();

    return job_result_future;
}
}   // namespace ThreadPool

int work(int t, int id) {
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);

    return t + id;
}

int main() {
    ThreadPool::ThreadPool pool(3);
    std::vector<std::future<int>> futures;
    
    for (int i = 0; i < 10; ++i) {
        futures.emplace_back(pool.EnqueueJob(work, i % 3 + 1, i));
    }

    for (auto& f : futures) {
        printf("result : %d \n", f.get());
    }
    
    return 0;
}
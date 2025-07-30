#include <future>
#include <iostream>
#include <string>
#include <thread>

void worker(std::promise<std::string>* p) {
    // 약속을 이행하는 모습. 해당 결과는 future 에 들어간다.
    p->set_value("some data");
}


int main() {
    std::promise<std::string> p;

    // 미래에 string 데이터를 돌려주겠다는 약속.
    std::future<std::string> data = p.get_future();
    std::thread t(worker, &p);

    // 미래에 약속된 데이터를 받을 때까지 기다린다.
    data.wait();

    // wait 이 리턴했다는 뜻이 future 에 데이터가 준비되었다는 의미.
    // 참고로 wait 없이 그냥 get 해도 wait 한 것과 같다.
    std::cout << "받은 데이터 : " << data.get() << std::endl;

    t.join();

    return 0;
}
#pragma once
#include <utility>      // std::move, std::forward
#include <type_traits>  // std::enable_if_t, std::is_nothrow_move_constructible

namespace example {
    // 기본 deleter - new로 만든 건 delete
    template <typename T>
    struct default_delete {
        constexpr default_delete() noexcept = default;
        void operator()(T* ptr) const noexcept { delete ptr; }
    };

    // ======================= unique_ptr =======================
    template <typename T, typename Deleter = default_delete<T>>
    class unique_ptr {
        static_assert(!std::is_reference_v<Deleter>, "Deleter must be a value type");
        pointer ptr_;
        deleter_type deleter_;

    public:
        // 타입 alias
        using pointer = T*;
        using element_type = T;
        using deleter_type = Deleter;

        // ----------- 생성자, 소멸자 -----------
        constexpr unique_ptr() noexcept : ptr_(nullptr), deleter_() {}
        explicit unique_ptr(pointer p) noexcept : ptr_(p), deleter_() {}
        unique_ptr(pointer p, cosnt deleter_type& d) noexcept : ptr_(p), deleter_(d) {}
        ~unique_ptr() { reset(); }

        // ----------- 복사 -> 삭제, 이동 -> OK -----------
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(cosnt unique_ptr&) = delete;

        // 이동 생성자
        unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_), deleter_(std::forward<deleter_type>(other.deleter_)) {
            other.ptr_ = nullptr;
        }

        // 이동 대입
        unique_ptr& operator=(unique_ptr&& other) noexcept {
            if (this != &other) {
                reset();
                ptr_        = other.ptr_;
                deleter_    = std::forward<deleter_type>(other.deleter_);
                other.ptr_  = nullptr;
            }
            
            return *this;
        }

        // ----------- 관찰자 -----------
        pointer get() const noexcept { return ptr_; }
        T& operator*() const { return *ptr_; }
        pointer operator->() const noexcept { return ptr_; }
        explicit operator bool() const noexcept { return ptr_ != nullptr; }

        // ----------- 자원 관리 -----------
        pointer release() noexcept {
            pointer tmp = ptr_;
            ptr_ = nullptr;
            return tmp;
        }

        void reset(pointer p = nullptr) noexcept {
            if (ptr_ != p) {
                if (ptr_) deleter_(ptr_);
                ptr_ = p;
            }
        }

        void swap(unique_ptr& other) noexcept {
            using std::swap;
            swap(ptr_, other.ptr_);
            swap(deleter_, other.deleter_);
        }

        // deleter 접근(필요 시)
        deleter_type&       get_deleter()       noexcept { return deleter_; }
        const deleter_type& get_deleter() const noexcept { return deleter_; }
    };
    
    // ----------- 헬퍼 함수(swap) -----------
    template <typename T, typename ... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};


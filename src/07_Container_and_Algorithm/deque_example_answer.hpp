#pragma once                       // 헤더 다중 포함(Include Guard) 방지

// ───────── 메타 정보 블록 ─────────────────────────────────────
// 학습용 deque: std::deque 없이 원형 버퍼로 직접 구현
// push/pop front/back  O(1)
// random access        O(1)
// 예외 안전: 기본 보장, reallocation 시 strong 보장
// production 품질 X  – iterator 무효화·스레드 안전 등 미구현
// ────────────────────────────────────────────────────────────

// 표준 헤더
#include <memory>      // std::allocator, allocator_traits
#include <iterator>    // iterator 태그
#include <stdexcept>   // 예외(out_of_range)
#include <utility>     // std::move, forward
#include <cstddef>     // size_t, ptrdiff_t
#include <type_traits> // move_if_noexcept 판단용

namespace example {    // 모든 코드를 example 네임스페이스로 래핑

// ───────────────────────── iterator 정의 ─────────────────────

// 커스텀 이터레이터: 컨테이너 내부 구조 몰라도 인덱스로 접근 가능
template <typename Deque, typename TPtr, typename TRef>
class deque_iterator {
public:
    using iterator_category = std::random_access_iterator_tag; // ← <algorithm> 전부 사용 가능
    using value_type        = typename Deque::value_type;      // 컨테이너와 동일
    using difference_type   = std::ptrdiff_t;                  // 거리 계산용 부호형 정수
    using pointer           = TPtr;                            // 포인터 타입(가변/상수)
    using reference         = TRef;                            // 참조 타입(가변/상수)

    deque_iterator() = default;                                // 기본 생성자
    deque_iterator(const Deque* d, std::size_t pos)            // 컨테이너+인덱스 보관
        : dq_(d), idx_(pos) {}

    // 간단한 역참조 연산들
    reference operator*()  const { return (*dq_)[idx_]; }
    pointer   operator->() const { return &(*dq_)[idx_]; }

    // 전위/후위 ++, -- (idx_만 이동)
    deque_iterator& operator++()    { ++idx_; return *this; }
    deque_iterator  operator++(int) { auto tmp = *this; ++*this; return tmp; }
    deque_iterator& operator--()    { --idx_; return *this; }
    deque_iterator  operator--(int) { auto tmp = *this; --*this; return tmp; }

    // 산술 복합 대입
    deque_iterator& operator+=(difference_type n) { idx_ += n; return *this; }
    deque_iterator& operator-=(difference_type n) { idx_ -= n; return *this; }

    // +, - 연산자 (비멤버 friend로 정의)
    friend deque_iterator operator+(deque_iterator it, difference_type n)
        { it += n; return it; }
    friend deque_iterator operator+(difference_type n, deque_iterator it)
        { return it + n; }
    friend deque_iterator operator-(deque_iterator it, difference_type n)
        { it -= n; return it; }
    friend difference_type operator-(deque_iterator a, deque_iterator b)
        { return static_cast<difference_type>(a.idx_) - b.idx_; }

    // 랜덤 접근 인덱싱
    reference operator[](difference_type n) const { return (*dq_)[idx_ + n]; }

    // 비교 연산 (동일 컨테이너 & 인덱스 비교)
    friend bool operator==(deque_iterator a, deque_iterator b)
        { return a.dq_ == b.dq_ && a.idx_ == b.idx_; }
    friend bool operator!=(deque_iterator a, deque_iterator b)
        { return !(a == b); }
    friend bool operator< (deque_iterator a, deque_iterator b)
        { return a.idx_ < b.idx_; }
    friend bool operator> (deque_iterator a, deque_iterator b) { return b < a; }
    friend bool operator<=(deque_iterator a, deque_iterator b) { return !(b < a); }
    friend bool operator>=(deque_iterator a, deque_iterator b) { return !(a < b); }

private:
    const Deque*   dq_  = nullptr; // 대상 simple_deque 객체 주소 (const 여야 상수 iterator 공유)
    std::size_t    idx_ = 0;       // “논리적” 인덱스 (0 ~ size_-1)
};

// ──────────────────────── 컨테이너 본체 ───────────────────────

template <typename T, typename Alloc = std::allocator<T>>
class simple_deque {
public:
    // 타입 별칭 – STL 컨테이너와 동일한 인터페이스 맞추기
    using value_type      = T;
    using allocator_type  = Alloc;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename std::allocator_traits<Alloc>::pointer;
    using const_pointer   = typename std::allocator_traits<Alloc>::const_pointer;

    using iterator       = deque_iterator<simple_deque, pointer, reference>;
    using const_iterator = deque_iterator<const simple_deque, const_pointer, const_reference>;

    // ───────────── 생성/소멸/대입 ─────────────
    simple_deque() { allocate_buffer(8); }        // 기본 8칸 할당

    explicit simple_deque(size_type count, const T& value = T{})
        : simple_deque()                          // 위 기본 생성자 호출
    {
        while (size_ < count) push_back(value);   // 초기값 채우기
    }

    simple_deque(std::initializer_list<T> init) : simple_deque()
    { for (const auto& v : init) push_back(v); }  // {1,2,3} 형태 지원

    simple_deque(const simple_deque& other) : simple_deque()
    { for (auto& v : other) push_back(v); }       // 깊은 복사

    // 이동 생성자: 내부 포인터만 훔치고 다른 쪽은 초기화
    simple_deque(simple_deque&& other) noexcept
        : alloc_(std::move(other.alloc_)),
          buf_(other.buf_), cap_(other.cap_), head_(other.head_),
          tail_(other.tail_), size_(other.size_)
    { other.buf_ = nullptr; other.cap_ = other.head_ = other.tail_ = other.size_ = 0; }

    ~simple_deque() { destroy_buffer(); }         // 모든 요소 & 버퍼 해제

    // 복사·이동 대입을 한 번에 처리 (copy-swap idiom)
    simple_deque& operator=(simple_deque other) noexcept
    { swap(other); return *this; }

    void swap(simple_deque& other) noexcept        // 멤버 교환
    {
        using std::swap;
        swap(alloc_, other.alloc_);
        swap(buf_,   other.buf_);
        swap(cap_,   other.cap_);
        swap(head_,  other.head_);
        swap(tail_,  other.tail_);
        swap(size_,  other.size_);
    }

    // ──────────────── 원소 접근 ────────────────
    reference       front()       { range_check(); return buf_[head_]; }
    const_reference front() const { range_check(); return buf_[head_]; }

    reference       back()       { range_check(); return buf_[prev(tail_)]; }
    const_reference back() const { range_check(); return buf_[prev(tail_)]; }

    reference       operator[](size_type i)       { return buf_[physical(i)]; }
    const_reference operator[](size_type i) const { return buf_[physical(i)]; }

    reference       at(size_type i)       { bounds(i); return (*this)[i]; }
    const_reference at(size_type i) const { bounds(i); return (*this)[i]; }

    // ─────────────── 컨테이너 상태 ───────────────
    [[nodiscard]] bool      empty() const noexcept { return size_ == 0; }
    [[nodiscard]] size_type size()  const noexcept { return size_; }

    // ─────────────── 수정 연산(push/pop) ───────────────
    void push_back(const T& v)  { emplace_back(v); }
    void push_back(      T&& v) { emplace_back(std::move(v)); }

    template <typename... Args>
    reference emplace_back(Args&&... args)         // 우측 끝에 요소 생성
    {
        grow_if_full();                            // 공간 부족 시 확장
        std::allocator_traits<Alloc>::construct(
            alloc_, buf_ + tail_, std::forward<Args>(args)...);
        tail_ = next(tail_);
        ++size_;
        return back();
    }

    void push_front(const T& v)  { emplace_front(v); }
    void push_front(      T&& v) { emplace_front(std::move(v)); }

    template <typename... Args>
    reference emplace_front(Args&&... args)        // 좌측 끝에 요소 생성
    {
        grow_if_full();
        head_ = prev(head_);
        std::allocator_traits<Alloc>::construct(
            alloc_, buf_ + head_, std::forward<Args>(args)...);
        ++size_;
        return front();
    }

    void pop_back()                                // 우측 끝 제거
    {
        check_empty();
        tail_ = prev(tail_);
        destroy_element(tail_);
        --size_;
    }

    void pop_front()                               // 좌측 끝 제거
    {
        check_empty();
        destroy_element(head_);
        head_ = next(head_);
        --size_;
    }

    void clear() noexcept                          // 모든 요소 파괴
    {
        if (!buf_) return;
        for (size_type i = 0; i < size_; ++i) destroy_element(physical(i));
        head_ = tail_ = size_ = 0;
    }

    // ─────────────── 이터레이터 ───────────────
    iterator       begin()       noexcept { return iterator(this, 0); }
    const_iterator begin() const noexcept { return const_iterator(this, 0); }
    const_iterator cbegin()const noexcept { return begin(); }

    iterator       end()       noexcept { return iterator(this, size_); }
    const_iterator end() const noexcept { return const_iterator(this, size_); }
    const_iterator cend()const noexcept { return end(); }

private:
    // ─────────────── 내부 데이터 ───────────────
    Alloc       alloc_{};   // 사용자 정의 allocator 지원
    pointer     buf_   = nullptr;    // 실제 메모리(원형 배열)
    size_type   cap_   = 0;          // 배열 용량
    size_type   head_  = 0;          // 첫 요소 인덱스
    size_type   tail_  = 0;          // 마지막 다음 칸
    size_type   size_  = 0;          // 현재 요소 개수

    // ─────────────── 메모리 관리 ───────────────
    void allocate_buffer(size_type new_cap)
    { buf_ = std::allocator_traits<Alloc>::allocate(alloc_, new_cap); cap_ = new_cap; }

    void destroy_buffer()             // 전체 해제
    {
        if (!buf_) return;
        clear();                      // 요소 파괴
        std::allocator_traits<Alloc>::deallocate(alloc_, buf_, cap_);
        buf_ = nullptr; cap_ = 0;
    }

    // 공간 부족 시 두 배 확장
    void grow_if_full() { if (size_ == cap_) reserve(cap_ ? cap_ * 2 : 8); }

    void reserve(size_type new_cap)   // 새 용량으로 재할당+이동
    {
        if (new_cap <= cap_) return;
        pointer new_buf = std::allocator_traits<Alloc>::allocate(alloc_, new_cap);

        // 기존 요소 move/copy
        for (size_type i = 0; i < size_; ++i)
            std::allocator_traits<Alloc>::construct(
                alloc_, new_buf + i, std::move_if_noexcept((*this)[i]));

        // 원본 파괴 및 메모리 반납
        for (size_type i = 0; i < size_; ++i) destroy_element(physical(i));
        std::allocator_traits<Alloc>::deallocate(alloc_, buf_, cap_);

        // 새 버퍼로 전환
        buf_  = new_buf;
        cap_  = new_cap;
        head_ = 0;
        tail_ = size_;
    }

    // 개별 요소 파괴
    void destroy_element(size_type phys_idx)
    { std::allocator_traits<Alloc>::destroy(alloc_, buf_ + phys_idx); }

    // ─────────────── 인덱스 보조 ───────────────
    [[nodiscard]] size_type next(size_type i) const noexcept { return (i + 1) % cap_; }
    [[nodiscard]] size_type prev(size_type i) const noexcept { return (i + cap_ - 1) % cap_; }
    [[nodiscard]] size_type physical(size_type logical) const noexcept
    { return (head_ + logical) % cap_; }

    // ─────────────── 예외 체크 ───────────────
    void check_empty() const
    { if (empty()) throw std::out_of_range("simple_deque: empty"); }

    void range_check() const { check_empty(); }    // front/back 보호

    void bounds(size_type i) const                 // at()용 범위 체크
    { if (i >= size_) throw std::out_of_range("simple_deque: index out of range"); }
};

// ───────────────────────── 비멤버 swap ───────────────────────
template <typename T, typename Alloc>
void swap(simple_deque<T,Alloc>& a, simple_deque<T,Alloc>& b) noexcept
{ a.swap(b); }                     // Koenig lookup(ADL)용 오버로드

} // namespace example

#pragma once
// ────────────────────────────────────────────────────────────────
//  simple_deque  ─ 학습용 원형 버퍼 deque 구현
//  - std::deque 를 쓰지 않는다 (#include <deque> 없음!)
//  - push/pop front/back O(1)      (암시적 reallocation 제외)
//  - random access O(1)
//  - 예외 안전: 기본 보장 (strong 은 재할당 시 move / copy 로 달성)
//
//  ⚠️ production 용이 아니다! iterator invalidation, 스레드 안전,
//  복사/이동 예외 강도 등 세세한 부분은 std::deque 만큼 탄탄하지 않다.
// ────────────────────────────────────────────────────────────────

#include <memory>       // std::allocator
#include <iterator>     // std::random_access_iterator_tag
#include <stdexcept>    // std::out_of_range
#include <utility>      // std::move
#include <cstddef>      // std::size_t
#include <type_traits>  // std::is_nothrow_move_constructible

namespace example {
//─────────────────────────────────────────────────────────────
//                         iterator
//─────────────────────────────────────────────────────────────
template <typename Deque, typename TPtr, typename TRef>
class deque_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename Deque::value_type;
}


//─────────────────────────────────────────────────────────────
//                         simple_deque
//─────────────────────────────────────────────────────────────


//─────────────────────────────────────────────────────────────
//  non‑member swap
//─────────────────────────────────────────────────────────────


} // namespace example
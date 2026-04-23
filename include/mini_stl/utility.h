#pragma once

#include "type_traits.h"

namespace mini_stl {

template <typename T> struct is_lvalue_reference : false_type {};

template <typename T> struct is_lvalue_reference<T &> : true_type {};

template <typename T> constexpr remove_reference_t<T> &&move(T &&t) noexcept {
  return static_cast<remove_reference_t<T> &&>(t);
}

template <typename T> constexpr T &&forward(remove_reference_t<T> &t) noexcept {
  return static_cast<T &&>(t);
}

template <typename T>
constexpr T &&forward(remove_reference_t<T> &&t) noexcept {
  static_assert(!is_lvalue_reference<T>::value,
                "bad forward of rvlaue as lvalue");
  return static_cast<T &&>(t);
}

template <typename T> void swap(T &a, T &b) {
  T tmp = mini_stl::move(a);
  a = mini_stl::move(b);
  b = mini_stl::move(tmp);
}
} // namespace mini_stl

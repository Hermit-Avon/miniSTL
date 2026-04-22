// TODO: integral_constant, is_same, remove_reference, enable_if
#pragma once

namespace mini_stl {

// integral_constant
template <typename T, T v> struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant<T, v>;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

// is_same
using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <typename A, typename B> struct is_same : false_type {};

template <typename A> struct is_same<A, A> : true_type {};

template <typename A, typename B>
inline constexpr bool is_same_v = is_same<A, B>::value;

// remove_reference
template <typename T> struct remove_reference {
  using type = T;
};

template <typename T> struct remove_reference<T &> {
  using type = T;
};

template <typename T> struct remove_reference<T &&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

// enable_if
template <bool B, typename T = void> struct enable_if {};

template <typename T> struct enable_if<true, T> {
  using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

} // namespace mini_stl

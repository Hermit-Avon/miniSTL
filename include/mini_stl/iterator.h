#pragma once

#include <cstddef>

namespace mini_stl {
struct input_itertator_tag {};
struct output_iterrator_tag {};
struct forward_iterator_tag : input_itertator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = std::ptrdiff_t,
          typename Pointer = T *, typename Reference = T &>
struct iterator {
  using iterator_category = Category;
  using value_type = T;
  using difference_type = Distance;
  using pointer = Pointer;
  using reference = Reference;
};

template <typename Iter> struct iterator_traits {
  using iterator_category = typename Iter::iterator_category;
  using value_type = typename Iter::value_type;
  using difference_type = typename Iter::difference_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
};

template <typename T> struct iterator_traits<T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
};

template <typename T> struct iterator_traits<const T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = const T *;
  using reference = const T &;
};

} // namespace mini_stl

#include <gtest/gtest.h>

#include <mini_stl/iterator.h>
#include <mini_stl/type_traits.h>

namespace {
using DummyIter = mini_stl::iterator<mini_stl::forward_iterator_tag, int, long>;
}

using mini_stl::is_same_v;

TEST(IteratorTraits, CustomIterator) {
  static_assert(
      is_same_v<mini_stl::iterator_traits<DummyIter>::value_type, int>);
  static_assert(
      is_same_v<mini_stl::iterator_traits<DummyIter>::difference_type, long>);
  static_assert(
      is_same_v<mini_stl::iterator_traits<DummyIter>::iterator_category,
                mini_stl::forward_iterator_tag>);
  SUCCEED();
}

TEST(IteratorTraits, RawPointer) {
  static_assert(is_same_v<mini_stl::iterator_traits<int *>::value_type, int>);
  static_assert(is_same_v<mini_stl::iterator_traits<const int *>::reference,
                          const int &>);
  static_assert(is_same_v<mini_stl::iterator_traits<int *>::iterator_category,
                          mini_stl::random_access_iterator_tag>);
  SUCCEED();
}

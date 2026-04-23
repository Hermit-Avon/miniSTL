#include "mini_stl/utility.h"
#include <gtest/gtest.h>

using namespace mini_stl;

TEST(Utility, MoveForwardTypes) {
  int x = 1;
  static_assert(is_same_v<decltype(move(x)), int &&>);
  static_assert(is_same_v<decltype(forward<int &>(x)), int &>);
  static_assert(is_same_v<decltype(forward<int>(0)), int &&>);
}

TEST(Utility, SwapWorks) {
  int a = 10, b = 20;
  swap(a, b);
  EXPECT_EQ(a, 20);
  EXPECT_EQ(b, 10);
}

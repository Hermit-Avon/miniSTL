#include <gtest/gtest.h>
#include <limits>
#include <new>

#include "mini_stl/allocator.h"

namespace {
struct Counted {
  static int ctor;
  static int dtor;
  int v{0};

  explicit Counted(int x) : v(x) { ++ctor; }
  ~Counted() { ++dtor; }
};

int Counted::ctor = 0;
int Counted::dtor = 0;

void reset_counts() {
  Counted::ctor = 0;
  Counted::dtor = 0;
}
} // namespace

TEST(Allocator, AllocatorZeroReturnsNullptr) {
  mini_stl::allocator<int> alloc;
  int *p = alloc.allocate(0);
  EXPECT_EQ(p, nullptr);
}

TEST(Allocator, AllocateAndDeallocateIntArray) {
  mini_stl::allocator<int> alloc;
  int *p = alloc.allocate(4);
  ASSERT_NE(p, nullptr);

  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;

  EXPECT_EQ(p[2], 3);
  alloc.deallocate(p, 4);
}

TEST(Allocator, ConstructAndDestroySingleObject) {
  reset_counts();
  mini_stl::allocator<Counted> alloc;

  Counted *p = alloc.allocate(1);
  ASSERT_NE(p, nullptr);

  alloc.construct(p, 42);
  EXPECT_EQ(p->v, 42);
  EXPECT_EQ(Counted::ctor, 1);
  EXPECT_EQ(Counted::dtor, 0);

  alloc.destroy(p);
  EXPECT_EQ(Counted::dtor, 1);

  alloc.deallocate(p, 1);
}

TEST(Allocator, AllocateOverflowThrows) {
  mini_stl::allocator<int> alloc;
  using size_type = mini_stl::allocator<int>::size_type;

  const size_type too_big =
      std::numeric_limits<size_type>::max() / sizeof(int) + 1;

  EXPECT_THROW((void)alloc.allocate(too_big), std::bad_array_new_length);
}

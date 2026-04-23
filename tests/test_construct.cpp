#include <gtest/gtest.h>
#include <new>

#include "mini_stl/construct.h"

namespace {
struct Counted {
  static int ctor_count;
  static int dtor_count;
  int v{0};

  explicit Counted(int x) : v(x) { ++ctor_count; }
  ~Counted() { ++dtor_count; }
};

int Counted::ctor_count = 0;
int Counted::dtor_count = 0;

void reset_counts() {
  Counted::ctor_count = 0;
  Counted::dtor_count = 0;
}
} // namespace

TEST(ConstructDestroy, SingleObject) {
  reset_counts();

  void *raw = ::operator new(sizeof(Counted));
  auto *p = static_cast<Counted *>(raw);

  mini_stl::construct(p, 42);
  EXPECT_EQ(p->v, 42);
  EXPECT_EQ(Counted::ctor_count, 1);
  EXPECT_EQ(Counted::dtor_count, 0);

  mini_stl::destroy(p);
  EXPECT_EQ(Counted::dtor_count, 1);

  ::operator delete(raw);
}

TEST(ConstructDestroy, RangeDestroy) {
  reset_counts();

  constexpr int n = 3;
  void *raw = ::operator new(sizeof(Counted) * n);
  auto *p = static_cast<Counted *>(raw);

  for (int i = 0; i < n; i++) {
    mini_stl::construct(p + i, i + 1);
  }

  EXPECT_EQ(Counted::ctor_count, n);

  mini_stl::destroy(p, p + n);
  EXPECT_EQ(Counted::dtor_count, n);

  ::operator delete(raw);
}

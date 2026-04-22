#include <gtest/gtest.h>
#include <mini_stl/type_traits.h>

using namespace mini_stl;

//---------- 编译期验证 ----------
static_assert(integral_constant<int, 7>::value == 7);
static_assert(true_type::value);
static_assert(!false_type::value);

static_assert(is_same<int, int>::value);
static_assert(!is_same<int, long>::value);
static_assert(is_same_v<const int, const int>);
static_assert(!is_same_v<int, const int>);

static_assert(is_same_v<remove_reference<int>::type, int>);
static_assert(is_same_v<remove_reference<int &>::type, int>);
static_assert(is_same_v<remove_reference<int &&>::type, int>);

// enable_if: true 分支可用
static_assert(is_same_v<enable_if<true, int>::type, int>);

// ---------- 运行期验证（补充可读性） ----------
TEST(TypeTraits, BasicValues) {
  EXPECT_TRUE((is_same<int, int>::value));
  EXPECT_FALSE((is_same<int, long>::value));
  EXPECT_TRUE((is_same_v<remove_reference_t<int &>, int>));
}

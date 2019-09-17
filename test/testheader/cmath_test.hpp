#include "doctest/doctest.h"

#include <cmath>

#include "spook.hpp"

namespace spook_test::cmath {

  TEST_CASE("isinf test")
  {
    constexpr auto inf = std::numeric_limits<double>::infinity();

    CHECK_UNARY(spook::isinf(inf));
    CHECK_UNARY(spook::isinf(-inf));

    CHECK_UNARY_FALSE(spook::isinf(0.0));
    CHECK_UNARY_FALSE(spook::isinf((std::numeric_limits<double>::max)()));
    CHECK_UNARY_FALSE(spook::isinf(std::numeric_limits<double>::lowest()));
  }

  TEST_CASE("isnan test") 
  {
    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();

    constexpr auto b = spook::isnan(nan);
    static_assert(b == true);

    CHECK_UNARY(spook::isnan(nan));

    CHECK_UNARY_FALSE(spook::isnan(0.0));
    CHECK_UNARY_FALSE(spook::isnan((std::numeric_limits<double>::max)()));
    CHECK_UNARY_FALSE(spook::isnan(std::numeric_limits<double>::lowest()));
  }

  TEST_CASE("isfinite_test") 
  {
    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
    constexpr auto inf = std::numeric_limits<double>::infinity();

    constexpr auto b = spook::isfinite(nan);
    static_assert(b == false);

    CHECK_UNARY_FALSE(spook::isfinite(nan));
    CHECK_UNARY_FALSE(spook::isfinite(inf));
    CHECK_UNARY_FALSE(spook::isfinite(-inf));

    CHECK_UNARY(spook::isfinite(0.0));
    CHECK_UNARY(spook::isfinite(-0.0));
    CHECK_UNARY(spook::isfinite((std::numeric_limits<double>::max)()));
    CHECK_UNARY(spook::isfinite(std::numeric_limits<double>::lowest()));
  }

  TEST_CASE("isnormal_test") 
  {
    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
    constexpr auto inf = std::numeric_limits<double>::infinity();
    constexpr auto denorm = 0x1p-1033;

    constexpr bool b = spook::isnormal(denorm);
    static_assert(b == false);

    CHECK_UNARY_FALSE(spook::isnormal(nan));
    CHECK_UNARY_FALSE(spook::isnormal(inf));
    CHECK_UNARY_FALSE(spook::isnormal(-inf));
    CHECK_UNARY_FALSE(spook::isnormal(0.0));
    CHECK_UNARY_FALSE(spook::isnormal(-0.0));
    CHECK_UNARY_FALSE(spook::isnormal(denorm));
    CHECK_UNARY_FALSE(spook::isnormal(-denorm));

    CHECK_UNARY(spook::isnormal(1.0));
    CHECK_UNARY(spook::isnormal(-2.0));
    CHECK_UNARY(spook::isnormal((std::numeric_limits<double>::max)()));
    CHECK_UNARY(spook::isnormal(std::numeric_limits<double>::lowest()));
  }

  TEST_CASE("fabs_test") 
  {
    constexpr auto p_inf = std::numeric_limits<double>::infinity();

    CHECK_UNARY(p_inf == spook::fabs(-std::numeric_limits<double>::infinity()));
    CHECK_UNARY(p_inf == spook::fabs(std::numeric_limits<double>::infinity()));

    constexpr auto p_zero = +0.0;

    CHECK_UNARY(p_zero == spook::fabs(-0.0));
    CHECK_UNARY(p_zero == spook::fabs(+0.0));

    constexpr auto expect = 3.141;

    CHECK_UNARY(expect == spook::fabs(-3.141));
    CHECK_UNARY(expect == spook::fabs(+3.141));
  }

  TEST_CASE("abs_test")
  {
    constexpr auto ullmax = spook::abs((std::numeric_limits<std::size_t>::max)());

    CHECK_UNARY(0 == spook::abs(std::size_t(0)));
    CHECK_UNARY(ullmax == spook::abs(ullmax));

    CHECK_UNARY(0 == spook::abs(std::int64_t(0)));

    constexpr auto sllmin = (std::numeric_limits<std::int64_t>::min)() + 1;
    constexpr auto sllmax = (std::numeric_limits<std::int64_t>::max)();

    CHECK_UNARY(-sllmin == spook::abs(sllmin));
    CHECK_UNARY(sllmax == spook::abs(sllmax));
  }

  TEST_CASE("signbit_test")
  {
    CHECK_UNARY(spook::signbit(-1.0));
    CHECK_UNARY_FALSE(spook::signbit(1.0));

    constexpr auto inf = std::numeric_limits<double>::infinity();

    CHECK_UNARY(spook::signbit(-inf));
    CHECK_UNARY_FALSE(spook::signbit(inf));

    //未対応
    //CHECK_UNARY(spook::signbit(-0.0));
    //CHECK_UNARY_FALSE(spook::signbit(0.0));
    //constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
    //CHECK_UNARY(spook::signbit(-nan));
    //CHECK_UNARY_FALSE(spook::signbit(nan));
  }

  TEST_CASE("copysign_test")
  {

    CHECK_EQ(+2.0, spook::copysign(2.0, +2.0));
    CHECK_EQ(-2.0, spook::copysign(2.0, -2.0));

    CHECK_EQ(+2.0, spook::copysign(-2.0, +2.0));
    CHECK_EQ(-2.0, spook::copysign(-2.0, -2.0));

    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
    constexpr auto inf = std::numeric_limits<double>::infinity();

    //Assert::IsTrue (spook::signbit(spook::copysign(nan, -2.0)));
    //Assert::IsFalse(spook::signbit(spook::copysign(nan, +2.0)));
    CHECK_UNARY(std::signbit(spook::copysign(nan, -2.0)));
    CHECK_UNARY_FALSE(std::signbit(spook::copysign(nan, +2.0)));

    CHECK_EQ(+inf, spook::copysign(inf, +2.0));
    CHECK_EQ(-inf, spook::copysign(inf, -2.0));
  }

  TEST_CASE("ceil_test")
  {
    CHECK_UNARY(3.0 == spook::ceil(3.0));
    CHECK_UNARY(4.0 == spook::ceil(3.1));
    CHECK_UNARY(4.0 == spook::ceil(3.5));
    CHECK_UNARY(4.0 == spook::ceil(3.9));

    CHECK_UNARY(-3.0 == spook::ceil(-3.0));
    CHECK_UNARY(-3.0 == spook::ceil(-3.1));
    CHECK_UNARY(-3.0 == spook::ceil(-3.5));
    CHECK_UNARY(-3.0 == spook::ceil(-3.9));
  }

  TEST_CASE("floor_test")
  {
    CHECK_UNARY(3.0 == spook::floor(3.0));
    CHECK_UNARY(3.0 == spook::floor(3.1));
    CHECK_UNARY(3.0 == spook::floor(3.5));
    CHECK_UNARY(3.0 == spook::floor(3.9));

    CHECK_UNARY(-3.0 == spook::floor(-3.0));
    CHECK_UNARY(-4.0 == spook::floor(-3.1));
    CHECK_UNARY(-4.0 == spook::floor(-3.5));
    CHECK_UNARY(-4.0 == spook::floor(-3.9));
  }

  TEST_CASE("trunc_test")
  {
    CHECK_UNARY(3.0 == spook::trunc(3.0));
    CHECK_UNARY(3.0 == spook::trunc(3.1));
    CHECK_UNARY(3.0 == spook::trunc(3.5));
    CHECK_UNARY(3.0 == spook::trunc(3.9));

    CHECK_UNARY(-3.0 == spook::trunc(-3.0));
    CHECK_UNARY(-3.0 == spook::trunc(-3.1));
    CHECK_UNARY(-3.0 == spook::trunc(-3.5));
    CHECK_UNARY(-3.0 == spook::trunc(-3.9));
  }

  TEST_CASE("roud_to_nearest_test")
  {
    CHECK_UNARY(3.0 == spook::round_to_nearest(3.0));
    CHECK_UNARY(3.0 == spook::round_to_nearest(3.1));
    CHECK_UNARY(4.0 == spook::round_to_nearest(3.5));
    CHECK_UNARY(4.0 == spook::round_to_nearest(3.9));

    CHECK_UNARY(-3.0 == spook::round_to_nearest(-3.0));
    CHECK_UNARY(-3.0 == spook::round_to_nearest(-3.1));
    CHECK_UNARY(-4.0 == spook::round_to_nearest(-3.5));
    CHECK_UNARY(-4.0 == spook::round_to_nearest(-3.9));
  }

  TEST_CASE("remainder_test")
  {
    constexpr double eps = 1.0E-15;
    {
      auto expected = doctest::Approx(std::remainder(3.14, 3.0)).epsilon(eps);
      constexpr auto r = spook::remainder(3.14, 3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::remainder(5.0, 2.0)).epsilon(eps);
      constexpr auto r = spook::remainder(5.0, 2.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::remainder(6.0, 4.0)).epsilon(eps);
      constexpr auto r = spook::remainder(6.0, 4.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::remainder(6.3, 3.0)).epsilon(eps);
      constexpr auto r = spook::remainder(6.3, 3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::remainder(6.3, -3.0)).epsilon(eps);
      constexpr auto r = spook::remainder(6.3, -3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = std::remainder(-6.3, 3.0);
      constexpr auto r = spook::remainder(-6.3, 3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::remainder(6.3, 3.15)).epsilon(eps);
      constexpr auto r = spook::remainder(6.3, 3.15);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::remainder(6.0, 2.0)).epsilon(eps);
      constexpr auto r = spook::remainder(6.0, 2.0);
      CHECK_EQ(expected, r);
    }
  }
}
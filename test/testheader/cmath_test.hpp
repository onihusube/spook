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

  TEST_CASE("fmod_test"){
    constexpr double eps = 1.0E-15;
    {
      auto expected = doctest::Approx(std::fmod(3.14, 3.0)).epsilon(eps);
      constexpr auto r = spook::fmod(3.14, 3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(5.0, 2.0)).epsilon(eps);
      constexpr auto r = spook::fmod(5.0, 2.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(6.0, 4.0)).epsilon(eps);
      constexpr auto r = spook::fmod(6.0, 4.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(6.3, 3.0)).epsilon(eps);
      constexpr auto r = spook::fmod(6.3, 3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(6.3, -3.0)).epsilon(eps);
      constexpr auto r = spook::fmod(6.3, -3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(-6.3, 3.0)).epsilon(eps);
      constexpr auto r = spook::fmod(-6.3, 3.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(6.3, 3.15)).epsilon(eps);
      constexpr auto r = spook::fmod(6.3, 3.15);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::fmod(6.0, 2.0)).epsilon(eps);
      constexpr auto r = spook::fmod(6.0, 2.0);
      CHECK_EQ(expected, r);
    }
  }

  TEST_CASE("sin test") {
    using namespace spook::constant;
    constexpr double eps = 1.0E-15;

    {
      constexpr double coeff = 0.0;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 0.25;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 0.5;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 0.75;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.0;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.25;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.5;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.75;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 2.0;

      auto expected = std::sin(coeff * pi<>);
      constexpr auto calc = spook::sin(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }
  }

  TEST_CASE("cos test") {

    using namespace spook::constant;
    constexpr double eps = 1.0E-15;

    {
      constexpr double coeff = 0.0;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 0.25;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 0.5;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 0.75;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.0;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.25;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.5;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 1.75;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      constexpr double coeff = 2.0;

      auto expected = std::cos(coeff * pi<>);
      constexpr auto calc = spook::cos(coeff * pi<>);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }
  }

  TEST_CASE("atan test") {
    constexpr double eps = 1.0E-15;

    {
      auto expected = 4.0 * std::atan(1.0);
      constexpr auto pi = 4.0 * spook::atan(1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), pi);
    }

    {
      auto expected = std::atan(-1.0);
      constexpr auto calc = spook::atan(-1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(-0.75);
      constexpr auto calc = spook::atan(-0.75);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(-0.5);
      constexpr auto calc = spook::atan(-0.5);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(-0.25);
      constexpr auto calc = spook::atan(-0.25);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(0.0);
      constexpr auto calc = spook::atan(0.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(0.25);
      constexpr auto calc = spook::atan(0.25);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(0.5);
      constexpr auto calc = spook::atan(0.5);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(0.75);
      constexpr auto calc = spook::atan(0.75);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan(1.0);
      constexpr auto calc = spook::atan(1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }
  }

  TEST_CASE("atan2 test") {
    constexpr double eps = 1.0E-15;

    {
      auto expected = std::atan2(0.0, 1.0);
      constexpr auto calc = spook::atan2(0.0, 1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(1.0, 1.0);
      constexpr auto calc = spook::atan2(1.0, 1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(1.0, 0.0);
      constexpr auto calc = spook::atan2(1.0, 0.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(1.0, -1.0);
      constexpr auto calc = spook::atan2(1.0, -1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(0.0, -1.0);
      constexpr auto calc = spook::atan2(0.0, -1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(-1.0, -1.0);
      constexpr auto calc = spook::atan2(-1.0, -1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(-1.0, 0.0);
      constexpr auto calc = spook::atan2(-1.0, 0.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::atan2(-1.0, 1.0);
      constexpr auto calc = spook::atan2(-1.0, 1.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }
  }

  TEST_CASE("float pow test")
  {
    constexpr double eps = 1.0E-15;
    {
      auto expected = doctest::Approx(std::pow(2.0, 0.5)).epsilon(eps);
      constexpr auto r = spook::pow(2.0, 0.5);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(3.0, 0.5)).epsilon(eps);
      constexpr auto r = spook::pow(3.0, 0.5);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(2.0, 2.0)).epsilon(eps);
      constexpr auto r = spook::pow(2.0, 2.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(2.0, 0.0)).epsilon(eps);
      constexpr auto r = spook::pow(2.0, 0.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(2.0, -0.5)).epsilon(eps);
      constexpr auto r = spook::pow(2.0, -0.5);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(3.0, -0.5)).epsilon(eps);
      constexpr auto r = spook::pow(3.0, -0.5);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(2.0, -2.0)).epsilon(eps);
      constexpr auto r = spook::pow(2.0, -2.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(1000.0, -2.0)).epsilon(eps);
      constexpr auto r = spook::pow(1000.0, -2.0);
      CHECK_EQ(expected, r);
    }
    {
      auto expected = doctest::Approx(std::pow(1000.0, 2.0)).epsilon(1.0e-6);
      constexpr auto r = spook::pow(1000.0, 2.0);
      CHECK_EQ(expected, r);
    }
  }

  TEST_CASE("sqrt test") {
    constexpr double eps = 1.0E-15;
    
    {
      constexpr auto calc = spook::sqrt(-2.0);

      CHECK_UNARY(spook::isnan(calc));
    }

    {
      auto expected = std::sqrt(2.0);
      constexpr auto calc = spook::sqrt(2.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(3.0);
      constexpr auto calc = spook::sqrt(3.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(4.0);
      constexpr auto calc = spook::sqrt(4.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(8.0);
      constexpr auto calc = spook::sqrt(8.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(16.0);
      constexpr auto calc = spook::sqrt(16.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(32.0);
      constexpr auto calc = spook::sqrt(32.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(64.0);
      constexpr auto calc = spook::sqrt(64.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::sqrt(128.0);
      constexpr auto calc = spook::sqrt(128.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }

    {
      auto expected = std::sqrt(256.0);
      constexpr auto calc = spook::sqrt(256.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }

    {
      auto expected = std::sqrt(512.0);
      constexpr auto calc = spook::sqrt(512.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }

    {
      auto expected = std::sqrt(1024.0);
      constexpr auto calc = spook::sqrt(1024.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }
  }

  TEST_CASE("cbrt test") {
    constexpr double eps = 1.0E-15;

    {
      constexpr auto calc = spook::cbrt(-2.0);

      CHECK_UNARY(spook::isnan(calc));
    }

    {
      auto expected = std::cbrt(2.0);
      constexpr auto calc = spook::cbrt(2.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(3.0);
      constexpr auto calc = spook::cbrt(3.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(4.0);
      constexpr auto calc = spook::cbrt(4.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(8.0);
      constexpr auto calc = spook::cbrt(8.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(16.0);
      constexpr auto calc = spook::cbrt(16.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(32.0);
      constexpr auto calc = spook::cbrt(32.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(64.0);
      constexpr auto calc = spook::cbrt(64.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(eps), calc);
    }

    {
      auto expected = std::cbrt(128.0);
      constexpr auto calc = spook::cbrt(128.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }

    {
      auto expected = std::cbrt(256.0);
      constexpr auto calc = spook::cbrt(256.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }

    {
      auto expected = std::cbrt(512.0);
      constexpr auto calc = spook::cbrt(512.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }

    {
      auto expected = std::cbrt(1024.0);
      constexpr auto calc = spook::cbrt(1024.0);

      CHECK_EQ(doctest::Approx(expected).epsilon(1.0E-14), calc);
    }
  }

  TEST_CASE("lerp test") {
    constexpr double start = 0.0;
    constexpr double end = 10.0;
    constexpr double eps = 1.0E-14;

    CHECK_EQ(doctest::Approx(start), spook::lerp(start, end, 0.0));
    CHECK_EQ(doctest::Approx(1.0).epsilon(eps), spook::lerp(start, end, 0.1));
    CHECK_EQ(doctest::Approx(2.0).epsilon(eps), spook::lerp(start, end, 0.2));
    CHECK_EQ(doctest::Approx(3.0).epsilon(eps), spook::lerp(start, end, 0.3));
    CHECK_EQ(doctest::Approx(4.0).epsilon(eps), spook::lerp(start, end, 0.4));
    CHECK_EQ(doctest::Approx(5.0).epsilon(eps), spook::lerp(start, end, 0.5));
    CHECK_EQ(doctest::Approx(6.0).epsilon(eps), spook::lerp(start, end, 0.6));
    CHECK_EQ(doctest::Approx(7.0).epsilon(eps), spook::lerp(start, end, 0.7));
    CHECK_EQ(doctest::Approx(8.0).epsilon(eps), spook::lerp(start, end, 0.8));
    CHECK_EQ(doctest::Approx(9.0).epsilon(eps), spook::lerp(start, end, 0.9));
    CHECK_EQ(doctest::Approx(end), spook::lerp(start, end, 1.0));
    CHECK_EQ(doctest::Approx(15.0).epsilon(eps), spook::lerp(start, end, 1.5));
    CHECK_EQ(doctest::Approx(20.0).epsilon(eps), spook::lerp(start, end, 2.0));

    CHECK_EQ(doctest::Approx(end), spook::lerp(end, end, 2.0));
  }
}
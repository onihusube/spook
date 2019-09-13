#include "doctest/doctest.h"

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

  TEST_CASE("isnan test") {
    constexpr auto nan = std::numeric_limits<double>::quiet_NaN();

    constexpr auto b = spook::isnan(nan);
    static_assert(b == true);

    CHECK_UNARY(spook::isnan(nan));

    CHECK_UNARY_FALSE(spook::isnan(0.0));
    CHECK_UNARY_FALSE(spook::isnan((std::numeric_limits<double>::max)()));
    CHECK_UNARY_FALSE(spook::isnan(std::numeric_limits<double>::lowest()));
  }
}
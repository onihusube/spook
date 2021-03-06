#include "doctest/doctest.h"

#include "spook.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4146)
#endif				  // MSC_VER

namespace spook_test::numelic {

    TEST_CASE("gcd test") {
        {
            constexpr auto gcd = spook::gcd(0, 0);
            CHECK_EQ(0, gcd);
        }
        {
            constexpr auto gcd = spook::gcd(0, 1);
            CHECK_EQ(1, gcd);
        }
		{
			constexpr auto gcd = spook::gcd(3, 7);
			CHECK_EQ(1, gcd);
		}
		 {
            constexpr auto gcd = spook::gcd(1071u, 1029);
            CHECK_EQ(21, gcd);
        }
        {
            constexpr auto gcd = spook::gcd(1071ull, -1029);
            CHECK_EQ(21, gcd);
        }
        {
            constexpr auto gcd = spook::gcd(-1071ll, 1029u);
            CHECK_EQ(21, gcd);
        }
        {
            constexpr auto gcd = spook::gcd(-1071, -1029);
            CHECK_EQ(21, gcd);
        }
        {
            constexpr auto gcd = spook::gcd(67280421310721ull, 1029ull);
            CHECK_EQ(1, gcd);
        }
        {
            constexpr auto gcd = spook::gcd(2048, 67280421310721ull);
            CHECK_EQ(1, gcd);
        }

        {
            constexpr auto gcd = spook::gcd(1071.0, 1029.0);
            CHECK_EQ(21.0, gcd);
        }
    }

    TEST_CASE("lcm test") {
        {
            constexpr auto lcm = spook::lcm(0, 1);
            CHECK_EQ(0, lcm);
        }
        {
            constexpr auto lcm = spook::lcm(1, 0);
            CHECK_EQ(0, lcm);
        }
        {
            constexpr auto lcm = spook::lcm(16, 24);
            CHECK_EQ(48, lcm);
        }
        {
            constexpr auto lcm = spook::lcm(42u, 54);
            CHECK_EQ(378, lcm);
        }
        {
            constexpr auto lcm = spook::lcm(42ull, -54);
            CHECK_EQ(378, lcm);
        }
        {
            constexpr auto lcm = spook::lcm(-42, 54u);
            CHECK_EQ(378, lcm);
        }
        {
            constexpr auto lcm = spook::lcm(-42, -54);
            CHECK_EQ(378, lcm);
        }

        {
            constexpr auto lcm = spook::lcm(42.0, 54.0);
            CHECK_EQ(378.0, lcm);
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif // MSC_VER
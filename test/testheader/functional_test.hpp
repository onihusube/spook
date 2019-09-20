#include "doctest/doctest.h"

#include "spook.hpp"

namespace spook_test::functional {

	struct functor {
		constexpr auto operator()() const & -> int {
			return 10;
		}

		constexpr auto operator()(int n) const noexcept -> int {
			return n;
		}
	};

    constexpr auto test_func(int n) -> int {
        return n + n;
    }

    TEST_CASE("function invoke test") {
        constexpr functor fobj{};

        {
            constexpr auto n = spook::invoke(fobj);
            CHECK_EQ(10, n);
        }

        {
            constexpr auto n = spook::invoke(fobj, 1024);
            CHECK_EQ(1024, n);
        }

        {
            auto lambda = [](auto f, auto n) constexpr { return n * f(); };

            constexpr auto n = spook::invoke(lambda, fobj, 10);
            CHECK_EQ(100, n);
        }

        {
            constexpr auto n = spook::invoke(test_func, 10);
            CHECK_EQ(20, n);
        }
    }

    struct has_member {

        constexpr auto member_function(int n) const & noexcept -> int
        {
            return n;
        }

        int member_object;
    };

    TEST_CASE("memberptr invoke test") {
        constexpr const has_member fobj{128};

        {
            constexpr auto n = spook::invoke(&has_member::member_function, fobj, 256);
            CHECK_EQ(256, n);
        }

        {
            constexpr auto n = spook::invoke(&has_member::member_function, &fobj, 256);
            CHECK_EQ(256, n);
        }

        {
            constexpr int n = spook::invoke(&has_member::member_object, fobj);
            CHECK_EQ(128, n);
        }

        {
            constexpr int n = spook::invoke(&has_member::member_object, &fobj);
            CHECK_EQ(128, n);
        }
    }
}
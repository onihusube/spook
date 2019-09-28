#include "doctest/doctest.h"

#include <tuple>

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

	TEST_CASE("first_of test") {
		constexpr auto hof = spook::first_of(
			[]() constexpr {return 128; },
			[](int n) constexpr {return n * 2; },
			//[](auto&&) { return 0; });
			spook::delete_if([](auto&&) { return 0; }));
		
		constexpr auto n1 = hof();
		CHECK_EQ(128, n1);

		constexpr auto n2 = hof(3);
		CHECK_EQ(6, n2);

		//auto t = hof(spook::deleted_t{});

		auto l = spook::delete_if([](auto&&) { return 0; });
		static_assert(std::invocable<decltype(l), spook::deleted_t>);
	}
}

namespace spook_test::tuple {

    TEST_CASE("apply test") {
        {
            constexpr auto f = [](int n, double, int m, double) constexpr {
                return n + m;
            };

            constexpr auto r = spook::apply(f, std::make_tuple(128, 0.0, 64, 1.0));
            CHECK_EQ(192, r);
        }

        {
            constexpr auto f = [](int n, double v, int m, double d) constexpr {
                return n + m + v + d;
            };

            constexpr auto r = spook::apply(f, std::make_tuple(128, 32.0, 64, 16.0));
            CHECK_EQ(240.0, r);
        }
    }

    struct test {
        int n;
        double v;

        constexpr test(int m, double d) : n{m}, v{d} {}
    };

    TEST_CASE("make from tuple test") {
        constexpr auto t = spook::make_from_tuple<test>(std::make_tuple(32, 128.0));

        CHECK_EQ(32, t.n);
        CHECK_EQ(128.0, t.v);
    }
}
#include "doctest/doctest.h"

#include "spook.hpp"

namespace spook_test::bit {

	TEST_CASE("bit reverse test") {
		constexpr auto t = spook::bit::detail::bit_reverse(0b0011U);
	}
}
#include "doctest/doctest.h"

#include "spook.hpp"

namespace spook_test::bit {

	TEST_CASE("popcount test") {
		CHECK_EQ(0, spook::popcount(0u));
		CHECK_EQ(4, spook::popcount(0xFu));
		CHECK_EQ(8, spook::popcount(0xFFu));
		CHECK_EQ(16, spook::popcount(0xFFFFu));
		CHECK_EQ(32, spook::popcount(0xFFFFFFFFu));
		CHECK_EQ(64, spook::popcount(0xFFFFFFFFFFFFFFFFu));
		CHECK_EQ(1, spook::popcount(0x8000000000000000u));
		CHECK_EQ(32, spook::popcount(0xCCCCCCCCCCCCCCCCu));
		CHECK_EQ(32, spook::popcount(0x0F0F0F0F0F0F0F0Fu));
		CHECK_EQ(4, spook::popcount(0xAAu));
	}

	TEST_CASE("bit reverse test") {
		{
			using int_t = std::uint8_t;
			CHECK_EQ(0u, spook::bit_reverse(int_t(0)));
			CHECK_EQ(0x80u, spook::bit_reverse(int_t(1)));
			CHECK_EQ(0xFFu, spook::bit_reverse(int_t(0xFFu)));
			CHECK_EQ(0x50u, spook::bit_reverse(int_t(0x0Au)));
			CHECK_EQ(0xD0u, spook::bit_reverse(int_t(0x0Bu)));
			CHECK_EQ(0x30u, spook::bit_reverse(int_t(0x0Cu)));
			CHECK_EQ(0xB0u, spook::bit_reverse(int_t(0x0Du)));
			CHECK_EQ(0x70u, spook::bit_reverse(int_t(0x0Eu)));
			CHECK_EQ(0xF0u, spook::bit_reverse(int_t(0x0Fu)));
			CHECK_EQ(0x05u, spook::bit_reverse(int_t(0xA0u)));
			CHECK_EQ(0x0Du, spook::bit_reverse(int_t(0xB0u)));
			CHECK_EQ(0x03u, spook::bit_reverse(int_t(0xC0u)));
			CHECK_EQ(0x0Bu, spook::bit_reverse(int_t(0xD0u)));
			CHECK_EQ(0x07u, spook::bit_reverse(int_t(0xE0u)));
			CHECK_EQ(0x0Fu, spook::bit_reverse(int_t(0xF0u)));
		}
		{
			using int_t = std::uint16_t;
			CHECK_EQ(0u, spook::bit_reverse(int_t(0)));
			CHECK_EQ(0x8000u, spook::bit_reverse(int_t(1)));
			CHECK_EQ(0xFFFFu, spook::bit_reverse(int_t(0xFFFFu)));
			CHECK_EQ(0xB3D5u, spook::bit_reverse(int_t(0xABCDu)));
			CHECK_EQ(0xABCDu, spook::bit_reverse(int_t(0xB3D5u)));
		}
		{
			using int_t = std::uint32_t;
			CHECK_EQ(0u, spook::bit_reverse(int_t(0)));
			CHECK_EQ(0x80000000u, spook::bit_reverse(int_t(1)));
			CHECK_EQ(0xFFFFFFFFu, spook::bit_reverse(int_t(0xFFFFFFFFu)));
			CHECK_EQ(0xD5F7B3D5u, spook::bit_reverse(int_t(0xABCDEFABu)));
			CHECK_EQ(0xABCDEFABu, spook::bit_reverse(int_t(0xD5F7B3D5u)));
		}
		{
			using int_t = std::uint64_t;
			CHECK_EQ(0u, spook::bit_reverse(int_t(0)));
			CHECK_EQ(0x8000000000000000ull, spook::bit_reverse(int_t(1)));
			CHECK_EQ(0xFFFFFFFFFFFFFFFFull, spook::bit_reverse(int_t(0xFFFFFFFFFFFFFFFFull)));
			CHECK_EQ(0xB3D5F7B3D5F7B3D5ull, spook::bit_reverse(int_t(0xABCDEFABCDEFABCDull)));
			CHECK_EQ(0xABCDEFABCDEFABCDull, spook::bit_reverse(int_t(0xB3D5F7B3D5F7B3D5ull)));
		}
	}

	TEST_CASE("countr test") {
		CHECK_EQ(1, spook::countr_zero(0b10u));
		CHECK_EQ(4, spook::countr_zero(0x10u));
		CHECK_EQ(8, spook::countr_zero(0x100u));
		CHECK_EQ(16, spook::countr_zero(0x10000u));
		CHECK_EQ(32, spook::countr_zero(std::uint32_t(0)));
		CHECK_EQ(64, spook::countr_zero(std::uint64_t(0)));

		CHECK_EQ(1, spook::countr_one(0x01u));
		CHECK_EQ(4, spook::countr_one(0x0Fu));
		CHECK_EQ(8, spook::countr_one(0x0FFu));
		CHECK_EQ(16, spook::countr_one(0xFFFFu));
		CHECK_EQ(32, spook::countr_one(0xFFFFFFFFu));
		CHECK_EQ(64, spook::countr_one(0xFFFFFFFFFFFFFFFFull));
	}

	TEST_CASE("countl test") {
		CHECK_EQ(1, spook::countl_zero(std::uint32_t(0x40000000u)));
		CHECK_EQ(4, spook::countl_zero(std::uint32_t(0x08000000u)));
		CHECK_EQ(8, spook::countl_zero(std::uint32_t(0x00800000u)));
		CHECK_EQ(16, spook::countl_zero(std::uint32_t(0x00008000u)));
		CHECK_EQ(32, spook::countl_zero(std::uint32_t(0)));
		CHECK_EQ(64, spook::countl_zero(std::uint64_t(0)));

		CHECK_EQ(1, spook::countl_one(std::uint32_t(0x80000000u)));
		CHECK_EQ(4, spook::countl_one(std::uint32_t(0xF0000000u)));
		CHECK_EQ(8, spook::countl_one(std::uint32_t(0xFF000000u)));
		CHECK_EQ(16, spook::countl_one(std::uint32_t(0xFFFF0000u)));
		CHECK_EQ(32, spook::countl_one(std::uint32_t(0xFFFFFFFFu)));
		CHECK_EQ(64, spook::countl_one(std::uint64_t(0xFFFFFFFFFFFFFFFFull)));
	}

	TEST_CASE("is_pow2 test"){
		CHECK_UNARY(spook::is_pow2(1u));
		CHECK_UNARY(spook::is_pow2(2u));
		CHECK_UNARY(spook::is_pow2(4u));
		CHECK_UNARY(spook::is_pow2(8u));
		CHECK_UNARY(spook::is_pow2(16u));
		CHECK_UNARY(spook::is_pow2(32u));
		CHECK_UNARY(spook::is_pow2(64u));
		CHECK_UNARY(spook::is_pow2(128u));
		CHECK_UNARY(spook::is_pow2(256u));
		CHECK_UNARY(spook::is_pow2(512u));
		CHECK_UNARY(spook::is_pow2(1024u));

		CHECK_UNARY(spook::is_pow2(0x0000010000000000ull));
		CHECK_UNARY(spook::is_pow2(0x0000000001000000ull));
		CHECK_UNARY(spook::is_pow2(0x0100000000000000ull));
		CHECK_UNARY(spook::is_pow2(0x8000000000000000ull));

		CHECK_UNARY_FALSE(spook::is_pow2(0u));
		CHECK_UNARY_FALSE(spook::is_pow2(3209809318501u));
		CHECK_UNARY_FALSE(spook::is_pow2(0xFu));
		CHECK_UNARY_FALSE(spook::is_pow2(0x0000010000001000ull));
		CHECK_UNARY_FALSE(spook::is_pow2(0x000000000A000000ull));
		CHECK_UNARY_FALSE(spook::is_pow2(0x0C00000000000000ull));
		CHECK_UNARY_FALSE(spook::is_pow2(0x5000000000000000ull));
	}

	TEST_CASE("ceill2 test") {
		CHECK_EQ(1u, spook::ceil2(0u));
		CHECK_EQ(2u, spook::ceil2(2u));
		CHECK_EQ(4u, spook::ceil2(3u));
		CHECK_EQ(0x10u, spook::ceil2(0xFu));
		CHECK_EQ(0x100000u, spook::ceil2(0xF0000u));
		CHECK_EQ(0x1000000000u, spook::ceil2(0xF11111111u));
		CHECK_EQ(0x1000000000u, spook::ceil2(0x1000000000u));
		CHECK_EQ(0x1000000000000000ull, spook::ceil2(0x0800000000000001ull));
	}

	TEST_CASE("floor2 tset") {
		CHECK_EQ(0u, spook::floor2(0u));
		CHECK_EQ(2u, spook::floor2(2u));
		CHECK_EQ(2u, spook::floor2(3u));
		CHECK_EQ(0x8u, spook::floor2(0xFu));
		CHECK_EQ(0x80000u, spook::floor2(0xF0000u));
		CHECK_EQ(0x800000000u, spook::floor2(0xF11111111u));
		CHECK_EQ(0x1000000000u, spook::floor2(0x1000000000u));
		CHECK_EQ(0x0800000000000000ull, spook::floor2(0x0800000000000001ull));
		CHECK_EQ(0x1000000000000000ull, spook::floor2(0x1000000000000001ull));
	}

	TEST_CASE("lsb_pos test") {
		CHECK_EQ(0, spook::lsb_pos(0u));
		CHECK_EQ(1, spook::lsb_pos(1u));
		CHECK_EQ(5, spook::lsb_pos(0xFF10u));
		CHECK_EQ(32, spook::lsb_pos(0xFFFF80000000u));
		CHECK_EQ(64, spook::lsb_pos(0x8000000000000000u));
	}

	TEST_CASE("msb_pos test") {
		CHECK_EQ(0, spook::msb_pos(0u));
		CHECK_EQ(1, spook::msb_pos(1u));
		CHECK_EQ(16, spook::msb_pos(0xFF11u));
		CHECK_EQ(32, spook::msb_pos(0x800F0100u));
		CHECK_EQ(64, spook::msb_pos(0x800010000A001010u));
	}

	TEST_CASE("log2p1 test") {
		CHECK_EQ(0u, spook::log2p1(0u));
		CHECK_EQ(1u, spook::log2p1(1u));
		CHECK_EQ(7u, spook::log2p1(127u));
		CHECK_EQ(8u, spook::log2p1(128u));
		CHECK_EQ(10u, spook::log2p1(512u));
		CHECK_EQ(11u, spook::log2p1(1024u));
		CHECK_EQ(32u, spook::log2p1(0xF30cf328u));
		CHECK_EQ(64u, spook::log2p1(0xFF043802abcf9328u));
	}

	TEST_CASE("pow2 test") {
		CHECK_EQ(1, spook::pow2(0));
		CHECK_EQ(2, spook::pow2(1));
		CHECK_EQ(0x0000000000000080, spook::pow2(7));
		CHECK_EQ(0x0000000000008000, spook::pow2(15));
		CHECK_EQ(0x0000000080000000, spook::pow2(31));
		CHECK_EQ(0x8000000000000000, spook::pow2(63));
		CHECK_EQ(0x0000000000200000, spook::pow2(21));
	}
}
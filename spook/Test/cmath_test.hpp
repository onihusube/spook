#pragma once

#include "../pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "spook.hpp"

namespace spook_test::cmath {

	TEST_CLASS(cmath_test)
	{
	public:

		TEST_METHOD(isinf_test) {
			constexpr auto inf = std::numeric_limits<double>::infinity();

			Assert::IsTrue(spook::isinf(-inf));
			Assert::IsTrue(spook::isinf( inf));
			
			Assert::IsFalse(spook::isinf(0.0));
			Assert::IsFalse(spook::isinf((std::numeric_limits<double>::max)()));
			Assert::IsFalse(spook::isinf(std::numeric_limits<double>::lowest()));
		}

		TEST_METHOD(isnan_test) {
			constexpr auto nan = std::numeric_limits<double>::quiet_NaN();

			constexpr auto b = spook::isnan(nan);
			static_assert(b == true);

			Assert::IsTrue(spook::isnan(nan));

			Assert::IsFalse(spook::isnan(0.0));
			Assert::IsFalse(spook::isnan((std::numeric_limits<double>::max)()));
			Assert::IsFalse(spook::isnan(std::numeric_limits<double>::lowest()));
		}

		TEST_METHOD(fabs_test) {
			constexpr auto p_inf = std::numeric_limits<double>::infinity();

			Assert::IsTrue(p_inf == spook::fabs(-std::numeric_limits<double>::infinity()));
			Assert::IsTrue(p_inf == spook::fabs( std::numeric_limits<double>::infinity()));

			constexpr auto p_zero = +0.0;

			Assert::IsTrue(p_zero == spook::fabs(-0.0));
			Assert::IsTrue(p_zero == spook::fabs(+0.0));

			constexpr auto expect = 3.141;

			Assert::IsTrue(expect == spook::fabs(-3.141));
			Assert::IsTrue(expect == spook::fabs(+3.141));
		}

		TEST_METHOD(signbit_test) {
			Assert::IsTrue(spook::signbit(-1.0));
			Assert::IsFalse(spook::signbit(1.0));

			constexpr auto inf = std::numeric_limits<double>::infinity();

			Assert::IsTrue(spook::signbit(-inf));
			Assert::IsFalse(spook::signbit(inf));

			//未対応
			//Assert::IsTrue(spook::signbit(-0.0));
			//Assert::IsFalse(spook::signbit(0.0));

			constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
			//Assert::IsTrue(spook::signbit(-nan));
			//Assert::IsFalse(spook::signbit(nan));
		}

		TEST_METHOD(copysign_test) {

			Assert::AreEqual(+2.0, spook::copysign(2.0, +2.0));
			Assert::AreEqual(-2.0, spook::copysign(2.0, -2.0));

			Assert::AreEqual(+2.0, spook::copysign(-2.0, +2.0));
			Assert::AreEqual(-2.0, spook::copysign(-2.0, -2.0));

			constexpr auto nan = std::numeric_limits<double>::quiet_NaN();
			constexpr auto inf = std::numeric_limits<double>::infinity();

			//Assert::IsTrue (spook::signbit(spook::copysign(nan, -2.0)));
			//Assert::IsFalse(spook::signbit(spook::copysign(nan, +2.0)));
			Assert::IsTrue (std::signbit(spook::copysign(nan, -2.0)));
			Assert::IsFalse(std::signbit(spook::copysign(nan, +2.0)));

			Assert::AreEqual(+inf, spook::copysign(inf, +2.0));
			Assert::AreEqual(-inf, spook::copysign(inf, -2.0));
		}



		TEST_METHOD(ceil_test) {
			Assert::IsTrue(3.0 == spook::ceil(3.0));
			Assert::IsTrue(4.0 == spook::ceil(3.1));
			Assert::IsTrue(4.0 == spook::ceil(3.5));
			Assert::IsTrue(4.0 == spook::ceil(3.9));

			Assert::IsTrue(-3.0 == spook::ceil(-3.0));
			Assert::IsTrue(-3.0 == spook::ceil(-3.1));
			Assert::IsTrue(-3.0 == spook::ceil(-3.5));
			Assert::IsTrue(-3.0 == spook::ceil(-3.9));
		}

		TEST_METHOD(floor_test) {
			Assert::IsTrue(3.0 == spook::floor(3.0));
			Assert::IsTrue(3.0 == spook::floor(3.1));
			Assert::IsTrue(3.0 == spook::floor(3.5));
			Assert::IsTrue(3.0 == spook::floor(3.9));

			Assert::IsTrue(-3.0 == spook::floor(-3.0));
			Assert::IsTrue(-4.0 == spook::floor(-3.1));
			Assert::IsTrue(-4.0 == spook::floor(-3.5));
			Assert::IsTrue(-4.0 == spook::floor(-3.9));
		}

		TEST_METHOD(trunc_test) {
			Assert::IsTrue(3.0 == spook::trunc(3.0));
			Assert::IsTrue(3.0 == spook::trunc(3.1));
			Assert::IsTrue(3.0 == spook::trunc(3.5));
			Assert::IsTrue(3.0 == spook::trunc(3.9));

			Assert::IsTrue(-3.0 == spook::trunc(-3.0));
			Assert::IsTrue(-3.0 == spook::trunc(-3.1));
			Assert::IsTrue(-3.0 == spook::trunc(-3.5));
			Assert::IsTrue(-3.0 == spook::trunc(-3.9));
		}


		TEST_METHOD(roud_to_nearest_test) {
			Assert::IsTrue(3.0 == spook::round_to_nearest(3.0));
			Assert::IsTrue(3.0 == spook::round_to_nearest(3.1));
			Assert::IsTrue(4.0 == spook::round_to_nearest(3.5));
			Assert::IsTrue(4.0 == spook::round_to_nearest(3.9));

			Assert::IsTrue(-3.0 == spook::round_to_nearest(-3.0));
			Assert::IsTrue(-3.0 == spook::round_to_nearest(-3.1));
			Assert::IsTrue(-4.0 == spook::round_to_nearest(-3.5));
			Assert::IsTrue(-4.0 == spook::round_to_nearest(-3.9));
		}

		TEST_METHOD(remainder_test) {
			{
				auto expected = std::remainder(3.14, 3.0);
				constexpr auto r = spook::remainder(3.14, 3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(5.0, 2.0);
				constexpr auto r = spook::remainder(5.0, 2.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(6.0, 4.0);
				constexpr auto r = spook::remainder(6.0, 4.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(6.3, 3.0);
				constexpr auto r = spook::remainder(6.3, 3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(6.3, -3.0);
				constexpr auto r = spook::remainder(6.3, -3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(-6.3, 3.0);
				constexpr auto r = spook::remainder(-6.3, 3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(6.3, 3.15);
				constexpr auto r = spook::remainder(6.3, 3.15);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::remainder(6.0, 2.0);
				constexpr auto r = spook::remainder(6.0, 2.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
		}

		TEST_METHOD(fmod_test) {
			{
				auto expected = std::fmod(3.14, 3.0);
				constexpr auto r = spook::fmod(3.14, 3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(5.0, 2.0);
				constexpr auto r = spook::fmod(5.0, 2.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(6.0, 4.0);
				constexpr auto r = spook::fmod(6.0, 4.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(6.3, 3.0);
				constexpr auto r = spook::fmod(6.3, 3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(6.3, -3.0);
				constexpr auto r = spook::fmod(6.3, -3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(-6.3, 3.0);
				constexpr auto r = spook::fmod(-6.3, 3.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(6.3, 3.15);
				constexpr auto r = spook::fmod(6.3, 3.15);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
			{
				auto expected = std::fmod(6.0, 2.0);
				constexpr auto r = spook::fmod(6.0, 2.0);
				Assert::AreEqual(expected, r, 1.0E-15);
			}
		}

		TEST_METHOD(sin_test) {
			using namespace spook::constant;

			{
				constexpr double coeff = 0.0;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 0.25;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 0.5;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 0.75;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.0;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.25;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.5;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.75;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 2.0;

				auto expected = std::sin(coeff * π<>);
				constexpr auto calc = spook::sin(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}
		}


		TEST_METHOD(cos_test) {
			using namespace spook::constant;

			{
				constexpr double coeff = 0.0;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 0.25;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 0.5;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 0.75;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.0;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.25;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.5;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				constexpr double coeff = 1.75;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
				//Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				constexpr double coeff = 2.0;

				auto expected = std::cos(coeff * π<>);
				constexpr auto calc = spook::cos(coeff * π<>);

				Assert::AreEqual(expected, calc, 1.0E-15);
				//Assert::AreEqual(expected, calc, 1.0E-14);
			}
		}

		TEST_METHOD(tan_test) {
			using namespace spook::constant;

			constexpr auto t = spook::tan(π<> / 2.1);
		}

		TEST_METHOD(asin_test) {
			constexpr auto as = spook::asin(0.5);
			//constexpr auto ac = spook::acos(-1.0);
		}

		TEST_METHOD(atan_test) {

			{
				auto expected = 4.0 * std::atan(1.0);
				constexpr auto pi = 4.0 * spook::atan(1.0);

				Assert::AreEqual(expected, pi, 1.0E-15);
			}

			{
				auto expected = std::atan(-1.0);
				constexpr auto calc = spook::atan(-1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(-0.75);
				constexpr auto calc = spook::atan(-0.75);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(-0.5);
				constexpr auto calc = spook::atan(-0.5);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(-0.25);
				constexpr auto calc = spook::atan(-0.25);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(0.0);
				constexpr auto calc = spook::atan(0.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(0.25);
				constexpr auto calc = spook::atan(0.25);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(0.5);
				constexpr auto calc = spook::atan(0.5);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(0.75);
				constexpr auto calc = spook::atan(0.75);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan(1.0);
				constexpr auto calc = spook::atan(1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}
		}

		TEST_METHOD(atan2_test) {
			{
				auto expected = std::atan2(0.0, 1.0);
				constexpr auto calc = spook::atan2(0.0, 1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(1.0, 1.0);
				constexpr auto calc = spook::atan2(1.0, 1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(1.0, 0.0);
				constexpr auto calc = spook::atan2(1.0, 0.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(1.0, -1.0);
				constexpr auto calc = spook::atan2(1.0, -1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(0.0, -1.0);
				constexpr auto calc = spook::atan2(0.0, -1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(-1.0, -1.0);
				constexpr auto calc = spook::atan2(-1.0, -1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(-1.0, 0.0);
				constexpr auto calc = spook::atan2(-1.0, 0.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::atan2(-1.0, 1.0);
				constexpr auto calc = spook::atan2(-1.0, 1.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}
		}

		TEST_METHOD(exp_test) {

			constexpr auto e = spook::exp(3.2);
		}

		TEST_METHOD(log_test) {

			constexpr auto l1 = spook::log(2.5);
		}


		TEST_METHOD(pow_test) {
			constexpr auto p = spook::pow(10.0, -5);
		}


		TEST_METHOD(sqrt_test) {
			//intelisenseが死ぬので
#ifndef __EDG__
			{
				constexpr auto calc = spook::sqrt(-2.0);

				Assert::IsTrue(spook::isnan(calc));
			}

			{
				auto expected = std::sqrt(2.0);
				constexpr auto calc = spook::sqrt(2.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(3.0);
				constexpr auto calc = spook::sqrt(3.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(4.0);
				constexpr auto calc = spook::sqrt(4.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(8.0);
				constexpr auto calc = spook::sqrt(8.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(16.0);
				constexpr auto calc = spook::sqrt(16.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(32.0);
				constexpr auto calc = spook::sqrt(32.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(64.0);
				constexpr auto calc = spook::sqrt(64.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::sqrt(128.0);
				constexpr auto calc = spook::sqrt(128.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				auto expected = std::sqrt(256.0);
				constexpr auto calc = spook::sqrt(256.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				auto expected = std::sqrt(512.0);
				constexpr auto calc = spook::sqrt(512.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				auto expected = std::sqrt(1024.0);
				constexpr auto calc = spook::sqrt(1024.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}
#endif
		}

		TEST_METHOD(cbrt_test) {
			//intelisenseが死ぬので
#ifndef __EDG__
			{
				constexpr auto calc = spook::cbrt(-2.0);

				Assert::IsTrue(spook::isnan(calc));
			}

			{
				auto expected = std::cbrt(2.0);
				constexpr auto calc = spook::cbrt(2.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(3.0);
				constexpr auto calc = spook::cbrt(3.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(4.0);
				constexpr auto calc = spook::cbrt(4.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(8.0);
				constexpr auto calc = spook::cbrt(8.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(16.0);
				constexpr auto calc = spook::cbrt(16.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(32.0);
				constexpr auto calc = spook::cbrt(32.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(64.0);
				constexpr auto calc = spook::cbrt(64.0);

				Assert::AreEqual(expected, calc, 1.0E-15);
			}

			{
				auto expected = std::cbrt(128.0);
				constexpr auto calc = spook::cbrt(128.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				auto expected = std::cbrt(256.0);
				constexpr auto calc = spook::cbrt(256.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				auto expected = std::cbrt(512.0);
				constexpr auto calc = spook::cbrt(512.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}

			{
				auto expected = std::cbrt(1024.0);
				constexpr auto calc = spook::cbrt(1024.0);

				Assert::AreEqual(expected, calc, 1.0E-14);
			}
#endif
		}
	};
}
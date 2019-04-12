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
			//Assert::IsTrue(spook::signbit(-0.0));

			Assert::IsFalse(spook::signbit(1.0));
			//Assert::IsFalse(spook::signbit(0.0));
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


		TEST_METHOD(exp_test) {

			constexpr auto e = spook::exp(1.0);
		}
	};
}
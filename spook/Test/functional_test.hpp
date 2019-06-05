#pragma once

#include "../pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "spook.hpp"

namespace spook_test::functional {

	struct functor {
		constexpr auto operator()() const -> int {
			return 10;
		}

		constexpr auto operator()(int n) const -> int {
			return n;
		}
	};

	struct has_member {
		constexpr auto member_function(int n) const -> int {
			return n;
		}

		int member_object;
	};

	TEST_CLASS(functional_test)
	{
	public:

		TEST_METHOD(functor_invoke_test) {
			constexpr functor fobj{};

			{
				constexpr auto n = spook::invoke(fobj);
				Assert::AreEqual(10, n);
			}

			{
				constexpr auto n = spook::invoke(fobj, 1024);
				Assert::AreEqual(1024, n);
			}

			{
				auto lambda = [](auto f, auto n) constexpr { return n * f(); };

				constexpr auto n = spook::invoke(lambda, fobj, 10);
				Assert::AreEqual(100, n);
			}
		}

		constexpr auto call_datamember(const has_member& f) {
			using member_dataptr = int has_member::*;
			member_dataptr ptr = &has_member::member_object;

			return spook::invoke(ptr, f);
		}

		TEST_METHOD(memberptr_invoke_test) {
			using member_funcptr = auto (has_member::*)(int) const -> int;
			using member_dataptr = int has_member::*;

			constexpr has_member fobj{};

			{
				constexpr member_funcptr ptr = &has_member::member_function;
				constexpr auto n = spook::invoke(ptr, fobj, 10);
				Assert::AreEqual(10, n);
			}

			{
				//constexpr auto n = call_datamember(fobj);
				//Assert::AreEqual(1024, n);
			}
		}
	};
}
#pragma once

#include <limits>
#include <utility>
#include <complex>
#include <array>
#include <type_traits>
#include <cstdint>

#define SPOOK_NOT_USE_CONSTEVAL

#ifdef SPOOK_NOT_USE_CONSTEVAL

#define SPOOK_CONSTEVAL [[nodiscard]] constexpr

#else

#define SPOOK_CONSTEVAL [[nodiscard]] consteval

#endif // SPOOK_NOT_USE_CONSTEVAL


namespace spook {
	inline namespace customization_points {
		/**
		* @brief numeric_limitsをadaptするtraits
		* @detail これは組み込み型等のためのstd::numeric_limits<T>を使用するもの
		* @detail 組み込み型でない型で使用する場合は同じシグネチャになるように明示的特殊化する
		*/
		template<typename T>
		struct numeric_limits_traits : public std::numeric_limits<T> {};

		/**
		* @brief is_floating_pointをadaptするtraits
		* @detail これは組み込み型等のためのstd::is_floating_point<T>を使用するもの
		* @detail 組み込み型でない型で使用する場合は同じシグネチャになるように明示的特殊化する
		*/
		template<typename T>
		struct is_floating_point : public std::is_floating_point<T> {};

		template<typename T>
		inline constexpr bool is_floating_point_v = spook::is_floating_point<T>::value;

		/**
		* @brief is_integralをadaptするtraits
		* @detail これは組み込み型等のためのstd::is_integral<T>を使用するもの
		* @detail 組み込み型でない型で使用する場合は同じシグネチャになるように明示的特殊化する
		*/
		template<typename T>
		struct is_integral : public std::is_integral<T> {};

		template<typename T>
		inline constexpr bool is_integral_v = spook::is_integral<T>::value;

		/**
		* @brief 符号なし整数型かどうかを調べる
		* @detail これは組み込み型等のためのもの
		* @detail 任意の型に対しては明示的特殊化によってアダプトする
		*/
		template <typename T>
		struct is_unsigned : std::conjunction<
			spook::is_integral<T>,
			std::negation<std::is_signed<T>>
		> {};


	} // namespace customization_points
}


#ifdef __cpp_lib_concepts
#include <concepts>
#define CONCEPT_FALLBACK(constraint, ...) > requires constraint
#define CONCEPT_FALLBACK_REDECL(constraint, ...) > requires constraint

namespace spook {
	inline namespace concepts {

		template<typename T>
		concept integral = spook::is_integral_v<T>::value;

		template<typename T>
		concept floating_point = spook::is_floating_point<T>::value;

		template<typename T>
		concept unsigned_integral = spook::is_unsigned<T>::value;
	}
}
#else
#define CONCEPT_FALLBACK(constraint, ...) , __VA_ARGS__ = nullptr
#define CONCEPT_FALLBACK_REDECL(constraint, ...) , __VA_ARGS__
#endif


namespace spook {
	inline namespace type_traits {

		/**
		* @brief 条件が全てtrueの時に有効化
		*/
		template<typename... Ts>
		using enabler = std::enable_if_t<std::conjunction_v<Ts...>, std::nullptr_t>;

		/**
		* @brief あるメンバポインタがある型のメンバを指すものであるかを調べる
		* @tparam MemberPtr メンバポインタ
		* @tparam T MemberPtrによって指されるクラスかを調べる型
		*/
		template<typename MemberPtr, typename T>
		struct is_member_of : std::false_type {};

		template<typename T, typename R, typename... Args>
		struct is_member_of<R(T::*)(Args...), T> : std::true_type {};

		template<typename T, typename U>
		struct is_member_of<U T::*, T> : std::true_type {};

		template<typename MemberPtr, typename T>
		using is_member_of_decay = is_member_of<std::remove_cvref_t<MemberPtr>, std::remove_cvref_t<T>>;


		/**
		* @brief あるメンバポインタから属する型を取り出す
		* @tparam MemberPtr メンバポインタ
		*/
		template<typename MemberPtr>
		struct memberptr_to;

		// 要らないらしい
		// template<typename T, typename R, typename... Args>
		// struct memberptr_to<R(T::*)(Args...)> {
		// 	using type = T;
		// };

		template<typename T, typename U>
		struct memberptr_to<U T::*> {
			using type = T;
		};

		/**
		* @brief あるメンバポインタから属する型を取り出す
		* @tparam MemberPtr メンバポインタ
		*/
		template<typename MemberPtr>
		using memberptr_to_t = typename memberptr_to<MemberPtr>::type;
	}
}

namespace spook {
	inline namespace cmath {
		inline namespace constant {

			template<typename T = double>
			inline constexpr T pi = T(3.1415926535897932384626433832795L);


			template<typename T = double>
			inline constexpr T e = T(2.718281828459045235360287471352L);
		}

		inline namespace literals {

			SPOOK_CONSTEVAL auto operator""_radf(long double degree) -> float {
				using ld = long double;

				return float(degree / ld(180.0) * pi<ld>);
			}

			SPOOK_CONSTEVAL auto operator""_degf(long double radian) -> float {
				using ld = long double;

				return float(radian / pi<ld> * ld(180.0));
			}

			SPOOK_CONSTEVAL auto operator""_rad(long double degree) -> double {
				using ld = long double;

				return double(degree / ld(180.0) * pi<ld>);
			}

			SPOOK_CONSTEVAL auto operator""_deg(long double radian) -> double {
				using ld = long double;

				return double(radian / pi<ld> * ld(180.0));
			}

			SPOOK_CONSTEVAL auto operator""_radld(long double degree) -> long double {
				using ld = long double;

				return degree / ld(180.0) * pi<ld>;
			}

			SPOOK_CONSTEVAL auto operator""_degld(long double radian) -> long double {
				using ld = long double;

				return radian / pi<ld> * ld(180.0);
			}
		}

		//前方宣言
		template <typename T>
		SPOOK_CONSTEVAL auto signbit(T x) -> bool;

		template <typename T CONCEPT_FALLBACK(concepts::floating_point<T, enabler<spook::is_floating_point<T>>)>
		SPOOK_CONSTEVAL auto fabs(T x) -> T;

		template <typename T>
		SPOOK_CONSTEVAL auto abs(T x) -> T;

		template <typename T>
		SPOOK_CONSTEVAL auto floor(T x) -> T;

		template <typename T, typename N>
		SPOOK_CONSTEVAL auto pow(T x, N y) -> T;

		template <typename T>
		SPOOK_CONSTEVAL auto isinf(T x) -> bool {
			if constexpr (spook::is_integral_v<T>) {
				return false;
			}

			if ((spook::numeric_limits_traits<T>::max)() < x) return true;
			if (x < spook::numeric_limits_traits<T>::lowest()) return true;
			return false;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto isnan(T x) -> bool {
			if constexpr (spook::is_integral_v<T>) {
				return true;
			}

			return !(x == x);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto isfinite(T x) -> bool {
			if constexpr (spook::is_integral_v<T>) {
				return false;
			}

			if (spook::isinf(x)) return false;
			if (spook::isnan(x)) return false;

			return true;
		}

		template <typename T>
		SPOOK_CONSTEVAL auto iszero(T x) -> bool {
			return x == T(0.0);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto isnormal(T x) -> bool {
			if constexpr (spook::is_integral_v<T>) {
				return true;
			}

			if (spook::iszero(x)) return false;
			if (spook::isnan(x)) return false;
			if (spook::isinf(x)) return false;
			if (spook::fabs(x) < (spook::numeric_limits_traits<T>::min)()) return false;

			return true;
		}

		template <typename T>
		SPOOK_CONSTEVAL auto signbit(T x) -> bool {
			//ゼロの符号判定、定数式じゃ無理？
			//if (x == T(0.0)) {
			//	return (T(1.0) / x) < 0;
			//}

			//can't detect NaN's sign, for compile time...
			//std::bit_cast()...!?

			return x < T(0.0);
		}
		template <typename T>
		SPOOK_CONSTEVAL auto copysign(T x, T y) -> T {
			auto absv = spook::isnan(x) ? spook::numeric_limits_traits<T>::quiet_NaN() : spook::abs(x);

			return spook::signbit(y) ? -absv : absv;
		}

		template <typename T CONCEPT_FALLBACK_REDECL(concepts::floating_point<T, enabler<spook::is_floating_point<T>>)>
		SPOOK_CONSTEVAL auto fabs(T x) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (spook::iszero(x)) return T(+0.0);
			}

			return spook::signbit(x) ? -x : x;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto abs(T x) -> T {
			if constexpr (spook::is_floating_point_v<T> == true) {
				return spook::fabs(x);
			} else if constexpr (spook::is_unsigned<T>::value == true) {
				return x;
			} else {
				//符号付整数型の時
				if (T(0) <= x) return x;
				return -x;
			}
		}

		template <typename T>
		SPOOK_CONSTEVAL auto ceil(T x) -> T {
			if constexpr (spook::is_integral_v<T>) {
				return x;
			}

			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (x == 0.0) return x;
				if (spook::isinf(x)) return x;
			}

			if (x < 0.0) {
				return -spook::floor(spook::fabs(x));
			}
			else {
				auto s = std::size_t(x);

				return (T(s) == x) ? T(s) : T(++s);
			}
		}

		template<typename T>
		SPOOK_CONSTEVAL auto floor(T x) -> T {
			if constexpr (spook::is_integral_v<T>) {
				return x;
			}

			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (x == 0.0) return x;
				if (spook::isinf(x)) return x;
			}

			if (x < 0.0) {
				return -spook::ceil(spook::fabs(x));
			}
			else {
				auto s = std::size_t(x);

				return T(s);
			}
		}

		template<typename T>
		SPOOK_CONSTEVAL auto trunc(T x) -> T {
			if (spook::signbit(x)) {
				return spook::ceil(x);
			}
			else {
				return spook::floor(x);
			}
		}

		template<typename T CONCEPT_FALLBACK(concepts::floating_point<T, enabler<spook::is_floating_point<T>>)>
		SPOOK_CONSTEVAL auto round_to_nearest(T x) -> T {
			//ゼロ方向へ丸める
			auto rounded = spook::trunc(x);
			//少数部の絶対値を取り出す
			auto decimal = spook::fabs(x - rounded);
			
			if (decimal == T(0.5)) {
				if ((std::int64_t(rounded) & 1) == std::int64_t(1)) {
					//偶数方向へ丸める
					return spook::signbit(rounded) ? --rounded : ++rounded;
				}
			}
			else if (T(0.5) < decimal) {
				//ゼロ方向へ丸められているので反対向きに1つ増やす
				return spook::signbit(rounded) ? --rounded : ++rounded;
			}

			return rounded;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto remainder(T x, T y) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (spook::iszero(y) || spook::isinf(x) || spook::isnan(x) || spook::isnan(y)) {
					return spook::numeric_limits_traits<T>::quiet_NaN();
				}
			}

			auto n = spook::round_to_nearest(x / y);

			return x - n * y;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto fmod(T x, T y) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				bool y_is_zero = spook::iszero(y);

				if (!y_is_zero && spook::iszero(x)) return x;
				if (spook::isinf(x) || y_is_zero || spook::isnan(x) || spook::isnan(y)) {
					return spook::numeric_limits_traits<T>::quiet_NaN();
				}
				else {
					//xが有限であり、yが±∞であるとき
					if (spook::isinf(y)) return x;
				}
			}

			auto n = spook::trunc(x / y);

			return x - n * y;
		}

		namespace detail {
			
			/**
			* @brief 三角関数の入力を[0, pi]の範囲に収める
			* @param theta θ[rad]
			* @return {[0, pi]に収めたθ, 象限の情報（piの奇数倍の時true）}
			*/
			template<typename T>
			SPOOK_CONSTEVAL auto reduce_theta(T theta) -> std::pair<T, bool> {
				auto x = spook::fabs(theta);

				if (0.0 <= x && x < constant::pi<T>) {
					//ごちゃごちゃ計算する必要はない
					return { x, false };
				}

				//実質的にはこれ、ただし商も欲しかったので展開している
				//spook::fmod(spook::fabs(theta), constant::pi<T>);

				auto n = spook::trunc(spook::fabs(x) / constant::pi<T>);
				auto r = x - n * constant::pi<T>;
				if (spook::signbit(r)) r += constant::pi<T>;

				//象限の情報を得る、余りがゼロということはpiの整数倍の時
				//bool isodd = (r == 0.0) ? false : spook::fmod(n, T(2.0)) == T(1.0);

				//[0, pi]に押し込めた数と象限の情報
				return { r, spook::fmod(n, T(2.0)) == T(1.0) };
			}
		}

		template<typename T>
		SPOOK_CONSTEVAL auto sin(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (arg == 0.0) return arg;
				if (spook::isinf(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
				if (spook::isnan(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
			}

			auto [theta, isodd] = detail::reduce_theta(arg);

			//piの整数倍の時
			if (theta == 0.0) return 0.0;

			T x_sq = -(theta * theta);
			T series = theta;
			T tmp = theta;
			T fact = T(2.0);
			T r{};  //積み残し
			T t{};  //級数和の一時変数

			//マクローリン級数の計算
			do {
				tmp *= x_sq / (fact * (fact + T(1.0)));
				t = series + (tmp + r);
				r = (tmp + r) - (t - series);
				series = t;
				//series += tmp;
				fact += T(2.0);
			} while (spook::fabs(tmp) >= spook::numeric_limits_traits<T>::epsilon());

			series = isodd ? -series : series;
			return spook::signbit(arg) ? -series : series;
		}


		template<typename T>
		SPOOK_CONSTEVAL auto cos(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (arg == 0.0) return 1.0;
				if (spook::isinf(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
				if (spook::isnan(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
			}

			auto [theta, isodd] = detail::reduce_theta(arg);

			//pi/2の整数倍の時
			if (theta == 0.5 * constant::pi<T>) return 0.0;

			T x_sq = -(theta * theta);
			T series = T(1.0);
			T tmp = T(1.0);
			T fact = T(1.0);
			T r{};  //積み残し
			T t{};  //級数和の一時変数

			//マクローリン級数の計算
			do {
				tmp *= x_sq / (fact * (fact + T(1.0)));
				t = series + (tmp + r);
				r = (tmp + r) - (t - series);
				series = t;
				fact += T(2.0);
			} while (spook::fabs(tmp) >= spook::numeric_limits_traits<T>::epsilon());

			series = isodd ? -series : series;
			return series;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto tan(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (arg == 0.0) return arg;
				if (spook::isinf(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
				if (spook::isnan(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
			}

			auto[theta, isodd] = detail::reduce_theta(arg);

			//pi/2の整数倍の時
			if (theta == 0.5 * constant::pi<T>) return spook::numeric_limits_traits<T>::infinity();

			auto sin_v = spook::sin(theta);
			auto cos_v = spook::cos(theta);

			auto tan = sin_v / cos_v;

			return spook::copysign(arg, tan);
		}
		
		template<typename T>
		SPOOK_CONSTEVAL auto asin(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (arg == 0.0) return arg;
				if (T(1.0) < spook::fabs(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
			}

			//0 <= x の所で計算
			const T x = spook::fabs(arg);
			T x_sq = x * x;
			T k = T(1.0);
			T tmp = x;
			T term = T(1.0);
			T series = x;
			T r{};  //積み残し
			T t{};  //級数和の一時変数

			do {
				tmp *= k / (k + T(1.0)) * x_sq;
				k += T(2.0);
				term = tmp / k;

				t = series + (term + r);
				r = (term + r) - (t - series);
				series = t;
			} while (spook::fabs(term) >= spook::numeric_limits_traits<T>::epsilon());

			return spook::copysign(series, arg);;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto acos(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (arg == 0.0) return arg;
				if (T(1.0) < spook::fabs(arg)) return spook::numeric_limits_traits<T>::quiet_NaN();
			}

			return T(0.5) * constant::pi<T>* spook::asin(arg);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto atan(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (spook::iszero(arg)) return arg;
				if (spook::isinf(arg)) return spook::copysign(spook::constant::pi<T> / 2.0, arg);
			}

			//0 < x の所で計算
			const T x = spook::fabs(arg);
			const T coeff = x / (T(1.0) + x * x);
			const T coeff2 = x * coeff;

			T k = T(1.0);
			T tmp = T(1.0);
			T series = T(1.0);
			T r{};  //積み残し
			T t{};  //級数和の一時変数

			do {
				auto k_2 = k + k;
				tmp *= k_2 / (k_2 + T(1.0)) * coeff2;

				t = series + (tmp + r);
				r = (tmp + r) - (t - series);
				series = t;

				k += T(1.0);
			} while (spook::fabs(tmp) >= spook::numeric_limits_traits<T>::epsilon());

			//適正な符号へ戻す
			return spook::copysign(coeff * series, arg);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto atan2(T y, T x) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (spook::iszero(y)) {
					if (spook::signbit(x)) {
						return spook::copysign(spook::constant::pi<T>, y);
					}
					else {
						return spook::copysign(T(0.0), y);
					}
				}

				if (spook::iszero(x)) {
					return spook::copysign(spook::constant::pi<T> / T(2.0), y);
				}

				if (spook::isinf(y)) {
					if (spook::isinf(x)) {
						if (spook::signbit(x)) {
							return spook::copysign(T(3.0) * spook::constant::pi<T> / T(4.0), y);
						}
						else {
							return spook::copysign(spook::constant::pi<T> / T(4.0), y);
						}
					}

					return spook::copysign(spook::constant::pi<T> / T(2.0), y);
				}
				else {
					if (spook::isinf(x)) {
						if (spook::signbit(x)) {
							return spook::copysign(spook::constant::pi<T>, y);
						}
						else {
							return spook::copysign(T(0.0), y);
						}
					}
				}
			}

			auto atan_v = spook::atan(y / x);

			if (!spook::signbit(x)) {
				return atan_v;
			}

			if (spook::signbit(y)) {
				return atan_v - spook::constant::pi<T>;
			}

			return atan_v + spook::constant::pi<T>;
		}

		namespace detail {

			/**
			* @brief 入力が整数であるとわかっているときのためのexp
			* @param arg e^argのarg、整数であること
			* @return e^argを返す、近似計算ではない
			*/
			template<typename T>
			SPOOK_CONSTEVAL auto simple_exp(T arg) -> T {
				return spook::pow(constant::e<T>, size_t(arg));
			}
		}

		template<typename T>
		SPOOK_CONSTEVAL auto exp(T arg) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (arg == T(0.0)) return T(1.0);
				if (spook::isinf(arg)) {
					if (spook::signbit(arg)) return T(+0.0);
					return arg;
				}
			}
			
			//0 < x の範囲で計算
			T x = spook::signbit(arg)? -arg : arg;

			if (x == T(1.0)) return spook::signbit(arg) ? (1.0 / constant::e<T>) : constant::e<T>;

			//1 < xのとき
			if (1.0 < x) {
				//小数点未満の部分とそれ以外の部分に分ける
				T x1 = spook::floor(x);
				T x2 = x - x1;

				//それぞれのexpをかけて計算
				T expx = spook::exp(x2) * detail::simple_exp(x1);

				return spook::signbit(arg) ? (1.0 / expx) : expx;
			}

			T series = T(1.0);
			T tmp = T(1.0);
			T n = T(1.0);
			T r{};  //積み残し
			T t{};  //級数和の一時変数

			//マクローリン級数の計算
			do {
				tmp *= x / n;
				t = series + (tmp + r);
				r = (tmp + r) - (t - series);
				series = t;
				n += T(1.0);
			} while (spook::fabs(tmp) >= spook::numeric_limits_traits<T>::epsilon());

			//適正な値へ
			return spook::signbit(arg) ? (1.0 / series) : series;
		}


		template<typename T>
		SPOOK_CONSTEVAL auto log(T x) -> T {

			T series = (x - 1) / (x + 1);
			T tmp = series;
			T k = T(3.0);
			T term{};
			T r{};  //積み残し
			T t{};  //級数和の一時変数
			const T sq = series * series;

			//マクローリン級数の計算
			do {
				tmp *= sq;
				term = tmp / k;

				t = series + (term + r);
				r = (term + r) - (t - series);
				series = t;

				k += T(2.0);
			} while (spook::fabs(term) >= spook::numeric_limits_traits<T>::epsilon());

			return series + series;
		}

		namespace detail {

			/**
			* @brief 再帰的に2の累乗回の累乗を計算し、それらを適切に掛けることで掛け算回数を減らす
			* @param x 2の累乗回かけてあるx
			* @param prev_n 一つ前の冪の数（2の倍数
			* @param pow_n 掛けるべき回数、関数が戻った後は残りの掛けるべき回数へ変化する
			* @return 適切な回数かけられた途中結果
			*/
			template<typename T>
			SPOOK_CONSTEVAL auto pow_impl(T x, std::size_t prev_n, std::size_t& pow_n) -> T {
				//現在のかけた回数
				std::size_t now_n = prev_n + prev_n;

				if (now_n <= pow_n) {
					//x^2を計算し、次へ
					auto powx = pow_impl(x*x, now_n, pow_n);
					//終わったら、残りのかける回数を調べて必要ならかけて返す
					if (prev_n <= pow_n) {
						pow_n -= prev_n;
						powx *= x;
					}
					return powx;
				}
				else {
					//掛けるべき回数を超えた時は一つ前の結果を最大として戻る
					pow_n -= prev_n;
					return x;
				}
			}
		}

		template<typename T, typename N>
		SPOOK_CONSTEVAL auto pow(T x, N y) -> T {
			if constexpr (spook::is_integral_v<N>) {
				//0 < nの所で計算
				std::size_t n = spook::abs(y);

				if (n == 0)
					return T(1.0);
				if (n == 1)
					return spook::signbit(y) ? T(1.0) / x : x;

				auto x_pow_y = detail::pow_impl(x * x, 2, n);

				//奇数乗の時
				if (n == 1)
					x_pow_y *= x;

				//負の冪なら逆数へ
				return spook::signbit(y) ? T(1.0) / x_pow_y : x_pow_y;
			} else if constexpr (spook::is_floating_point_v<N>) {
				//TとNが一致しないならば、常にlong doubleを使用して計算
				using floating_t = std::conditional_t<std::is_same_v<T, N>, T, long double>;

				floating_t logx = spook::log(floating_t(x));
				return T(spook::exp(y * logx));
			} else {
				//その他の型に対しては未定義
				static_assert([]{return false;}(), "spook::pow<T, N>() is not implemented.");
			}
		}

		template<size_t N, typename T>
		SPOOK_CONSTEVAL auto n_root(T x) -> T {
			if (spook::signbit(x)) return spook::numeric_limits_traits<T>::quiet_NaN();

			const T c1 = T(N + 1) / T(N);
			const T c2 = -x / T(N);

			//初期値依存が激しいので考察の余地あり
			T xk = T(1.0) / x;
			T x_prev{};

			do {
				x_prev = xk;
				xk *= (c1 + c2 * spook::pow(xk, N));
				if (spook::isinf(xk)) break;
			} while (spook::fabs(xk - x_prev) >= spook::numeric_limits_traits<T>::epsilon());

			return spook::fabs(x * spook::pow(xk, N - 1));
		}

		template<typename T>
		SPOOK_CONSTEVAL auto sqrt(T x) -> T {
			return n_root<2>(x);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto cbrt(T x) -> T {
			return n_root<3>(x);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto lerp(T a, T b, T t) -> T {
			if (spook::iszero(t)) return a;
			if (t == T(1.0)) return b;
			if (spook::isfinite(t) && a == b) return a;

			return a + t * (b - a);
		}
	}

	inline namespace complex {

		template<typename T CONCEPT_FALLBACK(spook::floating_point<T, enabler<spook::is_floating_point<T>>)>
		SPOOK_CONSTEVAL auto polar(T rho, T theta) -> std::complex<T> {
			return{ rho * spook::cos(theta), rho * spook::sin(theta) };
		}
	}

	inline namespace bit {
		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto countr_zero(T x) -> int;
	}

	inline namespace numeric {

		namespace detail {

			struct mod_def {

				template<typename T>
				SPOOK_CONSTEVAL auto operator()(T m, T n) -> T {
					if constexpr (spook::is_floating_point_v<T>) {
						return spook::fmod(m, n);
					} else {
						return m % n;
					}
				}
			};
			
			/**
			* @brief ユークリッドの互除法によるジェネリックな実装
			* @detail 型Rはdoubleからの変換が可能であり、コピー（ムーブ）構築・代入が可能である必要がある
			* @param m, n 最大公約数を求める値のペア、前処理済
			* @param mod 剰余を求める関数オブジェクト
			* @return GCD
			*/
			template <typename R, typename Mod>
			SPOOK_CONSTEVAL auto gcd_impl(R m, R n, Mod mod) -> R {
				const R zero = R(0.0);

				do {
					R oldn = n;
					n = mod(m ,n);
					m = oldn;
				} while (n != zero);

				return R(m);
			}

			/**
			* @brief 符号なし整数型用の効率的な実装
			* @param m, n 最大公約数を求める値のペア、前処理済
			* @return GCD
			*/
			template <typename I>
			SPOOK_CONSTEVAL auto gcd_impl(I m, I n) -> I {
				//素の値を取り出す（2^n倍を出来るだけ戻す）
				const auto m_zeros = spook::countr_zero(m);
				m >>= m_zeros;
				const auto common_zeros = std::min(m_zeros, spook::countr_zero(n));
				n >>= common_zeros;

				do {
					//nの素の値を取り出す（2^nで割る）
					n >>= spook::countr_zero(n);

					//常にnが大きくなるようにswap
					if (n < m) {
						auto temp = m;
						m = n;
						n = temp;
					}

					//大きい方から小さい方を引く、ゼロになるまで
					n -= m;
				} while (n != 0);

				//最終的にゼロになった時に引いた数字が最大公約数（最初に素の値にした分を元に戻す）
				return m << common_zeros;
			}
		}

		template<typename M, typename N, typename Mod= detail::mod_def>
		SPOOK_CONSTEVAL auto gcd(M mx, N nx, [[maybe_unused]] Mod&& mod = detail::mod_def{}) -> std::common_type_t<M, N> {
			using R = std::common_type_t<M, N>;

			if (spook::iszero(mx)) return R(nx);
			if (spook::iszero(nx)) return R(mx);

			if constexpr (spook::is_integral_v<M> && spook::is_integral_v<N>) {
				using UR = std::make_unsigned_t<R>;

				//整数型用の処理
				UR abs_m = UR(spook::abs(mx));
				UR abs_n = UR(spook::abs(nx));

				return R(detail::gcd_impl(abs_m, abs_n));
			} else {
				const R abs_m = R(spook::abs(mx));
				const R abs_n = R(spook::abs(nx));

				R m = std::max(abs_m, abs_n);
				R n = std::min(abs_m, abs_n);

				return detail::gcd_impl(m, n, std::forward<Mod>(mod));
			}
		}

		template <typename M, typename N, typename Mod= detail::mod_def>
		SPOOK_CONSTEVAL auto lcm(M mx, N nx, [[maybe_unused]] Mod&& mod = detail::mod_def{}) -> std::common_type_t<M, N> {
			using R = std::common_type_t<M, N>;

			if (spook::iszero(mx) || spook::iszero(nx)) return R(0.0);

			if constexpr (spook::is_integral_v<M> && spook::is_integral_v<N>){
				using UR = std::make_unsigned_t<R>;
				//整数型用の処理
				UR abs_m = UR(spook::abs(mx));
				UR abs_n = UR(spook::abs(nx));

				//オーバーフロー対策に大きかろう方を先に割る
				return R((abs_m / detail::gcd_impl(abs_m, abs_n)) * abs_n);
			} else {
				const R abs_m = R(spook::abs(mx));
				const R abs_n = R(spook::abs(nx));

				R m = std::max(abs_m, abs_n);
				R n = std::min(abs_m, abs_n);

				//オーバーフロー対策に大きい方を先に割る
				return R((m / detail::gcd_impl(m, n, std::forward<Mod>(mod))) * n);
			}
		}
	}

	inline namespace bit {

		namespace detail {

			/**
			* @brief 任意の64ビット値を0~63の間に押し込めるハッシュ関数
			* @detail 1ビットだけ立っている値に対しては完全ハッシュとなる、その出力は下のhash2posによってその桁位置に写すことができる
			* @detail 詳細？http://supertech.csail.mit.edu/papers/debruijn.pdf
			* @param x 入力
			* @return [0, 63]の間の値
			*/
			SPOOK_CONSTEVAL auto hash_64(std::uint64_t x) -> int {
				int h = (x * 0x03F566ED27179461UL) >> 58;
				return h;
			}

			/**
			* @brief hash_64()の出力を対応する桁位置へ変換
			* @detail 求める簡易なもの -> https://wandbox.org/permlink/DKLoL1qKgiwTrugE
			*/
			inline constexpr char hash2pos[] = {1, 2, 60, 3, 61, 41, 55, 4, 62, 33, 50, 42, 56, 20, 36, 5, 63, 53, 31, 34, 51, 13, 15, 43, 57, 17, 28, 21, 37, 24, 45, 6, 64, 59, 40, 54, 32, 49, 19, 35, 52, 30, 12, 14, 16, 27, 23, 44, 58, 39, 48, 18, 29, 11, 26, 22, 38, 47, 10, 25, 46, 9, 8, 7};

			/**
			* @brief 最上位ビット以下を1で埋める
			* @param x 最上位ビットを検出したい整数値
			* @return 最上位ビット以下が１で埋められた値
			*/
			SPOOK_CONSTEVAL auto fill_msb_less_one(std::uint64_t x) -> std::uint64_t {
				x |= (x >> 1);
				x |= (x >> 2);
				x |= (x >> 4);
				x |= (x >> 8);
				x |= (x >> 16);
				x |= (x >> 32);

				return x;
			}

		} // namespace detail

		/**
		* @brief 右端を1桁目として、最上位ビットの位置を求める
		* @param x LSB位置を求める値
		* @return LSBの位置（x == 0なら0）
		*/
		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto msb_pos(T x) -> int {
			if (x == T(0)) return 0;
			//最上位ビットだけを残す
			T v = T(detail::fill_msb_less_one(std::uint64_t(x)));
			v = v ^ (v >> 1);

			int h = detail::hash_64(v);

			return detail::hash2pos[h];
		}

		/**
		* @brief 右端を1桁目として、最下位ビットの位置を求める
		* @param x MSB位置を求める値
		* @return MSBの位置（x == 0なら0）
		*/
		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto lsb_pos(T x) -> int
		{
			if (x == T(0)) return 0;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4146)
#endif				  // MSC_VER
			T v = x & -x; //最下位ビットだけを残す
#ifdef _MSC_VER
#pragma warning(pop)
#endif // MSC_VER

			int h = detail::hash_64(v);

			return detail::hash2pos[h];
		}

		namespace detail {

			SPOOK_CONSTEVAL auto popcount_impl(std::uint64_t x) -> int {
				using int_t = std::uint64_t;
				int_t t = ((x & int_t(0xAAAAAAAAAAAAAAAAull)) >> 1) + (x & int_t(0x5555555555555555ull));
				t = ((t & int_t(0xCCCCCCCCCCCCCCCCull)) >> 2) + (t & int_t(0x3333333333333333ull));
				t = ((t & int_t(0xF0F0F0F0F0F0F0F0ull)) >> 4) + (t & int_t(0x0F0F0F0F0F0F0F0Full));
				t = ((t & int_t(0xFF00FF00FF00FF00ull)) >> 8) + (t & int_t(0x00FF00FF00FF00FFull));
				t = ((t & int_t(0xFFFF0000FFFF0000ull)) >> 16) + (t & int_t(0x0000FFFF0000FFFFull));
				t = ((t & int_t(0xFFFFFFFF00000000ull)) >> 32) + (t & int_t(0x00000000FFFFFFFFull));

				return int(t);
			}

			template<typename T>
			SPOOK_CONSTEVAL auto popcount_impl(T x) -> int {
				int count{};

				while (x != T(0))
				{
					count += T(1) & x;
					x >>= 1;
				}

				return count;
			}
		}

		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto is_pow2(T x) -> bool {
			return x && !(x & (x - 1));
		}

		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto popcount(T x) -> int {
			if constexpr (spook::is_pow2(sizeof(T))) {
				return detail::popcount_impl(std::uint64_t(x));
			}
			else {
				return detail::popcount_impl(x);
			}
		}

		namespace detail {
			SPOOK_CONSTEVAL auto bit_reverse_impl(std::uint8_t x) -> std::uint8_t {
				using int_t = std::uint8_t;
				int_t t = (x  >> 4) | (x  << 4);
				t = ((t & int_t(0xCCu)) >> 2) | ((t & int_t(0x33u)) << 2);
				t = ((t & int_t(0xAAu)) >> 1) | ((t & int_t(0x55u)) << 1);

				return t;
			}

			SPOOK_CONSTEVAL auto bit_reverse_impl(std::uint16_t x) -> std::uint16_t {
				using int_t = std::uint16_t;
				int_t t = (x >> 8) | (x << 8);
				t = ((t & int_t(0xF0F0u)) >> 4) | ((t & int_t(0x0F0Fu)) << 4);
				t = ((t & int_t(0xCCCCu)) >> 2) | ((t & int_t(0x3333u)) << 2);
				t = ((t & int_t(0xAAAAu)) >> 1) | ((t & int_t(0x5555u)) << 1);

				return t;
			}

			SPOOK_CONSTEVAL auto bit_reverse_impl(std::uint32_t x) -> std::uint32_t {
				using int_t = std::uint32_t;
				int_t t = (x >> 16) | (x << 16);
				t = ((t & int_t(0xFF00FF00u)) >> 8) | ((t & int_t(0x00FF00FFu)) << 8);
				t = ((t & int_t(0xF0F0F0F0u)) >> 4) | ((t & int_t(0x0F0F0F0Fu)) << 4);
				t = ((t & int_t(0xCCCCCCCCu)) >> 2) | ((t & int_t(0x33333333u)) << 2);
				t = ((t & int_t(0xAAAAAAAAu)) >> 1) | ((t & int_t(0x55555555u)) << 1);

				return t;
			}

			SPOOK_CONSTEVAL auto bit_reverse_impl(std::uint64_t x) -> std::uint64_t {
				//最大桁の半分から再帰的に半分づつ入れ替えていく

				using int_t = std::uint64_t;
				int_t t = (x >> 32) | (x << 32);
				t = ((t & int_t(0xFFFF0000FFFF0000u)) >> 16) | ((t & int_t(0x0000FFFF0000FFFFu)) << 16);
				t = ((t & int_t(0xFF00FF00FF00FF00u)) >> 8 ) | ((t & int_t(0x00FF00FF00FF00FFu)) << 8);
				t = ((t & int_t(0xF0F0F0F0F0F0F0F0u)) >> 4 ) | ((t & int_t(0x0F0F0F0F0F0F0F0Fu)) << 4);
				t = ((t & int_t(0xCCCCCCCCCCCCCCCCu)) >> 2 ) | ((t & int_t(0x3333333333333333u)) << 2);
				t = ((t & int_t(0xAAAAAAAAAAAAAAAAu)) >> 1 ) | ((t & int_t(0x5555555555555555u)) << 1);

				return t;
			}

			template <typename T>
			SPOOK_CONSTEVAL auto bit_reverse_impl(T x) = delete;
		} // namespace detail

		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto bit_reverse(T x) -> T {
			//各型用の二分再帰による実装に移譲
			return detail::bit_reverse_impl(x);
		}

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto rotl(T x, int s) -> T;

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto rotr(T x, int s) -> T {
			constexpr auto N = sizeof(T) * CHAR_BIT;
			const int r = s % N;

			if (r == 0) return x;
			if (r < 0) return rotl(x, -r);
			return (x >> r) | (x << (N - r));
		}

		template<typename T CONCEPT_FALLBACK_REDECL(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto rotl(T x, int s) -> T {
			constexpr auto N = sizeof(T) * CHAR_BIT;
			const int r = s % N;

			if (r == 0) return x;
			if (r < 0) return rotr(x, -r);
			return (x << r) | (x >> (N - r));
		}

		template<typename T CONCEPT_FALLBACK_REDECL(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto countr_zero(T x) -> int {
			if (x == 0) return sizeof(T) * CHAR_BIT;

			int n = spook::lsb_pos(x);
			return --n;
		}

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto countr_one(T x) -> int {
			if (x == 0) return 0;

			return spook::countr_zero(~x);
		}

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto countl_zero(T x) -> int {
			if (x == 0) return sizeof(T) * CHAR_BIT;

			auto n = spook::msb_pos(x);
			return (sizeof(T) * CHAR_BIT) - n;
		}

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto countl_one(T x) -> int{
			if (x == 0) return 0;
			return spook::countl_zero(~x);
		}

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto ceil2(T x) -> T {
			if (x == T(0)) return T(1);

			//丁度2^Nの値を正しく出力するために1引いておく
			--x;
			T v = T(detail::fill_msb_less_one(std::uint64_t(x)));
			//帰ってきた値が全て１で埋まっていた場合（TのビットをNとすると2^N <= xの場合）、結果は正しくない
			return ++v;
		}

		template<typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto floor2(T x) -> T {
			if (x == T(0)) return T(0);

			T v = T(detail::fill_msb_less_one(std::uint64_t(x)));
			return v ^ (v >> 1);	//最上位ビットだけを残す
		}

		template <typename T CONCEPT_FALLBACK(spook::unsigned_integral<T, enabler<is_unsigned<T>>)>
		SPOOK_CONSTEVAL auto log2p1(T x) -> T {
			//log2p1はすなわち最上位ビットの位置！
			return T(spook::msb_pos(x));
		}

		template<typename R = std::uint64_t CONCEPT_FALLBACK(spook::unsigned_integral<R, enabler<is_unsigned<R>>)>
		SPOOK_CONSTEVAL auto pow2(unsigned int n) -> R {
			return R(1) << n;
		}
	}

	inline namespace functional {

		namespace detail {

			template<typename T>
			struct is_reference_wrapper : std::false_type {};
			
			template<typename T>
			struct is_reference_wrapper<std::reference_wrapper<T>> : std::true_type {};

			template<typename T>
			inline constexpr bool is_reference_wrapper_v = detail::is_reference_wrapper<T>::value;

			template<typename F, typename T, typename... Args>
			SPOOK_CONSTEVAL decltype(auto) invoke_memfn(F&& f, T&& t1, Args&&... args) {
				using prime_t = std::remove_cvref_t<decltype(t1)>;

				if constexpr (std::is_base_of_v<type_traits::memberptr_to_t<F>, prime_t>) {
					return (std::forward<T>(t1).*f)(std::forward<Args>(args)...);
				}
				else if constexpr (detail::is_reference_wrapper_v<prime_t>) {
					return (std::forward<T>(t1).get().*f)(std::forward<Args>(args)...);
				} else {
					return ((*std::forward<T>(t1)).*f)(std::forward<Args>(args)...);
				}
			}

			template <typename F, typename T>
			SPOOK_CONSTEVAL decltype(auto) invoke_memobj(F&& f, T&& t1) {
				using prime_t = std::remove_cvref_t<decltype(t1)>;

				if constexpr (std::is_base_of_v<type_traits::memberptr_to_t<F>, prime_t>) {
					return std::forward<T>(t1).*f;
				} else if constexpr (detail::is_reference_wrapper_v<prime_t>) {
					return std::forward<T>(t1).get().*f;
				} else {
					return (*std::forward<T>(t1)).*f;
				}
			}
		}

		template<typename F, typename... Args>
		SPOOK_CONSTEVAL auto invoke(F&& f, Args&&... args) -> std::invoke_result_t<F, Args...> {
			using prime_t = std::remove_cvref_t<F>;

			if constexpr (std::is_member_function_pointer_v<prime_t>) {
				//メンバポインタ呼び出し
				return detail::invoke_memfn(std::forward<F>(f), std::forward<Args>(args)...);
			} else if constexpr (sizeof...(Args) == 1 && std::is_member_object_pointer_v<prime_t>) {
				//メンバオブジェクト呼び出し
				return detail::invoke_memobj(std::forward<F>(f), std::forward<Args>(args)...);
			} else {
				//その他関数呼び出し
				return std::forward<F>(f)(std::forward<Args>(args)...);
			}
		}

		/**
		* @brief first_ofにて意図的な関数のdeleteを検知するためのタグ
		*/
		struct deleted_t {};

		/**
		* @brief first_ofに意図的な関数のdeleteを伝えるためのラッパー
		* @tparam F deleteしたい呼び出しを持つ関数型
		*/
		template <typename F>
		struct delete_if {

			template<typename Fn = F>
			constexpr delete_if(Fn&& f) : func(std::forward<Fn>(f)) {}

			template <typename... Args>
			requires std::invocable<F const&, Args...>
			SPOOK_CONSTEVAL auto operator()(Args&&...) const -> deleted_t {
				static_assert([] {return false; }(), "Deleted overload was invoked.");
				return {};
			}

			//using Callable_t = std::add_lvalue_reference_t<std::add_const_t<F>>;

		private:
			[[no_unique_address]] F func;
		};

		template<typename F>
		delete_if(F&&) -> delete_if<std::decay_t<F>>;

		/**
		* @brief 複数の関数をひとまとめにした関数オブジェクトを作成する
		* @tparam Fs 任意個数のCallableオブジェクト
		* @detail 呼び出し時は登録した順番に呼び出し可能かをチェックする
		*/
		template<typename... Fs>
		struct first_of {
			SPOOK_CONSTEVAL void operator()(...) const {
				static_assert([] {return false; }(), "No matching function for call to `first_of`. No matching function was found.");
			}
		};

		template<typename... Fs>
		first_of(Fs&&...) -> first_of<std::decay_t<Fs>...>;

		/**
		* @brief 複数の関数をひとまとめにした関数オブジェクトを作成する、first_ofの実装部分
		* @tparam F 先頭のCallableオブジェクト
		* @tparam Fs 任意個数のCallableオブジェクト
		* @detail 呼び出し時は登録した順番に呼び出し可能かをチェックする
		* @detail https://brevzin.github.io/c++/2019/09/23/declarative-cpos/
		*/
		template <typename F, typename... Fs>
		struct first_of<F, Fs...> {

			template<typename Fn = F, typename... Fns>
			constexpr first_of(Fn&& f, Fns&&... fs)
				: first(std::forward<Fn>(f))
				, rest(std::forward<Fns>(fs)...)
			{}

			template <typename... Args>
			SPOOK_CONSTEVAL decltype(auto) operator()(Args &&... args) const {
				if constexpr (std::invocable<F const&, Args...>) {
					return spook::invoke(first, std::forward<Args>(args)...);
				} else {
					return spook::invoke(rest, std::forward<Args>(args)...);
				}
			}

			/**
			* @brief delete_ifでラップされ登録されている関数呼び出し、コンパイルエラーをおこす
			* @detail のだけど、現状こっちは呼ばれていない・・・
			*/
			template<typename... Args>
			requires std::invocable<F const&, Args...> &&
					 std::same_as<std::invoke_result_t<decltype(this->first), Args...>, spook::deleted_t>
			SPOOK_CONSTEVAL void operator()(Args&&...) const {
				static_assert([]{return false; }(), "Deleted overload was invoked.");
			}

			using Subsequent = first_of<Fs...>;

		private:
			[[no_unique_address]] F first;
			[[no_unique_address]] Subsequent rest;
		};
	}

	inline namespace tuple {

		namespace detail {
			template <typename F, typename Tuple, std::size_t... Index>
			SPOOK_CONSTEVAL decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<Index...>) {
				return spook::invoke(std::forward<F>(f), std::get<Index>(std::forward<Tuple>(t))...);
			}

			template <typename T, typename Tuple, std::size_t... Index>
			SPOOK_CONSTEVAL auto make_from_tuple_impl(Tuple&& t, std::index_sequence<Index...>) -> T {
				return T(std::get<Index>(std::forward<Tuple>(t))...);
			}
		}

		template<typename F, typename Tuple>
		SPOOK_CONSTEVAL auto apply(F&& f, Tuple&& t) -> decltype(std::apply(std::declval<F&>(), std::declval<Tuple&>())) {
			using prime_tuple_t = std::remove_reference_t<Tuple>;
			
			return detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size_v<prime_tuple_t>>{});
		}

		template<typename T, typename Tuple>
		SPOOK_CONSTEVAL auto make_from_tuple(Tuple&& t) -> T {
			using prime_tuple_t = std::remove_reference_t<Tuple>;

			return detail::make_from_tuple_impl<T>(std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size_v<prime_tuple_t>>{});
		}
	}

	inline namespace dft {

		template<typename Range>
		using value_complex = std::complex<typename std::remove_cvref_t<Range>::value_type>;

		/**
		* @brief 4点FFT
		* @param first 入力範囲の開始点、少なくとも4要素イテレート可能である事
		* @param last 入力範囲の終端、使用しない
		* @detail http://www.lsi-contest.com/2012/shiyou_3-2.html
		* @return 4点FFT結果（複素数値）
		*/
		template<typename Iterator, typename Sentinel>
		SPOOK_CONSTEVAL auto fft_4(Iterator&& first, [[maybe_unused]] Sentinel&& last) -> std::array<value_complex<std::iterator_traits<Iterator>>, 4> {
			using prime_iter_t = std::remove_cvref_t<Iterator>;
			using T = typename std::iterator_traits<prime_iter_t>::value_type;
			using complex = value_complex<std::iterator_traits<Iterator>>;
			using Array = std::array<complex, 4>;

			auto iter = first;

			const auto x0 = *iter;
			const auto x1 = *(++iter);
			const auto x2 = *(++iter);
			const auto x3 = *(++iter);

			//x[0]+x[2]
			const auto x02p = x0 + x2;
			//x[0]-x[2]
			const auto x02m = x0 - x2;
			//x[1]+x[3]
			const auto x13p = x1 + x3;
			//x[1]-x[3]
			const auto x13m = x1 - x3;

			return Array{complex{x02p + x13p, T(0.0)}, complex{x02m, -x13m}, complex{x02p - x13p, T(0.0)}, complex{x02m, x13m}};
		}

		/**
		* @brief 4点FFT
		* @tparam Range 範囲を保持する任意の型、例えばコンテナ
		* @param container イテレータを引き出し可能な範囲を保持する任意のオブジェクト、少なくとも4要素を保持していること
		* @return 4点FFT結果（複素数値）
		*/
		template<typename Range>
		SPOOK_CONSTEVAL auto fft_4(Range&& container) -> std::array<value_complex<Range>, 4> {
			using std::begin;
			using std::end;

			return spook::fft_4(begin(container), end(container));
		}
	}
}
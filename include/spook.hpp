#pragma once

#include <limits>
#include <utility>

#define SPOOK_NOT_USE_CONSTEVAL

#ifdef SPOOK_NOT_USE_CONSTEVAL

#define SPOOK_CONSTEVAL constexpr

#else

#define SPOOK_CONSTEVAL consteval

#endif // SPOOK_NOT_USE_CONSTEVAL

namespace spook {

	/**
	* @brief numeric_limitsをadaptするtraits
	* @detail これは組み込み型等のためのstd::numeric_limits<T>を使用するもの
	* @detail 組み込み型でない型で使用する場合は同じシグネチャになるように部分特殊化する
	*/
	template<typename T>
	struct numeric_limits_traits : public std::numeric_limits<T> {};
}


namespace spook {
	inline namespace cmath {
		inline namespace constant {


			template<typename T = double>
			inline T constexpr π = T(3.1415926535897932384626433832795);
		}

		inline namespace literals {

			SPOOK_CONSTEVAL auto operator""_radf(long double degree) -> float {
				using ld = long double;

				return float(degree / ld(180.0) * π<ld>);
			}

			SPOOK_CONSTEVAL auto operator""_degf(long double radian) -> float {
				using ld = long double;

				return float(radian / π<ld> * ld(180.0));
			}

			SPOOK_CONSTEVAL auto operator""_rad(long double degree) -> double {
				using ld = long double;

				return double(degree / ld(180.0) * π<ld>);
			}

			SPOOK_CONSTEVAL auto operator""_deg(long double radian) -> double {
				using ld = long double;

				return double(radian / π<ld> * ld(180.0));
			}

			SPOOK_CONSTEVAL auto operator""_radld(long double degree) -> long double {
				using ld = long double;

				return degree / ld(180.0) * π<ld>;
			}

			SPOOK_CONSTEVAL auto operator""_degld(long double radian) -> long double {
				using ld = long double;

				return radian / π<ld> * ld(180.0);
			}
		}

		template<typename T>
		SPOOK_CONSTEVAL auto isinf(T x) -> bool {
			if ((spook::numeric_limits_traits<T>::max)() < x) return true;
			if (x < spook::numeric_limits_traits<T>::lowest()) return true;
			return false;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto isnan(T x) -> bool {
			return !(x == x);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto fabs(T x) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (x == 0.0) return +0.0;
			}
			return (x < 0.0) ? (-x) : (x);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto signbit(T x) -> bool {
			//ゼロの符号判定、定数式じゃ無理？
			//if (x == T(0.0)) {
			//	return (T(1.0) / x) < 0;
			//}

			//can't detect NaN's sign, for compile time...
			//std::bit_cast()...!?

			return x < T(0.0);
		}

		template<typename T>
		SPOOK_CONSTEVAL auto copysign(T x, T y) -> T {
			auto absv = spook::isnan(x) ? spook::numeric_limits_traits<T>::quiet_NaN() : spook::fabs(x);

			return spook::signbit(y) ? -absv : absv;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto ceil(T x) -> T {
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
			if (x < 0.0) {
				return spook::ceil(x);
			}
			else {
				return spook::floor(x);
			}
		}

		template<typename T>
		SPOOK_CONSTEVAL auto remainder(T x, T y) -> T {
			auto n = spook::trunc(x / y);

			return x - n * y;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto fmod(T x, T y) -> T {
			y = spook::fabs(y);
			auto r = spook::remainder(spook::fabs(x) , y);
			if (spook::signbit(r)) r += y;

			return spook::copysign(r, x);
		}

		namespace detail {
			
			/**
			* @brief 三角関数の入力を[0, π]の範囲に収める
			* @param theta θ[rad]
			* @return {[0, π]に収めたθ, 象限の情報（πの奇数倍の時true）}
			*/
			template<typename T>
			SPOOK_CONSTEVAL auto reduce_theta(T theta) -> std::pair<T, bool> {
				auto x = spook::fabs(theta);

				if (0.0 <= x && x < constant::π<T>) {
					//ごちゃごちゃ計算する必要はない
					return { x, false };
				}

				//実質的にはこれ、ただし商も欲しかったので展開している
				//spook::fmod(spook::fabs(theta), constant::π<T>);

				auto n = spook::trunc(spook::fabs(x) / constant::π<T>);
				auto r = x - n * constant::π<T>;
				if (spook::signbit(r)) r += constant::π<T>;

				//象限の情報を得る、余りがゼロということはπの整数倍の時
				//bool isodd = (r == 0.0) ? false : spook::fmod(n, T(2.0)) == T(1.0);

				//[0, π]に押し込めた数と象限の情報
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

			//πの整数倍の時
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

			//π/2の整数倍の時
			if (theta == 0.5 * constant::π<T>) return 0.0;

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

			//π/2の整数倍の時
			if (theta == 0.5 * constant::π<T>) return spook::numeric_limits_traits<T>::infinity();

			auto sin_v = spook::sin(theta);
			auto cos_v = spook::cos(theta);

			auto tan = sin_v / cos_v;

			return spook::signbit(arg) ? -tan : tan;
		}

		template<typename T>
		SPOOK_CONSTEVAL auto exp(T x) -> T {
			if (spook::numeric_limits_traits<T>::is_iec559) {
				if (x == T(0.0)) return T(1.0);
				if (isinf(x)) {
					if (x < T(0.0)) return T(+0.0);
					return x;
				}
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

			return series;
		}

	}
}
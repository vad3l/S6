#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>
#include <type_traits>
#include <numeric>

namespace phy {	

	/*
	 * A unit defined in terms of the base units
	 */
	template<int Metre, int Kilogram, int Second, int Ampere, int Kelvin, int Mole, int Candela>
	struct Unit {
		static constexpr int metre = Metre;
		static constexpr int kilogram = Kilogram;
		static constexpr int second = Second;
		static constexpr int ampere = Ampere;
		static constexpr int kelvin = Kelvin;
		static constexpr int mole = Mole;
		static constexpr int candela = Candela;
	};

	/*
	 * Various type aliases
	*/

	using Metre	= Unit<1,0,0,0,0,0,0>;
	using Kilogram	= Unit<0,1,0,0,0,0,0>;
	using Second	= Unit<0,0,1,0,0,0,0>;
	using Ampere	= Unit<0,0,0,1,0,0,0>;
	using Kelvin	= Unit<0,0,0,0,1,0,0>;
	using Mole	= Unit<0,0,0,0,0,1,0>;
	using Candela	= Unit<0,0,0,0,0,0,1>;
	using Radian	= Unit<0,0,0,0,0,0,0>;

	namespace details {
		template<typename R1, typename R2>
		using RealRatio = typename std::conditional<
					std::gcd(R1::den, R2::den) != 1,
					typename std::conditional<std::ratio_less<R1, R2>::value,
						R1,
						R2
					>::type,
					typename std::ratio<R1::num * R2::num, R1::den * R2::den>
				>::type;

		template<typename U1, typename U2>
		using MulUnit = Unit<U1::metre + U2::metre, U1::kilogram + U2::kilogram, U1::second + U2::second, U1::ampere + U2::ampere, U1::kelvin + U2::kelvin, U1::mole + U2::mole, U1::candela + U2::candela>;

		template<typename U1, typename U2>
		using DivUnit = Unit<U1::metre - U2::metre, U1::kilogram - U2::kilogram, U1::second - U2::second, U1::ampere - U2::ampere, U1::kelvin - U2::kelvin, U1::mole - U2::mole, U1::candela - U2::candela>;
	}

	/*
	 * A quantity is a value associated with a unit and a ratio
	 */
	template<class U, class R = std::ratio<1>>
	struct Qty {
		using Unit = U;
		using Ratio = R;

		intmax_t value;

		Qty();
		Qty(intmax_t v) {
			value = v;
		}

		template<typename ROther>
		Qty& operator+=(Qty<U, ROther> other) {
			value += other.value * (ROther::num / ROther::den);
			return *this;
		}

		template<typename ROther>
		Qty& operator-=(Qty<U, ROther> other) {
			value -= other.value * (ROther::num / ROther::den);		
			return *this;
		}
	};

	/*
	 * Various quantities
	 */

	using Length = Qty<Metre>;
	using Mass =Qty<Kilogram>;
	using Time = Qty<Second>;
	using Current = Qty<Ampere>;
	using Temperature = Qty<Kelvin>;
	using Amount = Qty<Mole>;
	using LuminousIntensity = Qty<Candela>;

	/*
	 * Some weird quantities
	 */

	using Mile = Qty<Metre,std::ratio<1609344, 1000>>;
	using Yard = Qty<Metre,std::ratio<9144, 10000>>;
	using Foot = Qty<Metre,std::ratio<3048, 10000>>;
	using Inch = Qty<Metre,std::ratio<254, 10000>>;

	/*
	 * Comparison operators
	 */

	template<typename U, typename R1, typename R2>
	bool operator==(Qty<U, R1> q1, Qty<U, R2> q2) {
		return q1.value * (R1::num / R1::den) == q2.value * (R2::num / R2::den);
	}

	template<typename U, typename R1, typename R2>
	bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2) {
		return !(q1 == q2);
	}

	template<typename U, typename R1, typename R2>
	bool operator<(Qty<U, R1> q1, Qty<U, R2> q2) {
		return q1.value * (R1::num / R1::den) < q2.value * (R2::num / R2::den);
	}

	template<typename U, typename R1, typename R2>
	bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2) {
		return q1.value * (R1::num / R1::den) <= q2.value * (R2::num / R2::den);
	}

	template<typename U, typename R1, typename R2>
	bool operator>(Qty<U, R1> q1, Qty<U, R2> q2) {
		return q1.value * (R1::num / R1::den) > q2.value * (R2::num / R2::den);
	}

	template<typename U, typename R1, typename R2>
	bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2) {
		return q1.value * (R1::num / R1::den) >= q2.value * (R2::num / R2::den);
	}

	/*
	 * Arithmetic operators
	 */

	template<typename U, typename R1, typename R2>
	Qty<U, details::RealRatio<R1, R2>> operator+(Qty<U, R1> q1, Qty<U, R2> q2) {
		return Qty<U, details::RealRatio<R1, R2>>(q1.value * R2::den + q2.value * R1::den);
	}

	template<typename U, typename R1, typename R2>
	Qty<U, details::RealRatio<R1, R2>> operator-(Qty<U, R1> q1, Qty<U, R2> q2) {
		return Qty<U, details::RealRatio<R1, R2>>(q1.value * R2::den - q2.value * R1::den);
	}

	template<typename U1, typename R1, typename U2, typename R2>
	Qty<details::MulUnit<U1, U2>, details::RealRatio<R1, R2>> operator*(Qty<U1, R1> q1, Qty<U2, R2> q2) {
		return Qty<details::MulUnit<U1, U2>, details::RealRatio<R1, R2>>(q1.value * R2::den + q2.value * R1::den);
	}

	template<typename U1, typename R1, typename U2, typename R2>
	Qty<details::DivUnit<U1, U2>, details::RealRatio<R1, R2>> operator/(Qty<U1, R1> q1, Qty<U2, R2> q2) { 
		return Qty<details::MulUnit<U1, U2>, details::RealRatio<R1, R2>>(q1.value * R2::den - q2.value * R1::den);
	}


	/*
	 * Cast function between two quantities
	 */
	template<typename ResQty, typename U, typename R>
	ResQty qtyCast(Qty<U,R>);
	namespace literals {

		/*
		 * Some user-defined literals
		 */

		Length operator "" _metres(unsigned long long int val) {
			return Length((intmax_t)val);
		}

		Mass operator "" _kilograms(unsigned long long int val) {
			return Mass((intmax_t)val);
		}

		Time operator "" _seconds(unsigned long long int val) {
			return Time((intmax_t)val);
		}

		Current operator "" _amperes(unsigned long long int val) {
			return Current((intmax_t)val);
		}

		Temperature operator "" _kelvins(unsigned long long int val) {
			return Temperature((intmax_t)val);
		}

		Amount operator "" _moles(unsigned long long int val) {
			return Amount((intmax_t)val);
		}

		LuminousIntensity operator "" _candelas(unsigned long long int val) {
			return LuminousIntensity((intmax_t)val);
		}

		/*
		 * Temperature literals
		 */

		Qty<Kelvin,std::ratio<1,100>> operator "" _celsius(unsigned long long int val) {
			return Qty<Kelvin,std::ratio<1,100>>((intmax_t)(val*100+27315));
		}
		Qty<Kelvin,std::ratio<1,1000>> operator "" _fahrenheit(unsigned long long int val) {
			return Qty<Kelvin,std::ratio<1,1000>>((intmax_t)((val*1000. + 459670)* 5/9.f));
		}

	}	

}

#endif // UNITS_H

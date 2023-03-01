#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>
#include <type_traits>

namespace phy {	


	namespace details {
		template<typename R1, typename R2>
		using MinoRatio = typename std::conditional<(R1::num/R1::den)<(R2::num/R2::den), R1, R2>::type;
	}

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

	using Mile = Qty<Metre,std::ratio<1609344, 1000>>;;
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
	Qty<U,details::MinoRatio<R1,R2>> operator+(Qty<U, R1> q1, Qty<U, R2> q2) {
		float temp1 = R1::num/R1::den;
		float temp2 = R2::num/R2::den;

		if (temp1 < temp2) {
			Qty<U,details::MinoRatio<R1,R2>> newe1(q1.value+q2.value*temp2);
			return newe1;	
		}
		
		Qty<U,details::MinoRatio<R1,R2>> newe2(q1.value+q2.value*temp1);
		return newe2;
	}

	template<typename U, typename R1, typename R2>
	Qty<U, R1> operator-(Qty<U, R1> q1, Qty<U, R2> q2) { return q1; }

	template<typename U1, typename R1, typename U2, typename R2>
	Qty<U2, R1> operator*(Qty<U1, R1> q1, Qty<U2, R2> q2) { return q1; }

	template<typename U1, typename R1, typename U2, typename R2>
	Qty<U1, R1> operator/(Qty<U1, R1> q1, Qty<U2, R2> q2) { 
		q1.value = q1.value/q2.value;
		return  q1;
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

		Kelvin operator "" _celsius(unsigned long long int val);
		Kelvin operator "" _fahrenheit(unsigned long long int val);

	}	

}

#endif // UNITS_H

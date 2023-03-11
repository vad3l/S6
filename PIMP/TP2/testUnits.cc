#include "Units.h"

#include <iostream>
#include <gtest/gtest.h>

using namespace phy::literals;

// Metre
TEST(QtyMetre, Add) {
	auto metre = 1_metres;
	EXPECT_EQ(2_metres, metre += 1_metres);
}

TEST(QtyMetre, Sub) {
	auto metre = 2_metres;
	EXPECT_EQ(1_metres, metre -= 1_metres);
}

TEST(QtyMetre, Superior) {
	EXPECT_TRUE(3_metres > 1_metres);
}

TEST(QtyMetre, Inferior) {
	EXPECT_TRUE(1_metres < 3_metres);
}

TEST(QtyMetre, Different) {
	EXPECT_TRUE(1_metres != 50_metres);
}

TEST(QtyMetre, Equal) {
	EXPECT_TRUE(10_metres == 10_metres);
}

TEST(QtyMetre, EqualDifferentsRatioCm){
	phy::Qty<phy::Metre, std::ratio<1,100>> cm(100);
	EXPECT_TRUE(1_metres == cm);
}

TEST(QtyMetre, EqualDifferentsRatioKm){
	phy::Qty<phy::Metre, std::ratio<1000,1>> km(1);
	EXPECT_TRUE(1000_metres == km);
}

// Masse
TEST(QtyKilogram, KilogramAdd) {
	auto kg = 1_kilograms;
	EXPECT_EQ(2_kilograms, kg += 1_kilograms);
}

TEST(QtyKilogram, KilogramSub) {
	auto kg = 2_kilograms;
	EXPECT_EQ(1_kilograms, kg -= 1_kilograms);
}

TEST( QtyKilogram, KilogramSuperior) {
	EXPECT_TRUE(3_kilograms > 1_kilograms);
}

TEST(QtyKilogram, KilogramInferior) {
	EXPECT_TRUE(1_kilograms < 3_kilograms);
}

TEST(QtyKilogram, KilogramDifferent) {
	EXPECT_TRUE(1_kilograms != 50_kilograms);
}

TEST(QtyKilogram, KilogramEqual) {
	EXPECT_TRUE(10_kilograms == 10_kilograms);
}

// Temps
TEST(QtySeconds, SecondsAdd) {
	auto sec = 1_seconds;
	EXPECT_EQ(2_seconds, sec += 1_seconds);
}

TEST(QtySeconds, SecondsSub) {
	auto sec = 2_seconds;
	EXPECT_EQ(1_seconds, sec -= 1_seconds);
}

TEST(QtySeconds, SecondsSuperior) {
	EXPECT_TRUE(3_seconds > 1_seconds);
}

TEST(QtySeconds, SecondsInferior) {
	EXPECT_TRUE(1_seconds < 3_seconds);
}

TEST(QtySeconds, SecondsDifferent) {
	EXPECT_TRUE(1_seconds != 50_seconds);
}

TEST(QtySeconds, SecondsEqual) {
	EXPECT_TRUE(10_seconds == 10_seconds);
}

// Current
TEST(QtyAmpere, AmpereAdd) {
	auto am = 1_amperes;
	EXPECT_EQ(2_amperes, am += 1_amperes);
}

TEST(QtyAmpere, AmpereSub) {
	auto am = 2_amperes;
	EXPECT_EQ(1_amperes, am -= 1_amperes);
}

TEST(QtyAmpere, AmpereSuperior) {
	EXPECT_TRUE(3_amperes > 1_amperes);
}

TEST(QtyAmpere, AmpereInferior) {
	EXPECT_TRUE(1_amperes < 3_amperes);
}

TEST(QtyAmpere, AmpereDifferent) {
	EXPECT_TRUE(1_amperes != 50_amperes);
}

TEST(QtyAmpere, AmpereEqual) {
	EXPECT_TRUE(10_amperes == 10_amperes);
}

// Temperature
TEST(QtyKelvin, KelvinAdd) {
	auto kev = 1_kelvins;
	EXPECT_EQ(2_kelvins, kev += 1_kelvins);
}

TEST(QtyKelvin, KelvinSub) {
	auto kev = 2_kelvins;
	EXPECT_EQ(1_kelvins, kev -= 1_kelvins);
}

TEST(QtyKelvin, KelvinSuperior) {
	EXPECT_TRUE(3_kelvins > 1_kelvins);
}

TEST(QtyKelvin, KelvinInferior) {
	EXPECT_TRUE(1_kelvins < 3_kelvins);
}

TEST(QtyKelvin, KelvinDifferent) {
	EXPECT_TRUE(1_kelvins != 50_kelvins);
}

TEST(QtyKelvin, KelvinEqual) {
	EXPECT_TRUE(10_kelvins == 10_kelvins);
}

// Quantity
TEST(QtyMoles, MolesAdd) {
	auto mol = 1_moles;
	EXPECT_EQ(2_moles, mol += 1_moles);
}

TEST(QtyMoles, MolesSub) {
	auto mol = 2_moles;
	EXPECT_EQ(1_moles, mol -= 1_moles);
}

TEST(QtyMoles, MolesSuperior) {
	EXPECT_TRUE(3_moles > 1_moles);
}

TEST(QtyMoles, MolesInferior) {
	EXPECT_TRUE(1_moles < 3_moles);
}

TEST(QtyMoles, MolesDifferent) {
	EXPECT_TRUE(1_moles != 50_moles);
}

TEST(QtyMoles, MolesEqual) {
	EXPECT_TRUE(10_moles == 10_moles);
}

// Candelas
TEST(QtyCandelas, CandelasAdd) {
	auto mol = 1_candelas;
	EXPECT_EQ(2_candelas, mol += 1_candelas);
}

TEST(QtyCandelas, CandelasSub) {
	auto mol = 2_candelas;
	EXPECT_EQ(1_candelas, mol -= 1_candelas);
}

TEST(QtyCandelas, CandelasSuperior) {
	EXPECT_TRUE(3_candelas > 1_candelas);
}

TEST(QtyCandelas, CandelasInferior) {
	EXPECT_TRUE(1_candelas < 3_candelas);
}

TEST(QtyCandelas, CandelasDifferent) {
	EXPECT_TRUE(1_candelas != 50_candelas);
}

TEST(QtyCandelas, CandelasEqual) {
	EXPECT_TRUE(10_candelas == 10_candelas);
}

TEST(OperatorPlus, PrimeRatio) {
	phy::Qty<phy::Metre, std::ratio<1, 10>> dm(5);
	phy::Qty<phy::Metre, std::ratio<1>> m(1);
	auto newqty = m + dm;
	EXPECT_EQ(15, newqty.value);
	EXPECT_EQ(1, decltype(newqty)::Ratio::num);
	EXPECT_EQ(10, decltype(newqty)::Ratio::den);
}

TEST(OperatorPlus, MultiRatio) {
	phy::Qty<phy::Metre, std::ratio<1, 5>> dm(5);
	phy::Qty<phy::Metre, std::ratio<1, 3>> m(1);
	auto newqty = m + dm;
	EXPECT_EQ(20, newqty.value);
	EXPECT_EQ(1, decltype(newqty)::Ratio::num);
	EXPECT_EQ(15, decltype(newqty)::Ratio::den);
}

TEST(OperatorPlus, Metres) {
	phy::Qty<phy::Metre, std::ratio<1>> dm(5);
	phy::Qty<phy::Metre, std::ratio<1, 10>> m(1);
	auto newqty = m + dm;
	EXPECT_EQ(51, newqty.value);
	EXPECT_EQ(1, decltype(newqty)::Ratio::num);
	EXPECT_EQ(10, decltype(newqty)::Ratio::den);
}

// Operator -
TEST(OperatorMoin, PrimeRatio) {
	phy::Qty<phy::Metre, std::ratio<1, 10>> dm(5);
	phy::Qty<phy::Metre, std::ratio<1>> m(1);
	auto newqty = m - dm;
	EXPECT_EQ(5, newqty.value);
	EXPECT_EQ(1, decltype(newqty)::Ratio::num);
	EXPECT_EQ(10, decltype(newqty)::Ratio::den);
}

TEST(OperatorMoin, MultiRatio) {
	phy::Qty<phy::Metre, std::ratio<1, 5>> dm(5);
	phy::Qty<phy::Metre, std::ratio<1, 3>> m(1);
	auto newqty = m - dm;
	EXPECT_EQ(20, newqty.value);
	EXPECT_EQ(1, decltype(newqty)::Ratio::num);
	EXPECT_EQ(15, decltype(newqty)::Ratio::den);
}

TEST(OperatorMoin, Metres) {
	phy::Qty<phy::Metre, std::ratio<1>> dm(5);
	phy::Qty<phy::Metre, std::ratio<1, 10>> m(1);
	auto newqty = m - dm;
	EXPECT_EQ(51, newqty.value);
	EXPECT_EQ(1, decltype(newqty)::Ratio::num);
	EXPECT_EQ(10, decltype(newqty)::Ratio::den);
}

// Celsius
TEST(QtyCelsuis, CelsiusZero) {
	auto c = 0_celsius;
	EXPECT_EQ(27315,c.value);
}

TEST(QtyCelsuis, CelsiusSunTemp) {
	auto c = 5505_celsius;
	EXPECT_EQ(577815,c.value);
}

// Fahrenheit
TEST(QtyFahrenheit, FahrenheitZero) {
	auto c = 0_fahrenheit;
	EXPECT_EQ(255372,c.value);
}

TEST(QtyFahrenheit, FahrenheitSunTemp) {
	auto c = 9941_fahrenheit;
	EXPECT_EQ(5778150,c.value);
}

// TEMPERATURE EXPERIENCE 
TEST(QtyTemperature, TemperatureAddCelsiusFahrenheitZero) {
	auto f = 0_fahrenheit;
	auto c = 0_celsius;
	auto add = c+f;
	std::cout << "F°" << f.value << " ratio :" << decltype(f)::Ratio::den << "\nC°"  << c.value << " ratio :" << decltype(c)::Ratio::den << "\nres : " << add.value << " ratio :" << decltype(add)::Ratio::den << std::endl;
	
	EXPECT_EQ(282687,add.value);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include "Units.h"

#include <iostream>
#include <gtest/gtest.h>

using namespace phy::literals;

TEST(Metre ,Add) {
	auto metre = 1_metres;
	EXPECT_EQ(2_metres, metre += 1_metres);
}

TEST(Metre, Sub) {
	auto metre = 2_metres;
	EXPECT_EQ(1_metres, metre -= 1_metres);
}

TEST(Velocity, Create) {
	//auto velocity = 100000_metres / 3600_seconds; // 100km/h
	auto metre = 1_metres;
	phy::Mile miles(45);
	auto oui = miles + metre; 
	std::cout << oui.value << std::endl;	
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

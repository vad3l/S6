#include "Units.h"

#include <iostream>
#include <gtest/gtest.h>

using namespace phy::literals;

TEST(Qty, MileToYard) {
	auto metre = 1_metres;
	metre += 2_metres;

	auto velocity = 100000_metres / 3600_seconds;
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

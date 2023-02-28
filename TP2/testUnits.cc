#include "Units.h"

#include <iostream>
#include <gtest/gtest.h>

using namespace phy::literals;

TEST(Qty, MileToYard) {
	auto metre = 1_metres;
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

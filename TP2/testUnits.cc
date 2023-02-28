#include "Units.h"

#include <iostream>
#include <gtest/gtest.h>

using namespace phy::literals;

TEST(Qty, MetreAdd) {
	auto metre = 1_metres;
	EXPECT_EQ(2_metres, metre += 1_metres);
}

TEST(Qty, MetreSub) {
	auto metre = 2_metres;
	EXPECT_EQ(1_metres, metre -= 1_metres);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include "Signal.h"

#include <gtest/gtest.h>

TEST (Cours, Cours) {
	sig::Signal<void(int)> s;
	int res = 0;
	s.connectSlot([&res](int x) { res += x; });
	s.connectSlot([&res](int x) { res += x; });
	s.emitSignal(1);
	EXPECT_EQ(res, 2);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

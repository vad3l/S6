#include "Signal.h"

#include <gtest/gtest.h>

TEST (DiscardCombiner, Example) {
	sig::Signal<void(int)> s;
	int res = 0;
	s.connectSlot([&res](int x) { res += x; });
	s.connectSlot([&res](int x) { res += x; });
	s.emitSignal(1);
	EXPECT_EQ(res, 2);
}

TEST (DiscardCombiner, VariadicVariation) {
	sig::Signal<void(int, double, float)> s;
	double res = 0;
	s.connectSlot([&res](int x, double y, float z) { res += x + y + z; });
	s.connectSlot([&res](int x, double y, float z) { res += x + y + z; });
	s.emitSignal(5, 5.0, 5.f);
	EXPECT_EQ(res, 30.0);
}


TEST (LastCombiner, Classic) {
	sig::Signal<int(void), sig::LastCombiner<int>> s;
	s.connectSlot([]() { return 1; });
	s.connectSlot([]() { return 20; });
	int res = s.emitSignal();
	EXPECT_EQ(res, 20);
}

TEST (LastCombiner, String) {
	sig::Signal<std::string(void), sig::LastCombiner<std::string>> s;
	s.connectSlot([]() { return std::string("nul"); });
	s.connectSlot([]() { return std::string("cool"); });
	std::string res = s.emitSignal();
	EXPECT_EQ(res, "cool");
}

TEST (VectorCombiner, Classic) {
	sig::Signal<int(void), sig::VectorCombiner<int>> s;
	s.connectSlot([]() { return 1; });
	s.connectSlot([]() { return 20; });
	auto res = s.emitSignal();
	std::vector<int> expected = { 1, 20 };
	EXPECT_EQ(res, expected);
}

TEST (VectorCombiner, String) {
	sig::Signal<std::string(void), sig::VectorCombiner<std::string>> s;
	s.connectSlot([]() { return "cool"; });
	s.connectSlot([]() { return "cool"; });
	auto res = s.emitSignal();
	std::vector<std::string> expected = { "cool", "cool" };
	EXPECT_EQ(res, expected);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

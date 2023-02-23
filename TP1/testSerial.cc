#include "Serial.h"
#include <gtest/gtest.h>

#include <filesystem>

using namespace serial;

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Uint8, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint8_t)5 ;
	}

	IBinaryFile file = IBinaryFile(path);
	uint8_t i;
	file >> i;
	EXPECT_EQ((uint8_t)5, i);
}

TEST(Int8, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int8_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	int8_t i;
	file >> i;
	EXPECT_EQ(5, i);
}

TEST(Uint16, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint16_t)5 ;
	}

	IBinaryFile file = IBinaryFile(path);
	uint16_t i;
	file >> i;
	EXPECT_EQ((uint16_t)5, i);
}

TEST(Int16, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int16_t)5 ;
	}

	IBinaryFile file = IBinaryFile(path);
	int16_t i;
	file >> i;
	EXPECT_EQ(5, i);
}

TEST(Uint32, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint32_t)5 ;
	}

	IBinaryFile file = IBinaryFile(path);
	uint32_t i;
	file >> i;
	EXPECT_EQ((uint32_t)5, i);
}

TEST(Int32, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int32_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	int32_t i;
	file >> i;
	EXPECT_EQ(5, i);
}

TEST(Uint64, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint64_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	uint64_t i;
	file >> i;
	EXPECT_EQ((uint64_t)5, i);
}

TEST(Int64, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int64_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	int64_t i;
	file >> i;
	EXPECT_EQ(5, i);
}

TEST(Char, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << 'a' ;
	}
	IBinaryFile file = IBinaryFile(path);
	char a;
	file >> a;
	EXPECT_EQ('a', a);
}

TEST(Float, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << float(5.f) ;
	}
	IBinaryFile file = IBinaryFile(path);
	float f;
	file >> f;
	EXPECT_EQ(5.f, f);
}

TEST(Double, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << double(5.0) ;
	}
	IBinaryFile file = IBinaryFile(path);
	double d;
	file >> d;
	EXPECT_EQ(5.0, d);
}

TEST(Bool, BinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << true ;
	}
	IBinaryFile file = IBinaryFile(path);
	bool b;
	file >> b;
	EXPECT_EQ(true, b);
}

TEST(String, BinaryFile) {
	std::string a = "Banger";
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << a;
	}

	IBinaryFile file = IBinaryFile(path);
	std::string s;
	file >> s ;
	EXPECT_EQ(a,s); 
}

TEST(Vector, BinaryFile) {
	std::vector<int32_t> v;
	v.push_back(5); v.push_back(8);
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << v;
	}

	IBinaryFile file = IBinaryFile(path);
	std::vector<int32_t> r;
	file >> r;
	EXPECT_EQ((size_t)2, r.size());
	EXPECT_EQ(5, r[0]);
	EXPECT_EQ(8, r[1]);
}

TEST(Map, BinaryFile) {
	std::map<int32_t, char> m;
	m.insert({ 5, 'a' });
	m.insert({ 15, 'y' });

	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << m;
	}

	IBinaryFile file = IBinaryFile(path);
	std::map<int32_t, char> r;
	file >> r;
	EXPECT_EQ((size_t)2, r.size());
	EXPECT_EQ('a', r[5]);
	EXPECT_EQ('y', r[15]);
}

TEST(Array, BinaryFile) {
	std::array<char, 2> m;
	m[0] = 'j';
	m[1] = 'e';

	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << m;
	}

	IBinaryFile file = IBinaryFile(path);
	std::array<char, 2> r;
	file >> r;
	EXPECT_EQ((size_t)2, r.size());
	EXPECT_EQ('j', r[0]);
	EXPECT_EQ('e', r[1]);
}

TEST(Set, BinaryFile) {
	std::set<uint8_t> s;
	s.insert(7);
	s.insert(8);
	s.insert(9);
	s.insert(97);
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << s;
	}

	IBinaryFile file = IBinaryFile(path);
	std::set<uint8_t> r;
	file >> r;
	EXPECT_EQ((size_t)4, r.size());
	EXPECT_EQ(7, *r.begin());
	EXPECT_EQ(97, *(std::prev(r.end())));
}


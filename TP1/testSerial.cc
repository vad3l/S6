#include "Serial.h"
#include <gtest/gtest.h>

#include <filesystem>

using namespace serial;

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Constructor , OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile fileToWrite = OBinaryFile(path,OBinaryFile::Mode::Truncate);

		std::byte toWrite{ 'A' };
		fileToWrite.write(&toWrite,sizeof(std::byte));
	
	}
	IBinaryFile fileToRead = IBinaryFile(path); 

	std::byte toRead{255};
	std::size_t size = fileToRead.read(&toRead, sizeof(std::byte));
	EXPECT_EQ(size,sizeof(std::byte));
	EXPECT_EQ('A', static_cast<char>(toRead));
}


TEST(OperatorUnit, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint8_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(uint8_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(uint8_t));
	EXPECT_EQ(size, sizeof(uint8_t));

	uint8_t new_uint8_te;
	std::memcpy(&new_uint8_te, reading, sizeof(uint8_t));
	EXPECT_EQ(5, new_uint8_te);	
}

TEST(OperatorInt8, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int8_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(int8_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(int8_t));
	EXPECT_EQ(size, sizeof(int8_t));

	int8_t new_int8_te;
	std::memcpy(&new_int8_te, reading, sizeof(int8_t));
	EXPECT_EQ(5, new_int8_te);	
}

TEST(OperatorUint16, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint16_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(uint16_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(uint16_t));
	EXPECT_EQ(size, sizeof(uint16_t));

	uint16_t new_uint16_te;
	std::memcpy(&new_uint16_te, reading, sizeof(uint16_t));
	EXPECT_EQ(5, new_uint16_te);	
}

TEST(OperatorInt16, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int16_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(int16_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(int16_t));
	EXPECT_EQ(size, sizeof(int16_t));

	int16_t new_int16_te;
	std::memcpy(&new_int16_te, reading, sizeof(int16_t));
	EXPECT_EQ(5, new_int16_te);	
}

TEST(OperatorUint32, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint32_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(uint32_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(uint32_t));
	EXPECT_EQ(size, sizeof(uint32_t));

	uint32_t new_uint32_t_te;
	std::memcpy(&new_uint32_t_te, reading, sizeof(uint32_t));
	EXPECT_EQ((uint32_t)5, new_uint32_t_te);	
}

TEST(OperatorInt32, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int32_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(int32_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(int32_t));
	EXPECT_EQ(size, sizeof(int32_t));

	int32_t new_int32_t_te;
	std::memcpy(&new_int32_t_te, reading, sizeof(int32_t));
	EXPECT_EQ(5, new_int32_t_te);	
}

TEST(OperatorUint64, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (uint64_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(uint64_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(uint64_t));
	EXPECT_EQ(size, sizeof(uint64_t));

	uint64_t new_uint64_t_t_te;
	std::memcpy(&new_uint64_t_t_te, reading, sizeof(uint64_t));
	EXPECT_EQ((uint64_t)5, new_uint64_t_t_te);	
}

TEST(OperatorInt64, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int64_t)5 ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(int64_t)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(int64_t));
	EXPECT_EQ(size, sizeof(int64_t));

	int64_t new_int64_te;
	std::memcpy(&new_int64_te, reading, sizeof(int64_t));
	EXPECT_EQ((int64_t)5, new_int64_te);	
}

TEST(OperatorChar, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << 'a' ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(char)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(char));
	EXPECT_EQ(size, sizeof(char));

	char new_a = static_cast<char>(reading[0]);
	EXPECT_EQ('a', new_a);
}

TEST(OperatorFloat, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << float(5.f) ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(float)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(float));
	EXPECT_EQ(size, sizeof(float));

	float new_float_te;
	std::memcpy(&new_float_te, reading, sizeof(float));
	EXPECT_EQ(5.f, new_float_te);	
}

TEST(OperatorDouble, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << double(5.0) ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(double)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(double));
	EXPECT_EQ(size, sizeof(double));

	double new_double_te;
	std::memcpy(&new_double_te, reading, sizeof(double));
	EXPECT_EQ(5.0, new_double_te);	
}

TEST(OperatorBool, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << true ;
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[sizeof(bool)];
	std::size_t size = file.read(reading, sizeof(std::byte) * sizeof(bool));
	EXPECT_EQ(size, sizeof(bool));

	bool boole;
	std::memcpy(&boole, reading, sizeof(bool));
	EXPECT_EQ(true, boole);	
}

TEST(OperatorString, OBinaryFile) {
	std::string a = "Banger";
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << a;
	}

	IBinaryFile file = IBinaryFile(path);
	std::string s ;

	file >> s ;
	EXPECT_EQ(a,s); 
}
	
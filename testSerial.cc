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
	std::size_t size = fileToRead.read(&toRead,sizeof(std::byte));
	EXPECT_EQ(size,sizeof(std::byte));
	std::cout << static_cast<char>(toRead) << std::endl;
}

TEST(Operator, OBinaryFile) {
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << (int32_t)5 << 5.f << 'a';
	}
	IBinaryFile file = IBinaryFile(path);
	std::byte reading[4 + 4 + 1];
	std::size_t size = file.read(reading, sizeof(std::byte) * (4 + 4 + 1));
	EXPECT_EQ(size, sizeof(std::byte) * (4 + 4 + 1));
	std::cout << static_cast<char>(reading[8]) << std::endl;
}

TEST(String, OBinaryFile) {
	std::string a = "Banger";
	std::string path((std::string)std::filesystem::temp_directory_path() + "/pmp.bin");
	{
		OBinaryFile file = OBinaryFile(path, OBinaryFile::Mode::Truncate);
		file << a;
	}

	IBinaryFile file = IBinaryFile(path);
	std::byte reading[a.size() + 1];
	std::size_t size = file.read(reading, a.size() + 1);
	char new_a[a.size() + 1];
	std::memcpy(new_a, reading, a.size() + 1);
	EXPECT_EQ(size, a.size() + 1);
	std::cout << new_a << std::endl;
}


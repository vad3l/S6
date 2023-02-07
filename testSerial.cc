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

		//const char bytes[] = { 72, 101, 108, 108, 111 };
		std::byte toWrite{65};
		fileToWrite.write(&toWrite,sizeof(std::byte));
	
	}
	IBinaryFile fileToRead = IBinaryFile(path); 

	std::byte toRead{255};
	std::size_t size = fileToRead.read(&toRead,sizeof(std::byte));
	EXPECT_EQ(size,sizeof(std::byte));

	std::cout << static_cast<char>(toRead) << std::endl;

}
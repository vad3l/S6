#include "Serial.h"

#include <stdexcept>
#include <iostream>
#include <cstring>

namespace serial {

	OBinaryFile::OBinaryFile(const std::string& filename,OBinaryFile::Mode mode)
	:m_file(fopen(filename.c_str(),(mode == Mode::Truncate ? "wb" : "ab")))
	{
		if (m_file == nullptr) {
			throw std::runtime_error("Error while trying to open binary files :"+filename);
		}
	}	

	OBinaryFile::~OBinaryFile(){
		fclose(m_file);
	}

	std::size_t OBinaryFile::write(const std::byte* data, std::size_t size){
		return std::fwrite(data,sizeof(std::byte),size,m_file);
	}

	IBinaryFile::IBinaryFile(const std::string& filename)
	:m_file(fopen(filename.c_str(),"rb"))
	{
		if (m_file == nullptr) {
			throw std::runtime_error("Error while trying to open binary files :"+filename);
		}
	}

/*	OBinaryFile& operator<<(OBinaryFile& file, int32_t x) {
		std::byte integer[4];
		std::memcpy(integer, &x, sizeof(x));
		file.write(integer, 4);
		return file;
	}

	OBinaryFile& operator<<(OBinaryFile& file, char x) {
		std::byte character{ x };
		file.write(&character, 1);
		return file;
	}
*/

	IBinaryFile::~IBinaryFile(){
		fclose(m_file);
	}

	std::size_t IBinaryFile::read(std::byte* data, std::size_t size){
		return std::fread(data,sizeof(std::byte),size,m_file);
	}
}

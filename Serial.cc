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

/*
	OBinaryFile& operator<<(OBinaryFile& file, int8_t x);
	OBinaryFile& operator<<(OBinaryFile& file, uint16_t x);
	OBinaryFile& operator<<(OBinaryFile& file, int16_t x);
	OBinaryFile& operator<<(OBinaryFile& file, uint32_t x);
	OBinaryFile& operator<<(OBinaryFile& file, int32_t x);
	OBinaryFile& operator<<(OBinaryFile& file, uint64_t x);
	OBinaryFile& operator<<(OBinaryFile& file, int64_t x);
	OBinaryFile& operator<<(OBinaryFile& file, char x);
	OBinaryFile& operator<<(OBinaryFile& file, float x);
	OBinaryFile& operator<<(OBinaryFile& file, double x);
	OBinaryFile& operator<<(OBinaryFile& file, bool x);
*/
	OBinaryFile& operator<<(OBinaryFile& file, const std::string& x) {
		std::byte bytes[x.size() + 1];
		std::memcpy(bytes, x.c_str(), x.size() + 1);
		file.write(bytes, x.size() + 1);
		return file;
	}

	IBinaryFile::~IBinaryFile(){
		fclose(m_file);
	}

	std::size_t IBinaryFile::read(std::byte* data, std::size_t size){
		return std::fread(data,sizeof(std::byte),size,m_file);
	}
}

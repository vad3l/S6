#include "Serial.h"

#include <stdexcept>
#include <iostream>
#include <cstring>

namespace serial {

	template<typename T>
	OBinaryFile& generic_writer (OBinaryFile& file, T x) {
		std::byte bytes[sizeof(T)];
		std::memcpy(bytes, &x, sizeof(T));
		file.write(bytes, sizeof(T));
		return file;
	}

	template<typename T>
	IBinaryFile& generic_reader (IBinaryFile& file, T& x) {
		std::byte bytes[sizeof(T)];
		file.read(bytes, sizeof(T));
		std::memcpy(&x, bytes, sizeof(T));
		return file;
	}

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

	OBinaryFile& operator<<(OBinaryFile& file, const std::string& x) {
		std::byte bytes[x.size() + 1];
		std::memcpy(bytes, x.c_str(), x.size() + 1);
		file.write(bytes, x.size() + 1);
		return file;
	}

	OBinaryFile& operator<<(OBinaryFile& file, uint8_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, int8_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, uint16_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, int16_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, uint32_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, int32_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, uint64_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, int64_t x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, char x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, float x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, double x) {
		return generic_writer(file, x);
	}

	OBinaryFile& operator<<(OBinaryFile& file, bool x) {
		return generic_writer(file, x);
	}

	IBinaryFile::~IBinaryFile(){
		fclose(m_file);
	}

	std::size_t IBinaryFile::read(std::byte* data, std::size_t size){
		return std::fread(data,sizeof(std::byte),size,m_file);
	}

	IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, int16_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, int32_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, int64_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, char& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, float& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, double& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, bool& x) {
		return generic_reader(file, x);
	}

	IBinaryFile& operator>>(IBinaryFile& file, std::string& x) {
		std::byte character;
		while (size_t readed = file.read(&character, sizeof(char))) {
			x += static_cast<char>(character);
		}
		return file;
	}
}

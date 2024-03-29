#ifndef SERIAL_H
#define SERIAL_H

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <array>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <iostream>
#include <ostream>
namespace serial {

	/**
	 * @brief A file to be written
	 */
	class OBinaryFile {
	public:
		/**
		 * @brief The mode for opening the file
		 */
		enum Mode {
			Truncate,
			Append,
		};

		/**
		 * @brief Constructor
		 *
		 * Opens the file for writing or throws a `std::runtime_error` in case of
		 * error.
		 */
		OBinaryFile(const std::string& filename, Mode mode = Truncate);

		OBinaryFile(const OBinaryFile&) = delete;
		OBinaryFile(OBinaryFile&& other) noexcept;

		OBinaryFile& operator=(const OBinaryFile&) = delete;
		OBinaryFile& operator=(OBinaryFile&& other) noexcept;

		/**
		 * @brief Closes the file
		 */
		~OBinaryFile();

		/**
		 * @brief Write `size` bytes pointed by `data` in the file
		 *
		 * Returns the number of bytes actually written
		 */
		std::size_t write(const std::byte* data, std::size_t size);
	private :
		FILE *m_file;
	};

	/**
	 * @brief A file to be read
	 */
	class IBinaryFile {
	public:
		/**
		 * @brief Constructor
		 *
		 * Opens the file for reading or throws a `std::runtime_error` in case of
		 * error.
		 */
		IBinaryFile(const std::string& filename);

		IBinaryFile(const IBinaryFile&) = delete;
		IBinaryFile(IBinaryFile&& other) noexcept;

		IBinaryFile& operator=(const IBinaryFile&) = delete;
		IBinaryFile& operator=(IBinaryFile&& other) noexcept;

		/**
		 * @brief Closes the file
		 */
		~IBinaryFile();

		/**
		 * @brief Read `size` bytes from the file and store them in the buffer
		 * pointed by `data`.
		 *
		 * Returns the number of bytes actually read.
		 */
		std::size_t read(std::byte* data, std::size_t size);
	private :
		FILE *m_file;
	};

	OBinaryFile& operator<<(OBinaryFile& file, uint8_t x);
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
	OBinaryFile& operator<<(OBinaryFile& file, const std::string& x);

	template<typename T>
	OBinaryFile& operator<<(OBinaryFile& file, const std::vector<T>& x) {
		file << x.size();
		for (size_t i = 0; i < x.size(); i++) {
			file << x[i];
		}
		return file;
	}

	template<typename T, std::size_t N>
	OBinaryFile& operator<<(OBinaryFile& file, const std::array<T,N>& x) {
		for (size_t i = 0; i < N; i++) {
			file << x[i];
		}
		return file;
	}

	template<typename K, typename V>
	OBinaryFile& operator<<(OBinaryFile& file, const std::map<K,V>& x) {
		file << x.size();
		for (auto const& [key, val] : x) {
			file << key << val;
		}
		return file;
	}

	template<typename T>
	OBinaryFile& operator<<(OBinaryFile& file, const std::set<T>& x) {
		file << x.size();
		for (const T &v : x) {
			file << v;
		}
		return file;
	}

	IBinaryFile& operator>>(IBinaryFile& file, int8_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, int16_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, int32_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, int64_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x);
	IBinaryFile& operator>>(IBinaryFile& file, char& x);
	IBinaryFile& operator>>(IBinaryFile& file, float& x);
	IBinaryFile& operator>>(IBinaryFile& file, double& x);
	IBinaryFile& operator>>(IBinaryFile& file, bool& x);
	IBinaryFile& operator>>(IBinaryFile& file, std::string& x);

	template<typename T>
	IBinaryFile& operator>>(IBinaryFile& file, std::vector<T>& x) {
		size_t size;
		file >> size;

		std::byte tab[sizeof(T)];
		for (size_t i = 0 ; i < size ; ++i) { 
			if (size_t readed = file.read(tab, sizeof(T))) {
				T value;
				std::memcpy(&value, tab, sizeof(T));
				x.push_back(value);
			}
		}
		return file;
	}

	template<typename T, std::size_t N>
	IBinaryFile& operator>>(IBinaryFile& file, std::array<T, N>& x) {
		for (size_t i = 0; i < N; i++) {
			T value;
			file >> value;
			x[i] = value;
		}
		return file;
	}

	template<typename K, typename V>
	IBinaryFile& operator>>(IBinaryFile& file, std::map<K, V>& x) {
		size_t size;
		file >> size;

		std::byte tab[sizeof(V) + sizeof(K)];
		for (size_t i = 0 ; i < size ; ++i) { 
			if (size_t readed = file.read(tab, sizeof(V) + sizeof(K))) {
				K key;
				V value;
				std::memcpy(&key, tab, sizeof(K));
				std::memcpy(&value, &tab[sizeof(K)], sizeof(V));
				x.insert({ key, value });
			}
		}
		return file;
	}

	template<typename T>
	IBinaryFile& operator>>(IBinaryFile& file, std::set<T>& x) {
		size_t size;
		file >> size;

		std::byte tab[sizeof(T)];
		for (size_t i = 0 ; i < size ; ++i) {
			if (size_t readed = file.read(tab, sizeof(T))) {
				T value;
				std::memcpy(&value, tab, sizeof(T));
				x.insert(value);
			}	
		}
		return file;
	}

} // namespace serial

#endif // SERIAL_H

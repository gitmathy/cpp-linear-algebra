/// Part of the project "cpp-linear-algebra"
///
/// @file la/util/file_io.hpp
/// @brief Definition file io operations in this project
/// @author Gitmathy, https://github.com/gitmathy
///
/// @copyright Copyright (c) 2026. All rights reserved.
/// Licensed under the MIT License (see LICENSE file in project root).

#ifndef LA_UTIL_FILE_IO_HPP
#define LA_UTIL_FILE_IO_HPP

#include "la/util/error.hpp"
#include "la/util/macros.hpp"
#include "la/util/types.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <type_traits>

namespace la {
namespace util {

/// @brief Writing things to a file
class file_writer
{
private:
    /// @brief Outputfile
    std::ofstream p_ofs;

    /// @brief Write binary or text
    bool p_binary;

    /// @brief Filename for error reporting and logging
    std::string p_filename;

public:
    /// @brief Open the file and be ready to write stuff
    inline file_writer(const std::string &filename, const bool binary);

    /// @brief Close the file
    inline ~file_writer() { p_ofs.close(); }

    /// @brief Append content to thee file
    /// @tparam T type of every element
    /// @param what what to write (reference or pointer)
    /// @param size number of elements
    template <typename T>
    void append(const T &what, const size_type size = 1);
};

/// @brief Reading things to a file
class file_reader
{
private:
    /// @brief Outputfile
    std::ifstream p_ifs;

    /// @brief Write binary or text
    bool p_binary;

    /// @brief Filename for error reporting and logging
    std::string p_filename;

public:
    /// @brief Open the file and be ready to write stuff
    inline file_reader(const std::string &filename, const bool binary);

    /// @brief Close the file
    inline ~file_reader() { p_ifs.close(); }

    /// @brief Get content to thee file
    /// @tparam T type of every element
    /// @param where to store the result (pointer or reference)
    /// @param size number of elements
    template <typename T>
    void get(T &where, const size_type size = 1);
};

// ===============================================
// G L O B A L   F U N C T I O N S
// ===============================================

/// @brief Delete a file
inline bool delete_file(const std::string &filename);

// ===============================================
// T E M P L A T E   I M P L E M E N T A T I O N S
// ===============================================

inline file_writer::file_writer(const std::string &filename, const bool binary)
    : p_ofs(filename, binary ? std::ios::out : std::ios::binary | std::ios::out), p_binary(binary),
      p_filename(filename)
{
    LOG_DEBUG("Opened file '" << p_filename << "' for write");
    if (!p_ofs) {
        LOG_ERROR("Failed to open file '" << p_filename << "' for write");
        util::error_factory("Cannot open file for write", __FUNCTION_NAME__, FILE_ERROR);
    }
}

template <typename T>
void file_writer::append(const T &what, const size_type size)
{
    LOG_TRACE("Writing elements of size " << size << "into file '" << p_filename << "'");
    if (p_binary) {
        if constexpr (std::is_pointer<T>()) {
            // binary mode: array of elements
            p_ofs.write(reinterpret_cast<const char *>(what), size * sizeof(*what));
        } else {
            // binary mode: single element
            p_ofs.write(reinterpret_cast<const char *>(&what), sizeof(T));
        }
    } else {
        if constexpr (std::is_pointer<T>()) {
            // text mode: array of elements
            for (size_type i = 0; i < size; ++i) {
                p_ofs << what[i] << ' ';
            }
        } else {
            // text mode: single element
            p_ofs << what << ' ';
        }
    }
    if (!p_ofs) {
        LOG_ERROR("Failed to write file '" << p_filename << "' for write");
        util::error_factory("Cannot open file for write", __FUNCTION_NAME__, FILE_ERROR);
    }
}

inline file_reader::file_reader(const std::string &filename, const bool binary)
    : p_ifs(filename, binary ? std::ios::in : std::ios::binary | std::ios::in), p_binary(binary),
      p_filename(filename)
{
    LOG_DEBUG("Opened file '" << filename << "' for read");
    if (!p_ifs) {
        LOG_ERROR("Failed to open file '" << filename << "' for read");
        util::error_factory("Cannot open file for read", __FUNCTION_NAME__, FILE_ERROR);
    }
}

template <typename T>
void file_reader::get(T &where, const size_type size)
{
    LOG_TRACE("Reading elements of size " << size << "from file '" << p_filename << "'");
    if (p_binary) {
        if constexpr (std::is_pointer<T>()) {
            // binary mode: array of elements
            p_ifs.read(reinterpret_cast<char *>(where), size * sizeof(*where));
        } else {
            // binary mode: single element
            p_ifs.read(reinterpret_cast<char *>(&where), sizeof(T));
        }
    } else {
        if constexpr (std::is_pointer<T>()) {
            // text mode: array of elements
            for (T it = where; it != where + size; ++it) {
                if (!(p_ifs >> *it)) {
                    LOG_ERROR("Reading text file failed due to I/O error");
                    util::error_factory("Cannot read text data.", __FUNCTION_NAME__, FILE_ERROR);
                }
            }
        } else {
            // text mode: single element
            if (!(p_ifs >> where)) {
                LOG_ERROR("Reading text file failed due to I/O error");
                util::error_factory("Cannot read text data.", __FUNCTION_NAME__, FILE_ERROR);
            }
        }
    }
    if (!p_ifs) {
        LOG_ERROR("Reading file failed due to I/O error");
        util::error_factory("Cannot read text data.", __FUNCTION_NAME__, FILE_ERROR);
    }
}

inline bool delete_file(const std::string &filename)
{
    std::cout << "Deleting " << filename << std::endl;
    try {
        if (!std::filesystem::remove(filename)) {
            util::error_factory("Cannot delete file", __FUNCTION_NAME__, FILE_ERROR);
        }
        return false;
    } catch (const std::filesystem::filesystem_error &) {
        LOG_ERROR("Failed to delete  file");
        util::error_factory("Cannot delete file", __FUNCTION_NAME__, FILE_ERROR);
    }
}

} // namespace util
} // namespace la

#endif

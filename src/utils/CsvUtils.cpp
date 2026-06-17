/**
 * @file CsvUtils.cpp
 * @brief Shared CSV parsing and file preparation utilities implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "CsvUtils.h"

#include <filesystem>
#include <ios>
#include <limits>
#include <system_error>

namespace SCMS {
namespace Persistence {

bool CsvUtils::ensureParentDirectory(const std::string& filePath) {
    if (filePath.empty()) {
        return false;
    }

    const std::filesystem::path path(filePath);
    const std::filesystem::path parent = path.parent_path();
    if (parent.empty()) {
        return true;
    }

    std::error_code error;
    std::filesystem::create_directories(parent, error);
    return !error;
}

bool CsvUtils::ensureFile(const std::string& filePath,
                          const std::string& header) {
    if (!ensureParentDirectory(filePath)) {
        return false;
    }

    std::error_code error;
    const bool exists = std::filesystem::exists(filePath, error);
    if (error) {
        return false;
    }

    const bool empty = !exists
        || std::filesystem::file_size(filePath, error) == 0U;
    if (error) {
        return false;
    }
    if (!empty) {
        return true;
    }

    std::ofstream output(filePath, std::ios::out | std::ios::trunc);
    if (!output) {
        return false;
    }
    output << header << '\n';
    return output.good();
}

bool CsvUtils::openOutput(std::ofstream& output,
                          const std::string& filePath,
                          const std::string& header,
                          bool append) {
    if (!ensureParentDirectory(filePath)) {
        return false;
    }

    std::error_code error;
    const bool exists = std::filesystem::exists(filePath, error);
    if (error) {
        return false;
    }
    const bool hasContent = exists
        && std::filesystem::file_size(filePath, error) > 0U;
    if (error) {
        return false;
    }

    const std::ios::openmode mode = std::ios::out
        | (append ? std::ios::app : std::ios::trunc);
    output.open(filePath, mode);
    if (!output) {
        return false;
    }

    if (!append || !hasContent) {
        output << header << '\n';
    }
    return output.good();
}

std::string CsvUtils::escape(const std::string& value) {
    std::string escaped;
    escaped.reserve(value.size() + 2U);
    escaped.push_back('"');
    for (const char character : value) {
        if (character == '"') {
            escaped.push_back('"');
        }
        escaped.push_back(character);
    }
    escaped.push_back('"');
    return escaped;
}

std::vector<std::string> CsvUtils::parseLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool quoted = false;

    for (std::size_t index = 0U; index < line.size(); ++index) {
        const char character = line[index];
        if (quoted) {
            if (character == '"') {
                if (index + 1U < line.size() && line[index + 1U] == '"') {
                    field.push_back('"');
                    ++index;
                } else {
                    quoted = false;
                }
            } else {
                field.push_back(character);
            }
        } else if (character == '"') {
            quoted = true;
        } else if (character == ',') {
            fields.push_back(field);
            field.clear();
        } else if (character != '\r') {
            field.push_back(character);
        }
    }

    if (quoted) {
        return {};
    }
    fields.push_back(field);
    return fields;
}

bool CsvUtils::parseInt(const std::string& value, int& result) {
    try {
        std::size_t processed = 0U;
        const long parsed = std::stol(value, &processed);
        if (processed != value.size()
            || parsed < std::numeric_limits<int>::min()
            || parsed > std::numeric_limits<int>::max()) {
            return false;
        }
        result = static_cast<int>(parsed);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool CsvUtils::parseFloat(const std::string& value, float& result) {
    try {
        std::size_t processed = 0U;
        const float parsed = std::stof(value, &processed);
        if (processed != value.size()) {
            return false;
        }
        result = parsed;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool CsvUtils::parseDouble(const std::string& value, double& result) {
    try {
        std::size_t processed = 0U;
        const double parsed = std::stod(value, &processed);
        if (processed != value.size()) {
            return false;
        }
        result = parsed;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool CsvUtils::parseBool(const std::string& value, bool& result) {
    if (value == "1" || value == "true" || value == "TRUE") {
        result = true;
        return true;
    }
    if (value == "0" || value == "false" || value == "FALSE") {
        result = false;
        return true;
    }
    return false;
}

}  // namespace Persistence
}  // namespace SCMS

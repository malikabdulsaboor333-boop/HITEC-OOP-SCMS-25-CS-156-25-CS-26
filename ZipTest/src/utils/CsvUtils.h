/**
 * @file CsvUtils.h
 * @brief Shared CSV parsing and file preparation utilities
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_UTILS_CSV_UTILS_H
#define SCMS_UTILS_CSV_UTILS_H

#include <fstream>
#include <string>
#include <vector>

namespace SCMS {
namespace Persistence {

class CsvUtils {
public:
    static bool ensureParentDirectory(const std::string& filePath);
    static bool ensureFile(const std::string& filePath,
                           const std::string& header);
    static bool openOutput(std::ofstream& output,
                           const std::string& filePath,
                           const std::string& header,
                           bool append);

    static std::string escape(const std::string& value);
    static std::vector<std::string> parseLine(const std::string& line);

    static bool parseInt(const std::string& value, int& result);
    static bool parseFloat(const std::string& value, float& result);
    static bool parseDouble(const std::string& value, double& result);
    static bool parseBool(const std::string& value, bool& result);

private:
    CsvUtils() = delete;
};

}  // namespace Persistence
}  // namespace SCMS

#endif

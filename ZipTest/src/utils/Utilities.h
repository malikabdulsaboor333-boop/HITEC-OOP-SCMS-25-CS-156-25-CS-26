/**
 * @file Utilities.h
 * @brief Reusable utility manager declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_UTILS_UTILITIES_H
#define SCMS_UTILS_UTILITIES_H

#include <memory>
#include <string>

namespace SCMS {
namespace Utils {

class UtilityManager {
public:
    UtilityManager();

    static std::string formatString(const std::string& label,
                                    const std::string& value);
    static bool validateNumericInput(const std::string& input);
    static bool validateEmail(const std::string& email);
    static bool validateCNIC(const std::string& cnic);
    static bool validatePhone(const std::string& phone);
    static std::string getCurrentDate();
    static std::string getCurrentTimestamp();
    static std::string toUpperCase(const std::string& input);
    static std::string toLowerCase(const std::string& input);
    static std::string trimWhitespace(const std::string& input);

    static std::shared_ptr<UtilityManager> createShared();
};

}  // namespace Utils
}  // namespace SCMS

#endif

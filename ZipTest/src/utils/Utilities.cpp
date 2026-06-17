/**
 * @file Utilities.cpp
 * @brief Reusable utility manager implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Utilities.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace SCMS {
namespace Utils {

UtilityManager::UtilityManager() = default;

std::string UtilityManager::formatString(const std::string& label,
                                         const std::string& value) {
    constexpr int labelWidth = 24;
    std::ostringstream formatted;
    formatted << std::left << std::setw(labelWidth) << label << ": " << value;
    return formatted.str();
}

bool UtilityManager::validateNumericInput(const std::string& input) {
    const std::string trimmedInput = trimWhitespace(input);
    if (trimmedInput.empty()) {
        return false;
    }

    std::size_t processedCharacters = 0U;
    try {
        const double value = std::stod(trimmedInput, &processedCharacters);
        return processedCharacters == trimmedInput.size()
            && std::isfinite(value);
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool UtilityManager::validateEmail(const std::string& email) {
    constexpr std::size_t nextCharacterOffset = 1U;

    const std::string trimmedEmail = trimWhitespace(email);
    const std::size_t atPosition = trimmedEmail.find('@');
    if (atPosition == std::string::npos
        || atPosition == 0U
        || atPosition + nextCharacterOffset >= trimmedEmail.size()
        || trimmedEmail.find('@', atPosition + nextCharacterOffset)
            != std::string::npos) {
        return false;
    }

    const std::size_t dotPosition = trimmedEmail.find(
        '.', atPosition + nextCharacterOffset);
    const bool containsWhitespace = std::any_of(
        trimmedEmail.begin(),
        trimmedEmail.end(),
        [](unsigned char character) {
            return std::isspace(character) != 0;
        });

    return dotPosition != std::string::npos
        && dotPosition > atPosition + nextCharacterOffset
        && dotPosition + nextCharacterOffset < trimmedEmail.size()
        && !containsWhitespace;
}

bool UtilityManager::validateCNIC(const std::string& cnic) {
    constexpr std::size_t cnicLength = 15U;
    constexpr std::size_t firstDashPosition = 5U;
    constexpr std::size_t secondDashPosition = 13U;

    if (cnic.size() != cnicLength
        || cnic[firstDashPosition] != '-'
        || cnic[secondDashPosition] != '-') {
        return false;
    }

    return std::all_of(
        cnic.begin(),
        cnic.end(),
        [firstDashPosition, secondDashPosition, index = std::size_t{0}](
            char character) mutable {
            const bool isDashPosition = index == firstDashPosition
                || index == secondDashPosition;
            const bool validCharacter = isDashPosition
                ? character == '-'
                : std::isdigit(static_cast<unsigned char>(character)) != 0;
            ++index;
            return validCharacter;
        });
}

bool UtilityManager::validatePhone(const std::string& phone) {
    constexpr std::size_t localPhoneLength = 11U;
    constexpr std::size_t internationalPhoneLength = 13U;
    constexpr std::size_t prefixPosition = 0U;
    constexpr std::size_t internationalDigitStart = 1U;
    constexpr std::size_t localDigitStart = 0U;

    std::string normalizedPhone;
    std::copy_if(
        phone.begin(),
        phone.end(),
        std::back_inserter(normalizedPhone),
        [](char character) {
            return character != ' '
                && character != '-'
                && character != '('
                && character != ')';
        });

    const bool localFormat = normalizedPhone.size() == localPhoneLength
        && normalizedPhone.rfind("03", prefixPosition) == prefixPosition;
    const bool internationalFormat =
        normalizedPhone.size() == internationalPhoneLength
        && normalizedPhone.rfind("+923", prefixPosition) == prefixPosition;

    if (!localFormat && !internationalFormat) {
        return false;
    }

    const std::size_t digitStart = internationalFormat
        ? internationalDigitStart
        : localDigitStart;
    return std::all_of(
        normalizedPhone.begin()
            + static_cast<std::string::difference_type>(digitStart),
        normalizedPhone.end(),
        [](char character) {
            return std::isdigit(static_cast<unsigned char>(character)) != 0;
        });
}

std::string UtilityManager::getCurrentDate() {
    const auto currentTime = std::chrono::system_clock::now();
    const std::time_t currentTimeValue =
        std::chrono::system_clock::to_time_t(currentTime);
    std::tm localTime {};

#ifdef _WIN32
    if (localtime_s(&localTime, &currentTimeValue) != 0) {
        return {};
    }
#else
    if (localtime_r(&currentTimeValue, &localTime) == nullptr) {
        return {};
    }
#endif

    std::ostringstream date;
    date << std::put_time(&localTime, "%Y-%m-%d");
    return date.str();
}

std::string UtilityManager::getCurrentTimestamp() {
    const auto currentTime = std::chrono::system_clock::now();
    const std::time_t currentTimeValue =
        std::chrono::system_clock::to_time_t(currentTime);
    std::tm localTime {};

#ifdef _WIN32
    if (localtime_s(&localTime, &currentTimeValue) != 0) {
        return {};
    }
#else
    if (localtime_r(&currentTimeValue, &localTime) == nullptr) {
        return {};
    }
#endif

    std::ostringstream timestamp;
    timestamp << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return timestamp.str();
}

std::string UtilityManager::toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(
        result.begin(),
        result.end(),
        result.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::toupper(character));
        });
    return result;
}

std::string UtilityManager::toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(
        result.begin(),
        result.end(),
        result.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::tolower(character));
        });
    return result;
}

std::string UtilityManager::trimWhitespace(const std::string& input) {
    const auto firstCharacter = std::find_if(
        input.begin(),
        input.end(),
        [](unsigned char character) {
            return std::isspace(character) == 0;
        });

    if (firstCharacter == input.end()) {
        return {};
    }

    const auto lastCharacter = std::find_if(
        input.rbegin(),
        input.rend(),
        [](unsigned char character) {
            return std::isspace(character) == 0;
        }).base();

    return std::string(firstCharacter, lastCharacter);
}

std::shared_ptr<UtilityManager> UtilityManager::createShared() {
    return std::make_shared<UtilityManager>();
}

}  // namespace Utils
}  // namespace SCMS

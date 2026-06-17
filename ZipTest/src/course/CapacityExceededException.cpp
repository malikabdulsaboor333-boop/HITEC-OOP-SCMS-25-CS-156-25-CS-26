/**
 * @file CapacityExceededException.cpp
 * @brief Course capacity exception implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "CapacityExceededException.h"

CapacityExceededException::CapacityExceededException(const std::string& message)
    : EnrollmentException(message) {
}

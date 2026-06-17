/**
 * @file EnrollmentException.cpp
 * @brief EnrollmentException class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Custom exception handling and inheritance.
 */

#include "EnrollmentException.h"

EnrollmentException::EnrollmentException(const std::string& message)
    : std::runtime_error(message) {
}

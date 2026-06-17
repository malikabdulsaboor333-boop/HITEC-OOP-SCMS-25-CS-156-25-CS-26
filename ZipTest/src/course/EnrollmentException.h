/**
 * @file EnrollmentException.h
 * @brief EnrollmentException class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Custom exception handling and inheritance.
 */

#ifndef SCMS_COURSE_ENROLLMENT_EXCEPTION_H
#define SCMS_COURSE_ENROLLMENT_EXCEPTION_H

#include <stdexcept>
#include <string>

class EnrollmentException : public std::runtime_error {
public:
    explicit EnrollmentException(const std::string& message);
};

#endif

/**
 * @file CapacityExceededException.h
 * @brief Course capacity exception declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_COURSE_CAPACITY_EXCEEDED_EXCEPTION_H
#define SCMS_COURSE_CAPACITY_EXCEEDED_EXCEPTION_H

#include "EnrollmentException.h"

#include <string>

class CapacityExceededException : public EnrollmentException {
public:
    explicit CapacityExceededException(const std::string& message);
};

#endif

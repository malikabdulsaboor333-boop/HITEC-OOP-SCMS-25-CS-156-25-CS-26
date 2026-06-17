/**
 * @file OverdueException.h
 * @brief Library overdue exception declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_LIBRARY_OVERDUE_EXCEPTION_H
#define SCMS_LIBRARY_OVERDUE_EXCEPTION_H

#include <stdexcept>
#include <string>

class OverdueException : public std::runtime_error {
public:
    explicit OverdueException(const std::string& message);
};

#endif

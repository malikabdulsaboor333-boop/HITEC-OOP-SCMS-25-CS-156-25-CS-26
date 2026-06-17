/**
 * @file OverdueException.cpp
 * @brief Library overdue exception implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "OverdueException.h"

OverdueException::OverdueException(const std::string& message)
    : std::runtime_error(message) {
}

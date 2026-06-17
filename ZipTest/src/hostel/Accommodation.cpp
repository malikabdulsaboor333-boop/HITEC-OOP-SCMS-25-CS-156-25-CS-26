/**
 * @file Accommodation.cpp
 * @brief Accommodation abstract interface implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Accommodation.h"

Accommodation::Accommodation() = default;

Accommodation::Accommodation(const std::string& newEntityId)
    : BaseEntity(newEntityId) {
}

Accommodation::~Accommodation() = default;

/**
 * @file Reportable.cpp
 * @brief Reportable abstract interface implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Reportable.h"

Reportable::Reportable() = default;

Reportable::Reportable(const std::string& newEntityId)
    : BaseEntity(newEntityId) {
}

Reportable::~Reportable() = default;

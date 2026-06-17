/**
 * @file BaseEntity.cpp
 * @brief BaseEntity abstract class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "BaseEntity.h"

#include <stdexcept>

BaseEntity::BaseEntity()
    : entityId(defaultEntityId) {
}

BaseEntity::BaseEntity(const std::string& newEntityId)
    : entityId(newEntityId) {
    if (entityId.empty()) {
        throw std::invalid_argument("Entity ID cannot be empty.");
    }
}

BaseEntity::~BaseEntity() = default;

const std::string& BaseEntity::getEntityId() const {
    return entityId;
}

void BaseEntity::setEntityId(const std::string& newEntityId) {
    if (newEntityId.empty()) {
        throw std::invalid_argument("Entity ID cannot be empty.");
    }

    entityId = newEntityId;
}

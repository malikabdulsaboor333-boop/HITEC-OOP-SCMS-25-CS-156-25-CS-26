/**
 * @file BaseEntity.h
 * @brief BaseEntity abstract class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_HOSTEL_BASE_ENTITY_H
#define SCMS_HOSTEL_BASE_ENTITY_H

#include <string>

class BaseEntity {
public:
    BaseEntity();
    explicit BaseEntity(const std::string& newEntityId);
    virtual ~BaseEntity();

    const std::string& getEntityId() const;
    void setEntityId(const std::string& newEntityId);

    virtual void displayInfo() const = 0;

private:
    static constexpr const char* defaultEntityId = "DEFAULT_HOSTEL_ENTITY";

    std::string entityId;
};

#endif

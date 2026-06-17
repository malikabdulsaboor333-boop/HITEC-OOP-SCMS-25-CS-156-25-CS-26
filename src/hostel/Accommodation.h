/**
 * @file Accommodation.h
 * @brief Accommodation abstract interface declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_HOSTEL_ACCOMMODATION_H
#define SCMS_HOSTEL_ACCOMMODATION_H

#include "BaseEntity.h"

#include <string>

class Accommodation : virtual public BaseEntity {
public:
    Accommodation();
    explicit Accommodation(const std::string& newEntityId);
    ~Accommodation() override;

    virtual bool allocateRoom(const std::string& blockName,
                              const std::string& roomNumber,
                              const std::string& studentRollNo) = 0;
    virtual bool vacateRoom(const std::string& blockName,
                            const std::string& roomNumber,
                            const std::string& studentRollNo) = 0;
};

#endif

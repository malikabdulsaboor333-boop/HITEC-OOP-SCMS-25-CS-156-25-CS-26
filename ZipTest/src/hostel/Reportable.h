/**
 * @file Reportable.h
 * @brief Reportable abstract interface declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_HOSTEL_REPORTABLE_H
#define SCMS_HOSTEL_REPORTABLE_H

#include "BaseEntity.h"

#include <string>

class Reportable : virtual public BaseEntity {
public:
    Reportable();
    explicit Reportable(const std::string& newEntityId);
    ~Reportable() override;

    virtual void generateReport() const = 0;
};

#endif

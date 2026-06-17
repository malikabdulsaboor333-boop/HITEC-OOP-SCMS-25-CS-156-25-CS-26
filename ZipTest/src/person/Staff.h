/**
 * @file Staff.h
 * @brief Staff class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Single inheritance, encapsulation, constructor chaining,
 * runtime polymorphism, virtual dispatch, and method overriding.
 */

#ifndef SCMS_PERSON_STAFF_H
#define SCMS_PERSON_STAFF_H

#include "Person.h"

#include <string>

class Staff : public Person {
public:
    Staff();
    Staff(const std::string& newName,
          const std::string& newCnic,
          int newAge,
          const std::string& newContact,
          const std::string& newEmployeeId,
          const std::string& newRole,
          double newSalary);
    ~Staff() override;

    const std::string& getEmployeeId() const;
    const std::string& getRole() const;
    double getSalary() const;

    void setEmployeeId(const std::string& newEmployeeId);
    void setRole(const std::string& newRole);
    void setSalary(double newSalary);

    void displayInfo() const override;

private:
    void validateStaffData() const;

    static constexpr const char* defaultEmployeeId = "UNASSIGNED_STAFF";
    static constexpr const char* defaultRole = "Unassigned";
    static constexpr double defaultSalary = 1.0;
    static constexpr double minimumSalary = 0.0;

    std::string employeeId;
    std::string role;
    double salary;
};

#endif

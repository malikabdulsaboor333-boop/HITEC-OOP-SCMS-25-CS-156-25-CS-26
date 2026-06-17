/**
 * @file Faculty.h
 * @brief Faculty class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Single inheritance, encapsulation, constructor chaining,
 * runtime polymorphism, virtual dispatch, and method overriding.
 */

#ifndef SCMS_PERSON_FACULTY_H
#define SCMS_PERSON_FACULTY_H

#include "Person.h"

#include <string>

class Faculty : public Person {
public:
    Faculty();
    Faculty(const std::string& newName,
            const std::string& newCnic,
            int newAge,
            const std::string& newContact,
            const std::string& newEmployeeId,
            const std::string& newDesignation,
            double newSalary);
    ~Faculty() override;

    const std::string& getEmployeeId() const;
    const std::string& getDesignation() const;
    double getSalary() const;

    void setEmployeeId(const std::string& newEmployeeId);
    void setDesignation(const std::string& newDesignation);
    void setSalary(double newSalary);

    void displayInfo() const override;

private:
    void validateFacultyData() const;

    static constexpr const char* defaultEmployeeId = "UNASSIGNED_FACULTY";
    static constexpr const char* defaultDesignation = "Unassigned";
    static constexpr double defaultSalary = 1.0;
    static constexpr double minimumSalary = 0.0;

    std::string employeeId;
    std::string designation;
    double salary;
};

#endif

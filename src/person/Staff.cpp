/**
 * @file Staff.cpp
 * @brief Staff class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Single inheritance, encapsulation, constructor chaining,
 * runtime polymorphism, virtual dispatch, and method overriding.
 */

#include "Staff.h"

#include <iostream>
#include <stdexcept>

Staff::Staff()
    : Person(),
      employeeId(defaultEmployeeId),
      role(defaultRole),
      salary(defaultSalary) {
}

Staff::Staff(const std::string& newName,
             const std::string& newCnic,
             int newAge,
             const std::string& newContact,
             const std::string& newEmployeeId,
             const std::string& newRole,
             double newSalary)
    : Person(newName, newCnic, newAge, newContact),
      employeeId(newEmployeeId),
      role(newRole),
      salary(newSalary) {
    validateStaffData();
}

Staff::~Staff() = default;

const std::string& Staff::getEmployeeId() const {
    return employeeId;
}

const std::string& Staff::getRole() const {
    return role;
}

double Staff::getSalary() const {
    return salary;
}

void Staff::setEmployeeId(const std::string& newEmployeeId) {
    if (newEmployeeId.empty()) {
        throw std::invalid_argument("Staff employee ID cannot be empty.");
    }
    employeeId = newEmployeeId;
}

void Staff::setRole(const std::string& newRole) {
    if (newRole.empty()) {
        throw std::invalid_argument("Staff role cannot be empty.");
    }
    role = newRole;
}

void Staff::setSalary(double newSalary) {
    if (newSalary <= minimumSalary) {
        throw std::invalid_argument("Staff salary must be positive.");
    }
    salary = newSalary;
}

void Staff::displayInfo() const {
    std::cout << "Staff Information\n";
    displayPersonInfo();
    std::cout << "Employee ID: " << employeeId << '\n'
              << "Role: " << role << '\n'
              << "Salary: " << salary << '\n';
}

void Staff::validateStaffData() const {
    if (employeeId.empty() || role.empty()) {
        throw std::invalid_argument(
            "Staff employee ID and role cannot be empty.");
    }
    if (salary <= minimumSalary) {
        throw std::invalid_argument("Staff salary must be positive.");
    }
}

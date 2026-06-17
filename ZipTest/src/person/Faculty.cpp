/**
 * @file Faculty.cpp
 * @brief Faculty class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Single inheritance, encapsulation, constructor chaining,
 * runtime polymorphism, virtual dispatch, and method overriding.
 */

#include "Faculty.h"

#include <iostream>
#include <stdexcept>

Faculty::Faculty()
    : Person(),
      employeeId(defaultEmployeeId),
      designation(defaultDesignation),
      salary(defaultSalary) {
}

Faculty::Faculty(const std::string& newName,
                 const std::string& newCnic,
                 int newAge,
                 const std::string& newContact,
                 const std::string& newEmployeeId,
                 const std::string& newDesignation,
                 double newSalary)
    : Person(newName, newCnic, newAge, newContact),
      employeeId(newEmployeeId),
      designation(newDesignation),
      salary(newSalary) {
    validateFacultyData();
}

Faculty::~Faculty() = default;

const std::string& Faculty::getEmployeeId() const {
    return employeeId;
}

const std::string& Faculty::getDesignation() const {
    return designation;
}

double Faculty::getSalary() const {
    return salary;
}

void Faculty::setEmployeeId(const std::string& newEmployeeId) {
    if (newEmployeeId.empty()) {
        throw std::invalid_argument("Faculty employee ID cannot be empty.");
    }
    employeeId = newEmployeeId;
}

void Faculty::setDesignation(const std::string& newDesignation) {
    if (newDesignation.empty()) {
        throw std::invalid_argument("Faculty designation cannot be empty.");
    }
    designation = newDesignation;
}

void Faculty::setSalary(double newSalary) {
    if (newSalary <= minimumSalary) {
        throw std::invalid_argument("Faculty salary must be positive.");
    }
    salary = newSalary;
}

void Faculty::displayInfo() const {
    std::cout << "Faculty Information\n";
    displayPersonInfo();
    std::cout << "Employee ID: " << employeeId << '\n'
              << "Designation: " << designation << '\n'
              << "Salary: " << salary << '\n';
}

void Faculty::validateFacultyData() const {
    if (employeeId.empty() || designation.empty()) {
        throw std::invalid_argument(
            "Faculty employee ID and designation cannot be empty.");
    }
    if (salary <= minimumSalary) {
        throw std::invalid_argument("Faculty salary must be positive.");
    }
}

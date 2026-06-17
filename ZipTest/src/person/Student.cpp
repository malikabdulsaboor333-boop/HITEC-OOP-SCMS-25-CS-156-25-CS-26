/**
 * @file Student.cpp
 * @brief Student class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Single inheritance, encapsulation, constructor chaining,
 * runtime polymorphism, virtual dispatch, and method overriding.
 */

#include "Student.h"

#include <iostream>
#include <stdexcept>

Student::Student()
    : Person(),
      rollNo(defaultRollNo),
      department(defaultDepartment),
      cgpa(defaultCgpa) {
}

Student::Student(const std::string& newName,
                 const std::string& newCnic,
                 int newAge,
                 const std::string& newContact,
                 const std::string& newRollNo,
                 const std::string& newDepartment,
                 float newCgpa)
    : Person(newName, newCnic, newAge, newContact),
      rollNo(newRollNo),
      department(newDepartment),
      cgpa(newCgpa) {
    validateStudentData();
}

Student::~Student() = default;

const std::string& Student::getRollNo() const {
    return rollNo;
}

const std::string& Student::getDepartment() const {
    return department;
}

float Student::getCgpa() const {
    return cgpa;
}

void Student::setRollNo(const std::string& newRollNo) {
    if (newRollNo.empty()) {
        throw std::invalid_argument("Student roll number cannot be empty.");
    }
    rollNo = newRollNo;
}

void Student::setDepartment(const std::string& newDepartment) {
    if (newDepartment.empty()) {
        throw std::invalid_argument("Student department cannot be empty.");
    }
    department = newDepartment;
}

void Student::setCgpa(float newCgpa) {
    if (newCgpa < minimumCgpa || newCgpa > maximumCgpa) {
        throw std::invalid_argument("CGPA must be between 0.0 and 4.0.");
    }
    cgpa = newCgpa;
}

void Student::displayInfo() const {
    std::cout << "Student Information\n";
    displayPersonInfo();
    displayStudentInfo();
}

void Student::displayStudentInfo() const {
    std::cout << "Roll No: " << rollNo << '\n'
              << "Department: " << department << '\n'
              << "CGPA: " << cgpa << '\n';
}

void Student::validateStudentData() const {
    if (rollNo.empty()) {
        throw std::invalid_argument("Student roll number cannot be empty.");
    }
    if (department.empty()) {
        throw std::invalid_argument("Student department cannot be empty.");
    }
    if (cgpa < minimumCgpa || cgpa > maximumCgpa) {
        throw std::invalid_argument("CGPA must be between 0.0 and 4.0.");
    }
}

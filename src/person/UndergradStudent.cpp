/**
 * @file UndergradStudent.cpp
 * @brief UndergradStudent class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Multi-level inheritance, encapsulation, constructor
 * chaining, runtime polymorphism, virtual dispatch, and method overriding.
 */

#include "UndergradStudent.h"

#include <iostream>
#include <stdexcept>

UndergradStudent::UndergradStudent()
    : Student(),
      projectTitle(defaultProjectTitle),
      academicAdvisor(defaultAcademicAdvisor) {
}

UndergradStudent::UndergradStudent(const std::string& newName,
                                   const std::string& newCnic,
                                   int newAge,
                                   const std::string& newContact,
                                   const std::string& newRollNo,
                                   const std::string& newDepartment,
                                   float newCgpa,
                                   const std::string& newProjectTitle,
                                   const std::string& newAcademicAdvisor)
    : Student(newName,
              newCnic,
              newAge,
              newContact,
              newRollNo,
              newDepartment,
              newCgpa),
      projectTitle(newProjectTitle),
      academicAdvisor(newAcademicAdvisor) {
    validateUndergradStudentData();
}

UndergradStudent::~UndergradStudent() = default;

const std::string& UndergradStudent::getProjectTitle() const {
    return projectTitle;
}

const std::string& UndergradStudent::getAcademicAdvisor() const {
    return academicAdvisor;
}

void UndergradStudent::setProjectTitle(const std::string& newProjectTitle) {
    if (newProjectTitle.empty()) {
        throw std::invalid_argument("Project title cannot be empty.");
    }
    projectTitle = newProjectTitle;
}

void UndergradStudent::setAcademicAdvisor(
    const std::string& newAcademicAdvisor) {
    if (newAcademicAdvisor.empty()) {
        throw std::invalid_argument("Academic advisor cannot be empty.");
    }
    academicAdvisor = newAcademicAdvisor;
}

void UndergradStudent::displayInfo() const {
    std::cout << "Undergraduate Student Information\n";
    displayPersonInfo();
    displayStudentInfo();
    std::cout << "Project Title: " << projectTitle << '\n'
              << "Academic Advisor: " << academicAdvisor << '\n';
}

void UndergradStudent::validateUndergradStudentData() const {
    if (projectTitle.empty() || academicAdvisor.empty()) {
        throw std::invalid_argument(
            "Project title and academic advisor cannot be empty.");
    }
}

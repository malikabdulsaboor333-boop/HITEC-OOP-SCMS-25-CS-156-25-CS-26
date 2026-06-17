/**
 * @file GradStudent.cpp
 * @brief GradStudent class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Multi-level inheritance, encapsulation, constructor
 * chaining, runtime polymorphism, virtual dispatch, and method overriding.
 */

#include "GradStudent.h"

#include <iostream>
#include <stdexcept>

GradStudent::GradStudent()
    : Student(),
      researchTopic(defaultResearchTopic),
      supervisor(defaultSupervisor) {
}

GradStudent::GradStudent(const std::string& newName,
                         const std::string& newCnic,
                         int newAge,
                         const std::string& newContact,
                         const std::string& newRollNo,
                         const std::string& newDepartment,
                         float newCgpa,
                         const std::string& newResearchTopic,
                         const std::string& newSupervisor)
    : Student(newName,
              newCnic,
              newAge,
              newContact,
              newRollNo,
              newDepartment,
              newCgpa),
      researchTopic(newResearchTopic),
      supervisor(newSupervisor) {
    validateGradStudentData();
}

GradStudent::~GradStudent() = default;

const std::string& GradStudent::getResearchTopic() const {
    return researchTopic;
}

const std::string& GradStudent::getSupervisor() const {
    return supervisor;
}

void GradStudent::setResearchTopic(const std::string& newResearchTopic) {
    if (newResearchTopic.empty()) {
        throw std::invalid_argument("Research topic cannot be empty.");
    }
    researchTopic = newResearchTopic;
}

void GradStudent::setSupervisor(const std::string& newSupervisor) {
    if (newSupervisor.empty()) {
        throw std::invalid_argument("Supervisor cannot be empty.");
    }
    supervisor = newSupervisor;
}

void GradStudent::displayInfo() const {
    std::cout << "Graduate Student Information\n";
    displayPersonInfo();
    displayStudentInfo();
    std::cout << "Research Topic: " << researchTopic << '\n'
              << "Supervisor: " << supervisor << '\n';
}

void GradStudent::validateGradStudentData() const {
    if (researchTopic.empty() || supervisor.empty()) {
        throw std::invalid_argument(
            "Research topic and supervisor cannot be empty.");
    }
}

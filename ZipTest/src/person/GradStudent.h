/**
 * @file GradStudent.h
 * @brief GradStudent class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Multi-level inheritance, encapsulation, constructor
 * chaining, runtime polymorphism, virtual dispatch, and method overriding.
 */

#ifndef SCMS_PERSON_GRAD_STUDENT_H
#define SCMS_PERSON_GRAD_STUDENT_H

#include "Student.h"

#include <string>

class GradStudent : public Student {
public:
    GradStudent();
    GradStudent(const std::string& newName,
                const std::string& newCnic,
                int newAge,
                const std::string& newContact,
                const std::string& newRollNo,
                const std::string& newDepartment,
                float newCgpa,
                const std::string& newResearchTopic,
                const std::string& newSupervisor);
    ~GradStudent() override;

    const std::string& getResearchTopic() const;
    const std::string& getSupervisor() const;

    void setResearchTopic(const std::string& newResearchTopic);
    void setSupervisor(const std::string& newSupervisor);

    void displayInfo() const override;

private:
    void validateGradStudentData() const;

    static constexpr const char* defaultResearchTopic = "Undeclared Research";
    static constexpr const char* defaultSupervisor = "Unassigned Supervisor";

    std::string researchTopic;
    std::string supervisor;
};

#endif

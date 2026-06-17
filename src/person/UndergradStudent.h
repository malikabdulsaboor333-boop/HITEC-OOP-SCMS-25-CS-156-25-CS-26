/**
 * @file UndergradStudent.h
 * @brief UndergradStudent class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Multi-level inheritance, encapsulation, constructor
 * chaining, runtime polymorphism, virtual dispatch, and method overriding.
 */

#ifndef SCMS_PERSON_UNDERGRAD_STUDENT_H
#define SCMS_PERSON_UNDERGRAD_STUDENT_H

#include "Student.h"

#include <string>

class UndergradStudent : public Student {
public:
    UndergradStudent();
    UndergradStudent(const std::string& newName,
                     const std::string& newCnic,
                     int newAge,
                     const std::string& newContact,
                     const std::string& newRollNo,
                     const std::string& newDepartment,
                     float newCgpa,
                     const std::string& newProjectTitle,
                     const std::string& newAcademicAdvisor);
    ~UndergradStudent() override;

    const std::string& getProjectTitle() const;
    const std::string& getAcademicAdvisor() const;

    void setProjectTitle(const std::string& newProjectTitle);
    void setAcademicAdvisor(const std::string& newAcademicAdvisor);

    void displayInfo() const override;

private:
    void validateUndergradStudentData() const;

    static constexpr const char* defaultProjectTitle = "Undeclared Project";
    static constexpr const char* defaultAcademicAdvisor = "Unassigned Advisor";

    std::string projectTitle;
    std::string academicAdvisor;
};

#endif

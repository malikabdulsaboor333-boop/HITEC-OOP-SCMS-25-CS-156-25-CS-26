/**
 * @file Student.h
 * @brief Student class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Single inheritance, encapsulation, constructor chaining,
 * runtime polymorphism, virtual dispatch, and method overriding.
 */

#ifndef SCMS_PERSON_STUDENT_H
#define SCMS_PERSON_STUDENT_H

#include "Person.h"

#include <string>

class Student : public Person {
public:
    Student();
    Student(const std::string& newName,
            const std::string& newCnic,
            int newAge,
            const std::string& newContact,
            const std::string& newRollNo,
            const std::string& newDepartment,
            float newCgpa);
    ~Student() override;

    const std::string& getRollNo() const;
    const std::string& getDepartment() const;
    float getCgpa() const;

    void setRollNo(const std::string& newRollNo);
    void setDepartment(const std::string& newDepartment);
    void setCgpa(float newCgpa);

    void displayInfo() const override;

protected:
    void displayStudentInfo() const;

private:
    void validateStudentData() const;

    static constexpr const char* defaultRollNo = "UNASSIGNED";
    static constexpr const char* defaultDepartment = "Undeclared";
    static constexpr float defaultCgpa = 0.0F;
    static constexpr float minimumCgpa = 0.0F;
    static constexpr float maximumCgpa = 4.0F;

    std::string rollNo;
    std::string department;
    float cgpa;
};

#endif

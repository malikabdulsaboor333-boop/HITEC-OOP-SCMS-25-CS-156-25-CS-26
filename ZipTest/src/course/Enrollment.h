/**
 * @file Enrollment.h
 * @brief Enrollment class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation, association, and custom exception
 * handling.
 */

#ifndef SCMS_COURSE_ENROLLMENT_H
#define SCMS_COURSE_ENROLLMENT_H

#include <string>

class Student;

class Enrollment {
public:
    Enrollment();
    Enrollment(const std::string& newStudentRollNo,
               const std::string& newCourseCode,
               const std::string& newSemester,
               char newGrade);
    Enrollment(const Student& associatedStudent,
               const std::string& newCourseCode,
               const std::string& newSemester,
               char newGrade);

    const std::string& getStudentRollNo() const;
    const std::string& getCourseCode() const;
    const std::string& getSemester() const;
    char getGrade() const;
    const Student* getStudent() const;

    void setStudentRollNo(const std::string& newStudentRollNo);
    void setCourseCode(const std::string& newCourseCode);
    void setSemester(const std::string& newSemester);
    void setGrade(char newGrade);
    void associateStudent(const Student& associatedStudent);
    void clearStudentAssociation();

    void displayEnrollmentInfo() const;
    void validate() const;

private:
    static bool isValidGrade(char candidateGrade);

    static constexpr const char* defaultStudentRollNo = "UNASSIGNED_STUDENT";
    static constexpr const char* defaultCourseCode = "UNASSIGNED_COURSE";
    static constexpr const char* defaultSemester = "UNASSIGNED_SEMESTER";
    static constexpr char defaultGrade = 'N';

    std::string studentRollNo;
    std::string courseCode;
    std::string semester;
    char grade;
    const Student* student;
};

#endif

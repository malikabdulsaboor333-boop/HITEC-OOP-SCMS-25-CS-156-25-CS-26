/**
 * @file Enrollment.cpp
 * @brief Enrollment class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation, association, and custom exception
 * handling.
 */

#include "Enrollment.h"

#include "EnrollmentException.h"
#include "../person/Student.h"

#include <iostream>

Enrollment::Enrollment()
    : Enrollment(defaultStudentRollNo,
                 defaultCourseCode,
                 defaultSemester,
                 defaultGrade) {
}

Enrollment::Enrollment(const std::string& newStudentRollNo,
                       const std::string& newCourseCode,
                       const std::string& newSemester,
                       char newGrade)
    : studentRollNo(newStudentRollNo),
      courseCode(newCourseCode),
      semester(newSemester),
      grade(newGrade),
      student(nullptr) {
    validate();
}

Enrollment::Enrollment(const Student& associatedStudent,
                       const std::string& newCourseCode,
                       const std::string& newSemester,
                       char newGrade)
    : Enrollment(associatedStudent.getRollNo(),
                 newCourseCode,
                 newSemester,
                 newGrade) {
    associateStudent(associatedStudent);
}

const std::string& Enrollment::getStudentRollNo() const {
    return studentRollNo;
}

const std::string& Enrollment::getCourseCode() const {
    return courseCode;
}

const std::string& Enrollment::getSemester() const {
    return semester;
}

char Enrollment::getGrade() const {
    return grade;
}

const Student* Enrollment::getStudent() const {
    return student;
}

void Enrollment::setStudentRollNo(const std::string& newStudentRollNo) {
    if (newStudentRollNo.empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: student roll number cannot be empty.");
    }

    studentRollNo = newStudentRollNo;
    student = nullptr;
}

void Enrollment::setCourseCode(const std::string& newCourseCode) {
    if (newCourseCode.empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: course code cannot be empty.");
    }

    courseCode = newCourseCode;
}

void Enrollment::setSemester(const std::string& newSemester) {
    if (newSemester.empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: semester cannot be empty.");
    }

    semester = newSemester;
}

void Enrollment::setGrade(char newGrade) {
    if (!isValidGrade(newGrade)) {
        throw EnrollmentException("Invalid enrollment data: unsupported grade.");
    }

    grade = newGrade;
}

void Enrollment::associateStudent(const Student& associatedStudent) {
    if (associatedStudent.getRollNo().empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: associated student has no roll number.");
    }
    student = &associatedStudent;
    studentRollNo = associatedStudent.getRollNo();
}

void Enrollment::clearStudentAssociation() {
    student = nullptr;
}

void Enrollment::displayEnrollmentInfo() const {
    std::cout << "Student Roll No: " << studentRollNo << '\n'
              << "Course Code: " << courseCode << '\n'
              << "Semester: " << semester << '\n'
              << "Grade: " << grade << '\n';
}

void Enrollment::validate() const {
    if (studentRollNo.empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: student roll number cannot be empty.");
    }

    if (courseCode.empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: course code cannot be empty.");
    }

    if (semester.empty()) {
        throw EnrollmentException(
            "Invalid enrollment data: semester cannot be empty.");
    }

    if (!isValidGrade(grade)) {
        throw EnrollmentException("Invalid enrollment data: unsupported grade.");
    }
}

bool Enrollment::isValidGrade(char candidateGrade) {
    return candidateGrade == 'A'
        || candidateGrade == 'B'
        || candidateGrade == 'C'
        || candidateGrade == 'D'
        || candidateGrade == 'F'
        || candidateGrade == 'I'
        || candidateGrade == 'N'
        || candidateGrade == 'W';
}

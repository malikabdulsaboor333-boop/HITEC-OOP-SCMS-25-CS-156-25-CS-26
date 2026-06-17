/**
 * @file Course.cpp
 * @brief Course class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation, association, operator overloading, and
 * custom exception handling.
 */

#include "Course.h"

#include "CapacityExceededException.h"
#include "Enrollment.h"
#include "EnrollmentException.h"

#include <iostream>
#include <ostream>

Course::Course()
    : Course(defaultCourseCode,
             defaultCourseTitle,
             defaultCreditHours,
             defaultMaxCapacity) {
}

Course::Course(const std::string& newCourseCode,
               const std::string& newCourseTitle,
               int newCreditHours,
               int newMaxCapacity)
    : courseCode(newCourseCode),
      courseTitle(newCourseTitle),
      creditHours(newCreditHours),
      maxCapacity(newMaxCapacity),
      enrolledStudents(0),
      faculty(nullptr) {
    validateCourseData();
}

Course::Course(const std::string& newCourseCode,
               const std::string& newCourseTitle,
               int newCreditHours,
               int newMaxCapacity,
               const Faculty& assignedFaculty)
    : Course(newCourseCode,
             newCourseTitle,
             newCreditHours,
             newMaxCapacity) {
    assignFaculty(assignedFaculty);
}

const std::string& Course::getCourseCode() const {
    return courseCode;
}

const std::string& Course::getCourseTitle() const {
    return courseTitle;
}

int Course::getCreditHours() const {
    return creditHours;
}

int Course::getMaxCapacity() const {
    return maxCapacity;
}

int Course::getEnrolledStudents() const {
    return enrolledStudents;
}

const Faculty* Course::getFaculty() const {
    return faculty;
}

const std::set<std::string>& Course::getEnrolledStudentRollNumbers() const {
    return enrolledStudentRollNumbers;
}

void Course::setCourseCode(const std::string& newCourseCode) {
    if (newCourseCode.empty()) {
        throw EnrollmentException("Invalid course data: course code cannot be empty.");
    }

    courseCode = newCourseCode;
}

void Course::setCourseTitle(const std::string& newCourseTitle) {
    if (newCourseTitle.empty()) {
        throw EnrollmentException("Invalid course data: course title cannot be empty.");
    }

    courseTitle = newCourseTitle;
}

void Course::setCreditHours(int newCreditHours) {
    if (newCreditHours <= minimumPositiveValue) {
        throw EnrollmentException("Invalid credit hours: value must be positive.");
    }

    creditHours = newCreditHours;
}

void Course::setMaxCapacity(int newMaxCapacity) {
    if (newMaxCapacity <= minimumPositiveValue) {
        throw EnrollmentException("Invalid course data: maximum capacity must be positive.");
    }

    if (newMaxCapacity < enrolledStudents) {
        throw EnrollmentException("Course capacity cannot be lower than current enrollment.");
    }

    maxCapacity = newMaxCapacity;
}

void Course::setEnrolledStudents(int newEnrolledStudents) {
    if (newEnrolledStudents < minimumPositiveValue) {
        throw EnrollmentException("Invalid enrollment data: count cannot be negative.");
    }

    if (newEnrolledStudents > maxCapacity) {
        throw CapacityExceededException("Course capacity exceeded.");
    }

    if (newEnrolledStudents != enrolledStudents) {
        enrolledStudentRollNumbers.clear();
    }
    enrolledStudents = newEnrolledStudents;
}

void Course::assignFaculty(const Faculty& assignedFaculty) {
    faculty = &assignedFaculty;
}

void Course::clearFaculty() {
    faculty = nullptr;
}

void Course::displayCourseInfo() const {
    writeCourseInfo(std::cout);
}

Course& Course::operator+=(const Enrollment& enrollment) {
    enrollment.validate();

    if (enrollment.getCourseCode() != courseCode) {
        throw EnrollmentException(
            "Invalid enrollment data: enrollment course code does not match.");
    }

    if (enrolledStudentRollNumbers.find(enrollment.getStudentRollNo())
        != enrolledStudentRollNumbers.end()) {
        throw EnrollmentException(
            "Invalid enrollment data: student is already enrolled.");
    }

    if (enrolledStudents >= maxCapacity) {
        throw CapacityExceededException("Course capacity exceeded.");
    }

    enrolledStudentRollNumbers.insert(enrollment.getStudentRollNo());
    ++enrolledStudents;
    return *this;
}

Course Course::operator+(const Enrollment& enrollment) const {
    Course result(*this);
    result += enrollment;
    return result;
}

bool Course::operator==(const Course& other) const {
    return courseCode == other.courseCode;
}

std::ostream& operator<<(std::ostream& output, const Course& course) {
    course.writeCourseInfo(output);
    return output;
}

void Course::validateCourseData() const {
    if (courseCode.empty()) {
        throw EnrollmentException("Invalid course data: course code cannot be empty.");
    }

    if (courseTitle.empty()) {
        throw EnrollmentException("Invalid course data: course title cannot be empty.");
    }

    if (creditHours <= minimumPositiveValue) {
        throw EnrollmentException("Invalid credit hours: value must be positive.");
    }

    if (maxCapacity <= minimumPositiveValue) {
        throw EnrollmentException("Invalid course data: maximum capacity must be positive.");
    }
}

void Course::writeCourseInfo(std::ostream& output) const {
    output << "Course Code: " << courseCode << '\n'
           << "Course Title: " << courseTitle << '\n'
           << "Credit Hours: " << creditHours << '\n'
           << "Maximum Capacity: " << maxCapacity << '\n'
           << "Enrolled Students: " << enrolledStudents << '\n'
           << "Faculty Assigned: " << (faculty == nullptr ? "No" : "Yes")
           << '\n';
}

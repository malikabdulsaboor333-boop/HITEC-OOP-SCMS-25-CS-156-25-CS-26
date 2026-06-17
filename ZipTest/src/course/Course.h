/**
 * @file Course.h
 * @brief Course class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation, association, operator overloading, and
 * custom exception handling.
 */

#ifndef SCMS_COURSE_COURSE_H
#define SCMS_COURSE_COURSE_H

#include <iosfwd>
#include <set>
#include <string>

class Enrollment;
class Faculty;

class Course {
public:
    Course();
    Course(const std::string& newCourseCode,
           const std::string& newCourseTitle,
           int newCreditHours,
           int newMaxCapacity);
    Course(const std::string& newCourseCode,
           const std::string& newCourseTitle,
           int newCreditHours,
           int newMaxCapacity,
           const Faculty& assignedFaculty);

    const std::string& getCourseCode() const;
    const std::string& getCourseTitle() const;
    int getCreditHours() const;
    int getMaxCapacity() const;
    int getEnrolledStudents() const;
    const Faculty* getFaculty() const;
    const std::set<std::string>& getEnrolledStudentRollNumbers() const;

    void setCourseCode(const std::string& newCourseCode);
    void setCourseTitle(const std::string& newCourseTitle);
    void setCreditHours(int newCreditHours);
    void setMaxCapacity(int newMaxCapacity);
    void setEnrolledStudents(int newEnrolledStudents);
    void assignFaculty(const Faculty& assignedFaculty);
    void clearFaculty();

    void displayCourseInfo() const;

    Course& operator+=(const Enrollment& enrollment);
    Course operator+(const Enrollment& enrollment) const;
    bool operator==(const Course& other) const;

    friend std::ostream& operator<<(std::ostream& output, const Course& course);

private:
    void validateCourseData() const;
    void writeCourseInfo(std::ostream& output) const;

    static constexpr const char* defaultCourseCode = "UNASSIGNED_COURSE";
    static constexpr const char* defaultCourseTitle = "Untitled Course";
    static constexpr int defaultCreditHours = 1;
    static constexpr int defaultMaxCapacity = 1;
    static constexpr int minimumPositiveValue = 0;

    std::string courseCode;
    std::string courseTitle;
    int creditHours;
    int maxCapacity;
    int enrolledStudents;
    const Faculty* faculty;
    std::set<std::string> enrolledStudentRollNumbers;
};

#endif

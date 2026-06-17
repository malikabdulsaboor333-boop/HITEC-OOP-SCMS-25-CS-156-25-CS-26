/**
 * @file Reports.h
 * @brief Campus reporting declarations and report data models
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_UTILS_REPORTS_H
#define SCMS_UTILS_REPORTS_H

#include <memory>
#include <string>
#include <vector>

namespace SCMS {
namespace Reports {

struct StudentSummary {
    std::string rollNo;
    std::string studentName;
    std::string department;
    double gpa {};
};

struct FacultySummary {
    std::string employeeId;
    std::string facultyName;
    std::string designation;
};

struct CourseSummary {
    std::string courseCode;
    std::string courseTitle;
    int creditHours {};
    int enrolledStudents {};
};

struct LibrarySummary {
    std::string itemId;
    std::string title;
    bool overdue {};
};

struct FeeSummary {
    std::string recordId;
    std::string studentRollNo;
    double amount {};
    bool paid {};
};

struct HostelSummary {
    std::string blockName;
    int totalRooms {};
    int occupiedRooms {};
    int totalOccupants {};
};

struct CampusReportData {
    std::vector<StudentSummary> students;
    std::vector<FacultySummary> faculty;
    std::vector<CourseSummary> courses;
    std::vector<LibrarySummary> libraryRecords;
    std::vector<FeeSummary> feeRecords;
    std::vector<HostelSummary> hostelBlocks;
};

class ReportGenerator {
public:
    ReportGenerator();
    ReportGenerator(const std::string& newReportTitle,
                    const std::string& newGeneratedDate);

    const std::string& getReportTitle() const;
    const std::string& getGeneratedDate() const;

    void setReportTitle(const std::string& newReportTitle);
    void setGeneratedDate(const std::string& newGeneratedDate);

    std::string generateCampusReport(const CampusReportData& data) const;
    std::string generateStudentReport(
        std::vector<StudentSummary> students) const;
    std::string generateFacultyReport(
        const std::vector<FacultySummary>& faculty) const;
    std::string generateCourseReport(
        const std::vector<CourseSummary>& courses) const;
    std::string generateLibraryReport(
        const std::vector<LibrarySummary>& libraryRecords) const;
    std::string generateFinanceReport(
        const std::vector<FeeSummary>& feeRecords) const;
    std::string generateHostelReport(
        const std::vector<HostelSummary>& hostelBlocks) const;

    bool exportTextReport(const std::string& reportContent,
                          const std::string& filePath,
                          bool append = false) const;
    bool saveToFile(const std::string& reportContent,
                    const std::string& filePath = "data/scms_report.txt",
                    bool append = false) const;
    std::string loadTextReport(
        const std::string& filePath = "data/scms_report.txt") const;
    std::string loadFromFile(
        const std::string& filePath = "data/scms_report.txt") const;

    static std::unique_ptr<ReportGenerator> createUnique(
        const std::string& reportTitle,
        const std::string& generatedDate);

private:
    std::string reportTitle;
    std::string generatedDate;
};

}  // namespace Reports
}  // namespace SCMS

#endif

/**
 * @file Reports.cpp
 * @brief Campus reporting implementations and STL algorithm usage
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Reports.h"

#include "CsvUtils.h"
#include "Utilities.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace SCMS {
namespace Reports {

ReportGenerator::ReportGenerator()
    : reportTitle("SCMS Campus Report"),
      generatedDate(Utils::UtilityManager::getCurrentTimestamp()) {
}

ReportGenerator::ReportGenerator(const std::string& newReportTitle,
                                 const std::string& newGeneratedDate)
    : reportTitle(newReportTitle),
      generatedDate(newGeneratedDate) {
    if (reportTitle.empty()) {
        throw std::invalid_argument("Report title cannot be empty.");
    }

    if (generatedDate.empty()) {
        throw std::invalid_argument("Generated date cannot be empty.");
    }
}

const std::string& ReportGenerator::getReportTitle() const {
    return reportTitle;
}

const std::string& ReportGenerator::getGeneratedDate() const {
    return generatedDate;
}

void ReportGenerator::setReportTitle(const std::string& newReportTitle) {
    if (newReportTitle.empty()) {
        throw std::invalid_argument("Report title cannot be empty.");
    }

    reportTitle = newReportTitle;
}

void ReportGenerator::setGeneratedDate(const std::string& newGeneratedDate) {
    if (newGeneratedDate.empty()) {
        throw std::invalid_argument("Generated date cannot be empty.");
    }

    generatedDate = newGeneratedDate;
}

std::string ReportGenerator::generateCampusReport(
    const CampusReportData& data) const {
    std::ostringstream report;

    report << "========================================\n"
           << "SMART CAMPUS MANAGEMENT SYSTEM\n"
           << "CONSOLIDATED REPORT\n"
           << "========================================\n"
           << "Title: " << reportTitle << '\n'
           << "Generated Date: " << generatedDate << "\n\n"
           << generateStudentReport(data.students) << '\n'
           << generateFacultyReport(data.faculty) << '\n'
           << generateCourseReport(data.courses) << '\n'
           << generateLibraryReport(data.libraryRecords) << '\n'
           << generateFinanceReport(data.feeRecords) << '\n'
           << generateHostelReport(data.hostelBlocks);

    const std::string reportContent = report.str();
    static_cast<void>(
        exportTextReport(reportContent, "data/scms_report.txt"));
    return reportContent;
}

std::string ReportGenerator::generateStudentReport(
    std::vector<StudentSummary> students) const {
    constexpr int decimalPlaces = 2;

    std::sort(
        students.begin(),
        students.end(),
        [](const StudentSummary& left, const StudentSummary& right) {
            if (left.gpa == right.gpa) {
                return left.rollNo < right.rollNo;
            }
            return left.gpa > right.gpa;
        });

    std::ostringstream report;
    report << "STUDENT INFORMATION SUMMARY\n"
           << "Total Students: " << students.size() << '\n';

    std::for_each(
        students.begin(),
        students.end(),
        [&report](const StudentSummary& student) {
            report << "- " << student.rollNo << " | "
                   << student.studentName << " | "
                   << student.department << " | GPA: "
                   << std::fixed << std::setprecision(decimalPlaces)
                   << student.gpa << '\n';
        });

    return report.str();
}

std::string ReportGenerator::generateFacultyReport(
    const std::vector<FacultySummary>& faculty) const {
    std::ostringstream report;
    report << "FACULTY SUMMARY\n"
           << "Total Faculty: " << faculty.size() << '\n';

    std::for_each(
        faculty.begin(),
        faculty.end(),
        [&report](const FacultySummary& member) {
            report << "- " << member.employeeId << " | "
                   << member.facultyName << " | "
                   << member.designation << '\n';
        });

    return report.str();
}

std::string ReportGenerator::generateCourseReport(
    const std::vector<CourseSummary>& courses) const {
    std::ostringstream report;
    report << "COURSE SUMMARY\n"
           << "Total Courses: " << courses.size() << '\n';

    std::for_each(
        courses.begin(),
        courses.end(),
        [&report](const CourseSummary& course) {
            report << "- " << course.courseCode << " | "
                   << course.courseTitle << " | Credit Hours: "
                   << course.creditHours << " | Enrolled: "
                   << course.enrolledStudents << '\n';
        });

    return report.str();
}

std::string ReportGenerator::generateLibraryReport(
    const std::vector<LibrarySummary>& libraryRecords) const {
    const auto firstOverdue = std::find_if(
        libraryRecords.begin(),
        libraryRecords.end(),
        [](const LibrarySummary& record) {
            return record.overdue;
        });

    std::vector<LibrarySummary> overdueRecords;
    std::copy_if(
        libraryRecords.begin(),
        libraryRecords.end(),
        std::back_inserter(overdueRecords),
        [](const LibrarySummary& record) {
            return record.overdue;
        });

    std::ostringstream report;
    report << "LIBRARY SUMMARY\n"
           << "Total Tracked Items: " << libraryRecords.size() << '\n'
           << "Overdue Items: " << overdueRecords.size() << '\n'
           << "First Overdue Item: ";

    if (firstOverdue == libraryRecords.end()) {
        report << "None\n";
    } else {
        report << firstOverdue->itemId << " | " << firstOverdue->title << '\n';
    }

    std::for_each(
        overdueRecords.begin(),
        overdueRecords.end(),
        [&report](const LibrarySummary& record) {
            report << "- OVERDUE: " << record.itemId << " | "
                   << record.title << '\n';
        });

    return report.str();
}

std::string ReportGenerator::generateFinanceReport(
    const std::vector<FeeSummary>& feeRecords) const {
    constexpr int decimalPlaces = 2;

    const auto unpaidCount = std::count_if(
        feeRecords.begin(),
        feeRecords.end(),
        [](const FeeSummary& record) {
            return !record.paid;
        });

    std::vector<FeeSummary> unpaidRecords;
    std::copy_if(
        feeRecords.begin(),
        feeRecords.end(),
        std::back_inserter(unpaidRecords),
        [](const FeeSummary& record) {
            return !record.paid;
        });

    double collectedFees = 0.0;
    std::for_each(
        feeRecords.begin(),
        feeRecords.end(),
        [&collectedFees](const FeeSummary& record) {
            if (record.paid) {
                collectedFees += record.amount;
            }
        });

    std::ostringstream report;
    report << "FINANCE SUMMARY\n"
           << "Total Fee Records: " << feeRecords.size() << '\n'
           << "Unpaid Fee Records: " << unpaidCount << '\n'
           << "Collected Fees: " << std::fixed
           << std::setprecision(decimalPlaces)
           << collectedFees << '\n';

    std::for_each(
        unpaidRecords.begin(),
        unpaidRecords.end(),
        [&report](const FeeSummary& record) {
            report << "- UNPAID: " << record.recordId << " | "
                   << record.studentRollNo << " | Amount: "
                   << std::fixed << std::setprecision(decimalPlaces)
                   << record.amount << '\n';
        });

    return report.str();
}

std::string ReportGenerator::generateHostelReport(
    const std::vector<HostelSummary>& hostelBlocks) const {
    int totalRooms = 0;
    int occupiedRooms = 0;
    int totalOccupants = 0;

    std::for_each(
        hostelBlocks.begin(),
        hostelBlocks.end(),
        [&totalRooms, &occupiedRooms, &totalOccupants](
            const HostelSummary& block) {
            totalRooms += block.totalRooms;
            occupiedRooms += block.occupiedRooms;
            totalOccupants += block.totalOccupants;
        });

    std::ostringstream report;
    report << "HOSTEL SUMMARY\n"
           << "Total Blocks: " << hostelBlocks.size() << '\n'
           << "Total Rooms: " << totalRooms << '\n'
           << "Occupied Rooms: " << occupiedRooms << '\n'
           << "Vacant Rooms: " << totalRooms - occupiedRooms << '\n'
           << "Total Occupants: " << totalOccupants << '\n';

    std::for_each(
        hostelBlocks.begin(),
        hostelBlocks.end(),
        [&report](const HostelSummary& block) {
            report << "- " << block.blockName << " | Rooms: "
                   << block.totalRooms << " | Occupied: "
                   << block.occupiedRooms << " | Occupants: "
                   << block.totalOccupants << '\n';
        });

    return report.str();
}

bool ReportGenerator::exportTextReport(
    const std::string& reportContent,
    const std::string& filePath,
    bool append) const {
    if (reportContent.empty() || filePath.empty()) {
        return false;
    }

    if (!Persistence::CsvUtils::ensureParentDirectory(filePath)) {
        return false;
    }

    const std::ios::openmode mode = std::ios::out
        | (append ? std::ios::app : std::ios::trunc);
    std::ofstream output(filePath, mode);
    if (!output) {
        return false;
    }

    output << reportContent;
    return output.good();
}

bool ReportGenerator::saveToFile(const std::string& reportContent,
                                 const std::string& filePath,
                                 bool append) const {
    return exportTextReport(reportContent, filePath, append);
}

std::string ReportGenerator::loadTextReport(
    const std::string& filePath) const {
    if (filePath.empty()) {
        return {};
    }

    std::ifstream input(filePath);
    if (!input) {
        return {};
    }

    return std::string(
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>());
}

std::string ReportGenerator::loadFromFile(
    const std::string& filePath) const {
    return loadTextReport(filePath);
}

std::unique_ptr<ReportGenerator> ReportGenerator::createUnique(
    const std::string& reportTitle,
    const std::string& generatedDate) {
    return std::make_unique<ReportGenerator>(reportTitle, generatedDate);
}

}  // namespace Reports
}  // namespace SCMS

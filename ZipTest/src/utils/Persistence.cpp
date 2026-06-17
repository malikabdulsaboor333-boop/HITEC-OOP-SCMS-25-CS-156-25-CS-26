/**
 * @file Persistence.cpp
 * @brief Campus-wide CSV persistence service implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Persistence.h"

#include "CsvUtils.h"
#include "../course/Course.h"
#include "../course/Enrollment.h"
#include "../finance/FinanceManager.h"
#include "../hostel/HostelManager.h"
#include "../library/Book.h"
#include "../library/Journal.h"
#include "../library/LibraryManager.h"
#include "../person/Faculty.h"
#include "../person/GradStudent.h"
#include "../person/Staff.h"
#include "../person/Student.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <utility>

namespace {

const std::string dataPath = "data/";
const std::string studentsPath = dataPath + "students.csv";
const std::string facultyPath = dataPath + "faculty.csv";
const std::string staffPath = dataPath + "staff.csv";
const std::string gradStudentsPath = dataPath + "grad_students.csv";
const std::string coursesPath = dataPath + "courses.csv";
const std::string enrollmentsPath = dataPath + "enrollments.csv";
const std::string libraryItemsPath = dataPath + "library_items.csv";
const std::string libraryMembersPath = dataPath + "library_members.csv";
const std::string libraryBorrowingsPath =
    dataPath + "library_borrowings.csv";
const std::string hostelBlocksPath = dataPath + "hostel_blocks.csv";
const std::string hostelRoomsPath = dataPath + "hostel_rooms.csv";
const std::string hostelAllocationsPath =
    dataPath + "hostel_allocations.csv";
const std::string invoicesPath = dataPath + "invoices.csv";
const std::string financeSummaryPath = dataPath + "finance_summary.csv";
const std::string financeRecordsPath =
    dataPath + "scms_finance_audit.csv";
const std::string reportPath = dataPath + "scms_report.txt";

constexpr const char* personHeader =
    "Name,CNIC,Age,Contact,RollNo,Department,CGPA";
constexpr const char* facultyHeader =
    "Name,CNIC,Age,Contact,EmployeeId,Designation,Salary";
constexpr const char* staffHeader =
    "Name,CNIC,Age,Contact,EmployeeId,Role,Salary";
constexpr const char* gradStudentHeader =
    "Name,CNIC,Age,Contact,RollNo,Department,CGPA,ResearchTopic,Supervisor";
constexpr const char* courseHeader =
    "CourseCode,CourseTitle,CreditHours,MaxCapacity,EnrolledStudents,"
    "FacultyEmployeeId";
constexpr const char* enrollmentHeader =
    "StudentRollNo,CourseCode,Semester,Grade";
constexpr const char* libraryItemHeader =
    "Type,ItemId,Title,Available,Creator,IdentifierOrVolume,YearOrIssue";
constexpr const char* libraryMemberHeader = "MemberId,MemberName";
constexpr const char* borrowingHeader = "MemberId,ItemId";
constexpr const char* hostelBlockHeader = "ManagerEntityId,BlockName";
constexpr const char* hostelRoomHeader =
    "BlockName,RoomNumber,RoomType,FloorNumber,MaxCapacity";
constexpr const char* hostelAllocationHeader =
    "BlockName,RoomNumber,StudentRollNo";
constexpr const char* invoiceHeader =
    "RecordType,RecordId,Description,Amount,TransactionDate,"
    "InvoiceNumber,PayerName,Paid,InvoiceCounter,LineItemCount,LineItems";
constexpr const char* financeSummaryHeader = "Metric,Value";
constexpr const char* financeRecordHeader =
    "RecordType,RecordId,Description,TransactionDateOrAmount,"
    "PartyIdOrDate,PartyNameOrId,AmountOrName,AllowanceOrSemester,"
    "DeductionOrPaid";

bool isHeader(const std::vector<std::string>& fields,
              const std::string& firstColumn) {
    return !fields.empty() && fields[0] == firstColumn;
}

template <typename RowHandler>
void readCsvRows(const std::string& filePath, RowHandler handleRow) {
    std::ifstream input(filePath);
    if (!input) {
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        const std::vector<std::string> fields =
            SCMS::Persistence::CsvUtils::parseLine(line);
        if (!fields.empty()) {
            handleRow(fields);
        }
    }
}

void writePersonFields(std::ostream& output, const Person& person) {
    output << SCMS::Persistence::CsvUtils::escape(person.getName()) << ','
           << SCMS::Persistence::CsvUtils::escape(person.getCnic()) << ','
           << person.getAge() << ','
           << SCMS::Persistence::CsvUtils::escape(person.getContact());
}

}  // namespace

namespace SCMS {
namespace Persistence {

bool CampusPersistence::ensureDataFiles() {
    const std::vector<std::pair<std::string, std::string>> files = {
        {studentsPath, personHeader},
        {facultyPath, facultyHeader},
        {staffPath, staffHeader},
        {gradStudentsPath, gradStudentHeader},
        {coursesPath, courseHeader},
        {enrollmentsPath, enrollmentHeader},
        {libraryItemsPath, libraryItemHeader},
        {libraryMembersPath, libraryMemberHeader},
        {libraryBorrowingsPath, borrowingHeader},
        {hostelBlocksPath, hostelBlockHeader},
        {hostelRoomsPath, hostelRoomHeader},
        {hostelAllocationsPath, hostelAllocationHeader},
        {invoicesPath, invoiceHeader},
        {financeSummaryPath, financeSummaryHeader},
        {financeRecordsPath, financeRecordHeader}
    };

    const bool csvFilesReady = std::all_of(
        files.begin(),
        files.end(),
        [](const std::pair<std::string, std::string>& file) {
            return CsvUtils::ensureFile(file.first, file.second);
        });
    return csvFilesReady
        && CsvUtils::ensureFile(
            reportPath, "SCMS report has not been generated yet.");
}

bool CampusPersistence::savePersons(
    const std::vector<std::unique_ptr<Person>>& people,
    bool append) {
    std::ofstream students;
    std::ofstream faculty;
    std::ofstream staff;
    std::ofstream gradStudents;
    if (!CsvUtils::openOutput(students, studentsPath, personHeader, append)
        || !CsvUtils::openOutput(
            faculty, facultyPath, facultyHeader, append)
        || !CsvUtils::openOutput(staff, staffPath, staffHeader, append)
        || !CsvUtils::openOutput(
            gradStudents, gradStudentsPath, gradStudentHeader, append)) {
        return false;
    }

    for (const std::unique_ptr<Person>& person : people) {
        if (!person) {
            continue;
        }

        if (const auto* graduate =
                dynamic_cast<const GradStudent*>(person.get())) {
            writePersonFields(gradStudents, *graduate);
            gradStudents << ','
                         << CsvUtils::escape(graduate->getRollNo()) << ','
                         << CsvUtils::escape(graduate->getDepartment()) << ','
                         << graduate->getCgpa() << ','
                         << CsvUtils::escape(graduate->getResearchTopic())
                         << ','
                         << CsvUtils::escape(graduate->getSupervisor())
                         << '\n';
        } else if (const auto* student =
                       dynamic_cast<const Student*>(person.get())) {
            writePersonFields(students, *student);
            students << ',' << CsvUtils::escape(student->getRollNo()) << ','
                     << CsvUtils::escape(student->getDepartment()) << ','
                     << student->getCgpa() << '\n';
        } else if (const auto* facultyMember =
                       dynamic_cast<const Faculty*>(person.get())) {
            writePersonFields(faculty, *facultyMember);
            faculty << ','
                    << CsvUtils::escape(facultyMember->getEmployeeId()) << ','
                    << CsvUtils::escape(facultyMember->getDesignation())
                    << ',' << facultyMember->getSalary() << '\n';
        } else if (const auto* staffMember =
                       dynamic_cast<const Staff*>(person.get())) {
            writePersonFields(staff, *staffMember);
            staff << ',' << CsvUtils::escape(staffMember->getEmployeeId())
                  << ',' << CsvUtils::escape(staffMember->getRole()) << ','
                  << staffMember->getSalary() << '\n';
        }
    }

    return students.good() && faculty.good() && staff.good()
        && gradStudents.good();
}

std::vector<std::unique_ptr<Person>> CampusPersistence::loadPersons() {
    std::vector<std::unique_ptr<Person>> people;

    const auto loadStudent = [&people](
                                 const std::vector<std::string>& fields) {
        if (isHeader(fields, "Name") || fields.size() != 7U) {
            return;
        }
        int age = 0;
        float cgpa = 0.0F;
        if (!CsvUtils::parseInt(fields[2], age)
            || !CsvUtils::parseFloat(fields[6], cgpa)) {
            return;
        }
        try {
            people.push_back(std::make_unique<Student>(
                fields[0], fields[1], age, fields[3], fields[4], fields[5],
                cgpa));
        } catch (const std::exception&) {
        }
    };
    readCsvRows(studentsPath, loadStudent);

    const auto loadFaculty = [&people](
                                 const std::vector<std::string>& fields) {
        if (isHeader(fields, "Name") || fields.size() != 7U) {
            return;
        }
        int age = 0;
        double salary = 0.0;
        if (!CsvUtils::parseInt(fields[2], age)
            || !CsvUtils::parseDouble(fields[6], salary)) {
            return;
        }
        try {
            people.push_back(std::make_unique<Faculty>(
                fields[0], fields[1], age, fields[3], fields[4], fields[5],
                salary));
        } catch (const std::exception&) {
        }
    };
    readCsvRows(facultyPath, loadFaculty);

    const auto loadStaff = [&people](
                               const std::vector<std::string>& fields) {
        if (isHeader(fields, "Name") || fields.size() != 7U) {
            return;
        }
        int age = 0;
        double salary = 0.0;
        if (!CsvUtils::parseInt(fields[2], age)
            || !CsvUtils::parseDouble(fields[6], salary)) {
            return;
        }
        try {
            people.push_back(std::make_unique<Staff>(
                fields[0], fields[1], age, fields[3], fields[4], fields[5],
                salary));
        } catch (const std::exception&) {
        }
    };
    readCsvRows(staffPath, loadStaff);

    const auto loadGraduate = [&people](
                                  const std::vector<std::string>& fields) {
        if (isHeader(fields, "Name") || fields.size() != 9U) {
            return;
        }
        int age = 0;
        float cgpa = 0.0F;
        if (!CsvUtils::parseInt(fields[2], age)
            || !CsvUtils::parseFloat(fields[6], cgpa)) {
            return;
        }
        try {
            people.push_back(std::make_unique<GradStudent>(
                fields[0], fields[1], age, fields[3], fields[4], fields[5],
                cgpa, fields[7], fields[8]));
        } catch (const std::exception&) {
        }
    };
    readCsvRows(gradStudentsPath, loadGraduate);

    return people;
}

bool CampusPersistence::saveCourses(
    const std::vector<Course>& courses,
    const std::vector<Enrollment>& enrollments,
    bool append) {
    std::ofstream courseOutput;
    std::ofstream enrollmentOutput;
    if (!CsvUtils::openOutput(
            courseOutput, coursesPath, courseHeader, append)
        || !CsvUtils::openOutput(
            enrollmentOutput,
            enrollmentsPath,
            enrollmentHeader,
            append)) {
        return false;
    }

    for (const Course& course : courses) {
        const Faculty* faculty = course.getFaculty();
        courseOutput
            << CsvUtils::escape(course.getCourseCode()) << ','
            << CsvUtils::escape(course.getCourseTitle()) << ','
            << course.getCreditHours() << ',' << course.getMaxCapacity()
            << ',' << course.getEnrolledStudents() << ','
            << CsvUtils::escape(
                   faculty == nullptr ? "" : faculty->getEmployeeId())
            << '\n';
    }

    for (const Enrollment& enrollment : enrollments) {
        enrollmentOutput
            << CsvUtils::escape(enrollment.getStudentRollNo()) << ','
            << CsvUtils::escape(enrollment.getCourseCode()) << ','
            << CsvUtils::escape(enrollment.getSemester()) << ','
            << enrollment.getGrade() << '\n';
    }

    return courseOutput.good() && enrollmentOutput.good();
}

bool CampusPersistence::loadCourses(std::vector<Course>& courses,
                                    std::vector<Enrollment>& enrollments) {
    std::vector<Course> loadedCourses;
    std::vector<Enrollment> loadedEnrollments;
    std::set<std::string> courseCodes;

    readCsvRows(
        coursesPath,
        [&loadedCourses, &courseCodes](
            const std::vector<std::string>& fields) {
            if (isHeader(fields, "CourseCode") || fields.size() != 6U) {
                return;
            }
            int creditHours = 0;
            int capacity = 0;
            int enrolled = 0;
            if (!CsvUtils::parseInt(fields[2], creditHours)
                || !CsvUtils::parseInt(fields[3], capacity)
                || !CsvUtils::parseInt(fields[4], enrolled)
                || !courseCodes.insert(fields[0]).second) {
                return;
            }
            try {
                Course course(
                    fields[0], fields[1], creditHours, capacity);
                course.setEnrolledStudents(enrolled);
                loadedCourses.push_back(course);
            } catch (const std::exception&) {
                courseCodes.erase(fields[0]);
            }
        });

    readCsvRows(
        enrollmentsPath,
        [&loadedEnrollments](const std::vector<std::string>& fields) {
            if (isHeader(fields, "StudentRollNo") || fields.size() != 4U
                || fields[3].size() != 1U) {
                return;
            }
            try {
                loadedEnrollments.emplace_back(
                    fields[0], fields[1], fields[2], fields[3][0]);
            } catch (const std::exception&) {
            }
        });

    courses = std::move(loadedCourses);
    enrollments = std::move(loadedEnrollments);
    return true;
}

bool CampusPersistence::saveLibrary(const LibraryManager& manager,
                                    bool append) {
    std::ofstream itemOutput;
    std::ofstream memberOutput;
    std::ofstream borrowingOutput;
    if (!CsvUtils::openOutput(
            itemOutput, libraryItemsPath, libraryItemHeader, append)
        || !CsvUtils::openOutput(
            memberOutput,
            libraryMembersPath,
            libraryMemberHeader,
            append)
        || !CsvUtils::openOutput(
            borrowingOutput,
            libraryBorrowingsPath,
            borrowingHeader,
            append)) {
        return false;
    }

    for (const std::unique_ptr<LibraryItem>& item : manager.getItems()) {
        if (const auto* book = dynamic_cast<const Book*>(item.get())) {
            itemOutput << "BOOK," << CsvUtils::escape(book->getItemId())
                       << ',' << CsvUtils::escape(book->getTitle()) << ','
                       << book->getIsAvailable() << ','
                       << CsvUtils::escape(book->getAuthor()) << ','
                       << CsvUtils::escape(book->getIsbn()) << ','
                       << book->getPublicationYear() << '\n';
        } else if (const auto* journal =
                       dynamic_cast<const Journal*>(item.get())) {
            itemOutput << "JOURNAL,"
                       << CsvUtils::escape(journal->getItemId()) << ','
                       << CsvUtils::escape(journal->getTitle()) << ','
                       << journal->getIsAvailable() << ','
                       << CsvUtils::escape(journal->getPublisher()) << ','
                       << journal->getVolume() << ',' << journal->getIssue()
                       << '\n';
        }
    }

    for (const LibraryMember& member : manager.getMembers()) {
        memberOutput << CsvUtils::escape(member.getMemberId()) << ','
                     << CsvUtils::escape(member.getMemberName()) << '\n';
        for (const std::string& itemId : member.getBorrowedItems()) {
            borrowingOutput << CsvUtils::escape(member.getMemberId()) << ','
                            << CsvUtils::escape(itemId) << '\n';
        }
    }

    return itemOutput.good() && memberOutput.good()
        && borrowingOutput.good();
}

bool CampusPersistence::loadLibrary(LibraryManager& manager) {
    LibraryManager loadedManager;
    std::map<std::string, bool> availability;

    readCsvRows(
        libraryItemsPath,
        [&loadedManager, &availability](
            const std::vector<std::string>& fields) {
            if (isHeader(fields, "Type") || fields.size() != 7U) {
                return;
            }
            bool available = false;
            int firstNumber = 0;
            int secondNumber = 0;
            if (!CsvUtils::parseBool(fields[3], available)) {
                return;
            }
            try {
                bool added = false;
                if (fields[0] == "BOOK"
                    && CsvUtils::parseInt(fields[6], secondNumber)) {
                    added = loadedManager.addItem(std::make_unique<Book>(
                        fields[1], fields[2], true, fields[4], fields[5],
                        secondNumber));
                } else if (fields[0] == "JOURNAL"
                           && CsvUtils::parseInt(fields[5], firstNumber)
                           && CsvUtils::parseInt(fields[6], secondNumber)) {
                    added = loadedManager.addItem(std::make_unique<Journal>(
                        fields[1], fields[2], true, fields[4], firstNumber,
                        secondNumber));
                }
                if (added) {
                    availability[fields[1]] = available;
                }
            } catch (const std::exception&) {
            }
        });

    readCsvRows(
        libraryMembersPath,
        [&loadedManager](const std::vector<std::string>& fields) {
            if (isHeader(fields, "MemberId") || fields.size() != 2U) {
                return;
            }
            try {
                static_cast<void>(loadedManager.registerMember(
                    LibraryMember(fields[0], fields[1])));
            } catch (const std::exception&) {
            }
        });

    readCsvRows(
        libraryBorrowingsPath,
        [&loadedManager](const std::vector<std::string>& fields) {
            if (isHeader(fields, "MemberId") || fields.size() != 2U) {
                return;
            }
            static_cast<void>(
                loadedManager.issueItem(fields[1], fields[0]));
        });

    for (const std::pair<const std::string, bool>& status : availability) {
        LibraryItem* item = loadedManager.searchItemById(status.first);
        if (item != nullptr && item->getIsAvailable()) {
            item->setIsAvailable(status.second);
        }
    }

    manager = std::move(loadedManager);
    return true;
}

bool CampusPersistence::saveHostel(const HostelManager& manager,
                                   bool append) {
    std::ofstream blockOutput;
    std::ofstream roomOutput;
    std::ofstream allocationOutput;
    if (!CsvUtils::openOutput(
            blockOutput, hostelBlocksPath, hostelBlockHeader, append)
        || !CsvUtils::openOutput(
            roomOutput, hostelRoomsPath, hostelRoomHeader, append)
        || !CsvUtils::openOutput(
            allocationOutput,
            hostelAllocationsPath,
            hostelAllocationHeader,
            append)) {
        return false;
    }

    for (const HostelBlock& block : manager.getHostelBlocks()) {
        blockOutput << CsvUtils::escape(manager.getEntityId()) << ','
                    << CsvUtils::escape(block.getBlockName()) << '\n';
        for (const Room& room : block.getRooms()) {
            roomOutput << CsvUtils::escape(block.getBlockName()) << ','
                       << CsvUtils::escape(room.getRoomNumber()) << ','
                       << CsvUtils::escape(room.getRoomType()) << ','
                       << room.getFloorNumber() << ','
                       << room.getMaxCapacity() << '\n';
            for (const std::string& occupant : room.getOccupants()) {
                allocationOutput
                    << CsvUtils::escape(block.getBlockName()) << ','
                    << CsvUtils::escape(room.getRoomNumber()) << ','
                    << CsvUtils::escape(occupant) << '\n';
            }
        }
    }

    return blockOutput.good() && roomOutput.good()
        && allocationOutput.good();
}

bool CampusPersistence::loadHostel(HostelManager& manager) {
    std::string managerId = "DEFAULT_HOSTEL_MANAGER";
    std::vector<std::string> blockNames;

    readCsvRows(
        hostelBlocksPath,
        [&managerId, &blockNames](const std::vector<std::string>& fields) {
            if (isHeader(fields, "ManagerEntityId") || fields.size() != 2U
                || fields[0].empty() || fields[1].empty()
                || std::find(blockNames.begin(), blockNames.end(), fields[1])
                    != blockNames.end()) {
                return;
            }
            managerId = fields[0];
            blockNames.push_back(fields[1]);
        });

    HostelManager loadedManager(managerId);
    for (const std::string& blockName : blockNames) {
        try {
            static_cast<void>(
                loadedManager.addHostelBlock(HostelBlock(blockName)));
        } catch (const std::exception&) {
        }
    }

    readCsvRows(
        hostelRoomsPath,
        [&loadedManager](const std::vector<std::string>& fields) {
            if (isHeader(fields, "BlockName") || fields.size() != 5U) {
                return;
            }
            int floor = 0;
            int capacity = 0;
            if (!CsvUtils::parseInt(fields[3], floor)
                || !CsvUtils::parseInt(fields[4], capacity)) {
                return;
            }
            HostelBlock* block = loadedManager.searchBlock(fields[0]);
            if (block == nullptr) {
                return;
            }
            try {
                static_cast<void>(block->addRoom(
                    Room(fields[1], fields[2], floor, capacity)));
            } catch (const std::exception&) {
            }
        });

    readCsvRows(
        hostelAllocationsPath,
        [&loadedManager](const std::vector<std::string>& fields) {
            if (isHeader(fields, "BlockName") || fields.size() != 3U) {
                return;
            }
            static_cast<void>(loadedManager.allocateRoom(
                fields[0], fields[1], fields[2]));
        });

    manager = std::move(loadedManager);
    return true;
}

bool CampusPersistence::saveFinanceSummary(
    const FinanceManager& manager,
    bool append) {
    std::ofstream output;
    if (!CsvUtils::openOutput(
            output,
            financeSummaryPath,
            financeSummaryHeader,
            append)) {
        return false;
    }

    output << "SalaryRecords," << manager.getSalaryRecords().size() << '\n'
           << "FeeRecords," << manager.getFeeRecords().size() << '\n'
           << "InvoiceRecords," << manager.getInvoices().size() << '\n'
           << "TotalSalaryExpense,"
           << manager.calculateTotalSalaryExpense() << '\n'
           << "TotalCollectedFees,"
           << manager.calculateTotalCollectedFees() << '\n'
           << "InvoiceCounter," << Invoice::getInvoiceCounter() << '\n';
    return output.good();
}

bool CampusPersistence::saveToFile(
    const std::vector<std::unique_ptr<Person>>& people,
    bool append) {
    return savePersons(people, append);
}

bool CampusPersistence::loadFromFile(
    std::vector<std::unique_ptr<Person>>& people) {
    people = loadPersons();
    return true;
}

bool CampusPersistence::saveToFile(
    const std::vector<Course>& courses,
    const std::vector<Enrollment>& enrollments,
    bool append) {
    return saveCourses(courses, enrollments, append);
}

bool CampusPersistence::loadFromFile(
    std::vector<Course>& courses,
    std::vector<Enrollment>& enrollments) {
    return loadCourses(courses, enrollments);
}

bool CampusPersistence::saveToFile(const LibraryManager& manager,
                                   bool append) {
    return saveLibrary(manager, append);
}

bool CampusPersistence::loadFromFile(LibraryManager& manager) {
    return loadLibrary(manager);
}

bool CampusPersistence::saveToFile(const HostelManager& manager,
                                   bool append) {
    return saveHostel(manager, append);
}

bool CampusPersistence::loadFromFile(HostelManager& manager) {
    return loadHostel(manager);
}

bool CampusPersistence::saveToFile(const FinanceManager& manager,
                                   bool append) {
    return manager.saveToCsv(financeRecordsPath, append)
        && manager.saveInvoices(invoicesPath, append)
        && saveFinanceSummary(manager, append);
}

bool CampusPersistence::loadFromFile(FinanceManager& manager) {
    return manager.loadFromCsv(financeRecordsPath)
        && manager.loadInvoices(invoicesPath);
}

const std::string& CampusPersistence::dataDirectory() {
    return dataPath;
}

}  // namespace Persistence
}  // namespace SCMS

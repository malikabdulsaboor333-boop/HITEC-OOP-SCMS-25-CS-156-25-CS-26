/**
 * @file main.cpp
 * @brief Integrated Smart Campus Management System demonstration program
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "course/CapacityExceededException.h"
#include "course/Course.h"
#include "course/Enrollment.h"
#include "finance/FeeRecord.h"
#include "finance/FinanceManager.h"
#include "finance/Invoice.h"
#include "finance/SalaryRecord.h"
#include "hostel/HostelManager.h"
#include "library/Book.h"
#include "library/Journal.h"
#include "library/Library.h"
#include "library/LibraryManager.h"
#include "library/OverdueException.h"
#include "person/Faculty.h"
#include "person/Staff.h"
#include "person/Student.h"
#include "person/UndergradStudent.h"
#include "utils/Reports.h"
#include "utils/Persistence.h"
#include "utils/Utilities.h"

#include <cstdio>
#include <exception>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

constexpr int exitOption = 0;
constexpr int personOption = 1;
constexpr int courseOption = 2;
constexpr int libraryOption = 3;
constexpr int financeOption = 4;
constexpr int hostelOption = 5;
constexpr int reportsOption = 6;
constexpr int fullDemoOption = 7;
constexpr const char* selfTestArgument = "--self-test";
constexpr const char* persistenceSeedArgument = "--persistence-seed";
constexpr const char* persistenceVerifyArgument = "--persistence-verify";
constexpr const char* persistenceAppendArgument = "--persistence-append-test";
constexpr const char* financeCsvPath = "data/scms_finance_audit.csv";
constexpr const char* invoiceCsvPath = "data/invoices.csv";

void printSplash() {
    std::cout << R"(
  ____   ____ __  __ ____
 / ___| / ___|  \/  / ___|
 \___ \| |   | |\/| \___ \
  ___) | |___| |  | |___) |
 |____/ \____|_|  |_|____/

 HITEC UNIVERSITY SMART CAMPUS MANAGEMENT SYSTEM
)" << '\n';
}

void printMenu() {
    std::cout << "\n========================================\n"
              << "HITEC UNIVERSITY SCMS\n"
              << "========================================\n"
              << "1. Person Hierarchy Demo\n"
              << "2. Course and Enrollment Demo\n"
              << "3. Library Demo\n"
              << "4. Finance Demo\n"
              << "5. Hostel Demo\n"
              << "6. Reports and Utilities Demo\n"
              << "7. Run Complete Demonstration\n"
              << "0. Exit\n"
              << "Select an option: ";
}

bool demonstratePersonModule() {
    std::vector<std::unique_ptr<Person>> people;
    people.push_back(std::make_unique<Student>(
        "Abdul Saboor",
        "12345-1234567-1",
        20,
        "0300-1234567",
        "23-CS-156",
        "Computer Science",
        2.5F));
    people.push_back(std::make_unique<Faculty>(
        "Professor Mohsin Shahzad",
        "12345-1234567-2",
        42,
        "0300-1234568",
        "EMP-001",
        "Professor",
        180000.0));
    people.push_back(std::make_unique<Staff>(
        "Rehan Ali",
        "12345-1234567-3",
        32,
        "0300-1234569",
        "STF-001",
        "Coordinator",
        75000.0));
    people.push_back(std::make_unique<UndergradStudent>(
        "Abdullah Sajid",
        "12345-1234567-4",
        24,
        "0300-1234570",
        "25-CS-26",
        "Computer Science",
        3.9F,
        "Smart Campus Management System",
        "Professor Mohsin Shahzad"));

    for (const std::unique_ptr<Person>& person : people) {
        person->displayInfo();
        std::cout << '\n';
    }
    if (!SCMS::Persistence::CampusPersistence::savePersons(people)) {
        return false;
    }
    const std::vector<std::unique_ptr<Person>> loadedPeople =
        SCMS::Persistence::CampusPersistence::loadPersons();
    return people.size() == 4U && loadedPeople.size() == people.size();
}

bool demonstrateCourseModule() {
    Faculty instructor(
        "Professor Mohsin Shahzad",
        "12345-1234567-2",
        42,
        "0300-1234568",
        "EMP-001",
        "Professor",
        180000.0);
    Student firstStudent(
        "Abdul Saboor",
        "12345-1234567-1",
        20,
        "0300-1234567",
        "23-CS-156",
        "Computer Science",
        2.5F);
    Student secondStudent(
        "Abdullah Sajid",
        "12345-1234567-4",
        24,
        "0300-1234570",
        "25-CS-26",
        "Computer Science",
        3.9F);

    Course course(
        "CS-202",
        "Object-Oriented Programming",
        3,
        2,
        instructor);
    Enrollment firstEnrollment(
        firstStudent, "CS-202", "Spring 2025", 'N');
    Enrollment secondEnrollment(
        secondStudent, "CS-202", "Spring 2025", 'N');

    Course enrolledCourse = course + firstEnrollment;
    enrolledCourse += secondEnrollment;
    std::cout << enrolledCourse;

    const std::vector<Course> courses = {enrolledCourse};
    const std::vector<Enrollment> enrollments = {
        firstEnrollment, secondEnrollment
    };
    if (!SCMS::Persistence::CampusPersistence::saveCourses(
            courses, enrollments)) {
        return false;
    }
    std::vector<Course> loadedCourses;
    std::vector<Enrollment> loadedEnrollments;
    if (!SCMS::Persistence::CampusPersistence::loadCourses(
            loadedCourses, loadedEnrollments)) {
        return false;
    }

    bool capacityExceptionCaught = false;
    try {
        enrolledCourse += Enrollment(
            "23-CS-003", "CS-202", "Spring 2025", 'N');
    } catch (const CapacityExceededException& exception) {
        capacityExceptionCaught = true;
        std::cout << "Expected exception: " << exception.what() << '\n';
    }

    return capacityExceptionCaught
        && enrolledCourse.getFaculty() == &instructor
        && firstEnrollment.getStudent() == &firstStudent
        && enrolledCourse.getEnrolledStudents() == 2
        && loadedCourses.size() == 1U
        && loadedEnrollments.size() == 2U;
}

bool demonstrateLibraryModule() {
    LibraryManager manager;
    const bool bookAdded = manager.addItem(std::make_unique<Book>(
        "B-001",
        "Clean Code",
        true,
        "Robert C. Martin",
        "9780132350884",
        2008));
    const bool journalAdded = manager.addItem(std::make_unique<Journal>(
        "J-001",
        "IEEE Software",
        true,
        "IEEE",
        42,
        2));
    const bool memberRegistered =
        manager.registerMember(LibraryMember("M-001", "Abdul Saboor"));
    const bool issued = manager.issueItem("B-001", "M-001");
    const bool saved =
        SCMS::Persistence::CampusPersistence::saveLibrary(manager);
    LibraryManager loadedManager;
    const bool loaded =
        SCMS::Persistence::CampusPersistence::loadLibrary(loadedManager);
    const bool returned = manager.returnItem("B-001", "M-001");

    bool overdueExceptionCaught = false;
    try {
        manager.checkOverdue(5);
    } catch (const OverdueException& exception) {
        overdueExceptionCaught = true;
        std::cout << "Expected exception: " << exception.what() << '\n';
    }

    Library<Book> bookLibrary;
    const bool templateBookAdded = bookLibrary.addItem(Book(
        "B-002",
        "Design Patterns",
        true,
        "Gamma, Helm, Johnson, Vlissides",
        "9780201633610",
        1994));
    const Book* locatedBook = bookLibrary.findByTitle("Design Patterns");

    manager.displayInventory();
    return bookAdded
        && journalAdded
        && memberRegistered
        && issued
        && saved
        && loaded
        && loadedManager.searchItemById("B-001") != nullptr
        && !loadedManager.searchItemById("B-001")->getIsAvailable()
        && returned
        && overdueExceptionCaught
        && templateBookAdded
        && locatedBook != nullptr;
}

bool demonstrateFinanceModule() {
    SalaryRecord salary(
        "SAL-001",
        "June salary",
        "2025-06-30",
        "EMP-001",
        "Professor Mohsin Shahzad",
        150000.0,
        20000.0,
        10000.0);
    FeeRecord fee(
        "FEE-001",
        "Spring tuition fee",
        85000.0,
        "2025-02-10",
        "25-CS-156",
        "Abdul Saboor",
        "Spring 2025",
        true);

    FeeRecord copiedFee(fee);
    copiedFee -= 5000.0;
    if (copiedFee.getAmount() != 80000.0) {
        return false;
    }

    Invoice invoice(
        "INV-REC-001",
        "Campus service invoice",
        2500.0,
        "2025-03-01",
        "INV-001",
        "Abdul Saboor",
        {"Transport Card", "Processing Fee"},
        false);
    Invoice movedInvoice(std::move(invoice));

    FinanceManager manager;
    if (!manager.addSalaryRecord(salary) || !manager.addFeeRecord(fee)
        || !manager.addInvoice(movedInvoice)) {
        return false;
    }
    if (!manager.saveToCsv(financeCsvPath)
        || !manager.saveInvoices(invoiceCsvPath)
        || !SCMS::Persistence::CampusPersistence::saveFinanceSummary(
            manager)) {
        return false;
    }

    FinanceManager loadedManager;
    const bool loaded = loadedManager.loadFromCsv(financeCsvPath)
        && loadedManager.loadInvoices(invoiceCsvPath);
    std::cout << generateFinanceSummary(loadedManager);
    movedInvoice.displayRecord();

    return loaded
        && loadedManager.searchRecordById("SAL-001") != nullptr
        && loadedManager.searchRecordById("FEE-001") != nullptr
        && loadedManager.getInvoices().size() == 1U
        && Invoice::getInvoiceCounter() > 0;
}

bool demonstrateHostelModule() {
    HostelBlock block("Block A");
    if (!block.addRoom(Room("A-101", "Single", 1, 1))
        || !block.addRoom(Room("A-102", "Double", 1, 2))) {
        return false;
    }

    HostelManager manager("HOSTEL-MANAGER-001");
    if (!manager.addHostelBlock(block)) {
        return false;
    }

    Accommodation* accommodation = &manager;
    Reportable* reportable = &manager;
    BaseEntity* accommodationEntity = accommodation;
    BaseEntity* reportableEntity = reportable;

    const bool allocated =
        accommodation->allocateRoom("Block A", "A-102", "23-CS-001");
    const bool saved =
        SCMS::Persistence::CampusPersistence::saveHostel(manager);
    HostelManager loadedManager;
    const bool loaded =
        SCMS::Persistence::CampusPersistence::loadHostel(loadedManager);
    reportable->generateReport();
    const bool vacated =
        accommodation->vacateRoom("Block A", "A-102", "23-CS-001");

    return allocated
        && saved
        && loaded
        && loadedManager.searchBlock("Block A") != nullptr
        && loadedManager.searchBlock("Block A")->searchRoom("A-102")
            != nullptr
        && loadedManager.searchBlock("Block A")
               ->searchRoom("A-102")
               ->hasOccupant("23-CS-001")
        && vacated
        && accommodationEntity == reportableEntity;
}

bool demonstrateReportsModule() {
    using SCMS::Reports::CampusReportData;
    using SCMS::Reports::ReportGenerator;
    using SCMS::Utils::UtilityManager;

    const std::unique_ptr<ReportGenerator> generator =
        ReportGenerator::createUnique(
            "Spring 2025 Consolidated Report",
            UtilityManager::getCurrentTimestamp());
    const std::shared_ptr<UtilityManager> utilities =
        UtilityManager::createShared();

    CampusReportData data;
    data.students = {
        {"25-CS-26", "Abdullah Sajjid", "Computer Science", 3.90},
        {"23-CS-156", "Abdul Saboor", "Computer Science", 2.50}
    };
    data.faculty = {{"EMP-001", "Professor Mohsin Shahzad", "Professor"}};
    data.courses = {
        {"CS-202", "Object-Oriented Programming", 3, 2}
    };
    data.libraryRecords = {
        {"B-001", "Clean Code", false},
        {"J-001", "IEEE Software", true}
    };
    data.feeRecords = {
        {"FEE-001", "23-CS-156", 85000.0, true},
        {"FEE-002", "25-CS-26", 85000.0, false}
    };
    data.hostelBlocks = {{"Block A", 2, 1, 1}};

    const std::string report = generator->generateCampusReport(data);
    std::cout << report;
    const std::string loadedReport = generator->loadTextReport();

    return utilities != nullptr
        && UtilityManager::validateEmail("student@hitecuni.edu.pk")
        && report.find("CONSOLIDATED REPORT") != std::string::npos
        && loadedReport == report;
}

bool runCompleteDemonstration() {
    return demonstratePersonModule()
        && demonstrateCourseModule()
        && demonstrateLibraryModule()
        && demonstrateFinanceModule()
        && demonstrateHostelModule()
        && demonstrateReportsModule();
}

bool verifyPersistedData() {
    const std::vector<std::unique_ptr<Person>> people =
        SCMS::Persistence::CampusPersistence::loadPersons();

    std::vector<Course> courses;
    std::vector<Enrollment> enrollments;
    const bool coursesLoaded =
        SCMS::Persistence::CampusPersistence::loadCourses(
            courses, enrollments);

    LibraryManager libraryManager;
    const bool libraryLoaded =
        SCMS::Persistence::CampusPersistence::loadLibrary(libraryManager);
    const LibraryItem* borrowedBook =
        libraryManager.searchItemById("B-001");

    FinanceManager financeManager;
    const bool financeLoaded =
        financeManager.loadFromCsv(financeCsvPath)
        && financeManager.loadInvoices(invoiceCsvPath);

    HostelManager hostelManager;
    const bool hostelLoaded =
        SCMS::Persistence::CampusPersistence::loadHostel(hostelManager);
    const HostelBlock* block = hostelManager.searchBlock("Block A");
    const Room* room =
        block == nullptr ? nullptr : block->searchRoom("A-102");

    SCMS::Reports::ReportGenerator reportGenerator;
    const std::string report = reportGenerator.loadTextReport();

    return people.size() == 4U
        && coursesLoaded
        && courses.size() == 1U
        && enrollments.size() == 2U
        && libraryLoaded
        && borrowedBook != nullptr
        && !borrowedBook->getIsAvailable()
        && financeLoaded
        && financeManager.searchRecordById("SAL-001") != nullptr
        && financeManager.searchRecordById("FEE-001") != nullptr
        && financeManager.getInvoices().size() == 1U
        && hostelLoaded
        && room != nullptr
        && room->hasOccupant("23-CS-001")
        && report.find("CONSOLIDATED REPORT") != std::string::npos;
}

bool testAppendPersistence() {
    std::vector<std::unique_ptr<Person>> people;
    people.push_back(std::make_unique<Student>(
        "Append Test Student",
        "99999-9999999-9",
        21,
        "0300-9999999",
        "APP-CS-001",
        "Computer Science",
        3.0F));
    if (!SCMS::Persistence::CampusPersistence::saveToFile(people, true)
        || SCMS::Persistence::CampusPersistence::loadPersons().size()
            < 5U) {
        return false;
    }

    const std::vector<Course> courses = {
        Course("APP-101", "Persistence Testing", 1, 1)
    };
    const std::vector<Enrollment> enrollments = {
        Enrollment("APP-CS-001", "APP-101", "Spring 2025", 'N')
    };
    if (!SCMS::Persistence::CampusPersistence::saveToFile(
            courses, enrollments, true)) {
        return false;
    }
    std::vector<Course> loadedCourses;
    std::vector<Enrollment> loadedEnrollments;
    if (!SCMS::Persistence::CampusPersistence::loadFromFile(
            loadedCourses, loadedEnrollments)
        || loadedCourses.size() < 2U
        || loadedEnrollments.size() < 3U) {
        return false;
    }

    LibraryManager library;
    if (!library.addItem(std::make_unique<Book>(
            "APP-B-001",
            "Persistence Handbook",
            true,
            "SCMS",
            "APP-ISBN-001",
            2026))
        || !library.registerMember(
            LibraryMember("APP-M-001", "Append Test Student"))
        || !library.issueItem("APP-B-001", "APP-M-001")
        || !SCMS::Persistence::CampusPersistence::saveToFile(
            library, true)) {
        return false;
    }
    LibraryManager loadedLibrary;
    if (!SCMS::Persistence::CampusPersistence::loadFromFile(
            loadedLibrary)
        || loadedLibrary.searchItemById("APP-B-001") == nullptr) {
        return false;
    }

    HostelBlock appendBlock("Block APP");
    if (!appendBlock.addRoom(Room("APP-101", "Single", 1, 1))) {
        return false;
    }
    HostelManager hostel("HOSTEL-APPEND");
    if (!hostel.addHostelBlock(appendBlock)
        || !hostel.allocateRoom(
            "Block APP", "APP-101", "APP-CS-001")
        || !SCMS::Persistence::CampusPersistence::saveToFile(
            hostel, true)) {
        return false;
    }
    HostelManager loadedHostel;
    if (!SCMS::Persistence::CampusPersistence::loadFromFile(
            loadedHostel)
        || loadedHostel.searchBlock("Block APP") == nullptr) {
        return false;
    }

    FinanceManager finance;
    if (!finance.addSalaryRecord(SalaryRecord(
            "SAL-APP",
            "Append salary",
            "2026-06-07",
            "EMP-APP",
            "Append Employee",
            1000.0,
            100.0,
            50.0))
        || !finance.addFeeRecord(FeeRecord(
            "FEE-APP",
            "Append fee",
            500.0,
            "2026-06-07",
            "APP-CS-001",
            "Append Test Student",
            "Spring 2025",
            false))
        || !finance.addInvoice(Invoice(
            "INV-APP-REC",
            "Append invoice",
            100.0,
            "2026-06-07",
            "INV-APP",
            "Append Test Student",
            {"Append Line"},
            false))
        || !SCMS::Persistence::CampusPersistence::saveToFile(
            finance, true)) {
        return false;
    }
    FinanceManager loadedFinance;
    if (!SCMS::Persistence::CampusPersistence::loadFromFile(
            loadedFinance)
        || loadedFinance.searchRecordById("SAL-APP") == nullptr
        || loadedFinance.searchRecordById("FEE-APP") == nullptr
        || loadedFinance.getInvoices().size() < 2U) {
        return false;
    }

    SCMS::Reports::ReportGenerator reportGenerator;
    if (!reportGenerator.saveToFile(
            "\nAPPEND MODE TEST\n", "data/scms_report.txt", true)) {
        return false;
    }
    return reportGenerator.loadFromFile().find("APPEND MODE TEST")
        != std::string::npos;
}

bool runSelectedOption(int option) {
    switch (option) {
        case personOption:
            return demonstratePersonModule();
        case courseOption:
            return demonstrateCourseModule();
        case libraryOption:
            return demonstrateLibraryModule();
        case financeOption:
            return demonstrateFinanceModule();
        case hostelOption:
            return demonstrateHostelModule();
        case reportsOption:
            return demonstrateReportsModule();
        case fullDemoOption:
            return runCompleteDemonstration();
        default:
            return false;
    }
}

}  // namespace

int main(int argumentCount, char* arguments[]) {
    try {
        if (!SCMS::Persistence::CampusPersistence::ensureDataFiles()) {
            std::cerr << "SCMS error: unable to prepare data files.\n";
            return 1;
        }

        if (argumentCount > 1
            && std::string(arguments[1]) == selfTestArgument) {
            const bool passed = runCompleteDemonstration();
            std::cout << (passed ? "\nSCMS SELF-TEST: PASS\n"
                                 : "\nSCMS SELF-TEST: FAIL\n");
            return passed ? 0 : 1;
        }
        if (argumentCount > 1
            && std::string(arguments[1]) == persistenceSeedArgument) {
            const bool passed = runCompleteDemonstration();
            std::cout << (passed
                ? "\nSCMS PERSISTENCE SEED: PASS\n"
                : "\nSCMS PERSISTENCE SEED: FAIL\n");
            return passed ? 0 : 1;
        }
        if (argumentCount > 1
            && std::string(arguments[1]) == persistenceVerifyArgument) {
            const bool passed = verifyPersistedData();
            std::cout << (passed
                ? "SCMS PERSISTENCE RELOAD: PASS\n"
                : "SCMS PERSISTENCE RELOAD: FAIL\n");
            return passed ? 0 : 1;
        }
        if (argumentCount > 1
            && std::string(arguments[1]) == persistenceAppendArgument) {
            const bool passed = testAppendPersistence();
            std::cout << (passed
                ? "SCMS PERSISTENCE APPEND: PASS\n"
                : "SCMS PERSISTENCE APPEND: FAIL\n");
            return passed ? 0 : 1;
        }

        printSplash();

        while (true) {
            printMenu();
            int option = exitOption;
            if (!(std::cin >> option)) {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a numeric menu option.\n";
                continue;
            }

            if (option == exitOption) {
                std::cout << "Exiting SCMS.\n";
                return 0;
            }

            const bool succeeded = runSelectedOption(option);
            std::cout << (succeeded ? "\nOperation completed successfully.\n"
                                    : "\nInvalid option or operation failed.\n");
        }
    } catch (const std::exception& exception) {
        std::cerr << "SCMS error: " << exception.what() << '\n';
        return 1;
    }
}

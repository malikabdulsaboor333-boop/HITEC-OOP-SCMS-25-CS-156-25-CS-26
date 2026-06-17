# Module Documentation

## Person Module

Folder: `src/person`

Purpose: Represents people on campus using abstraction, inheritance, encapsulation, and runtime polymorphism.

Classes: `Person`, `Student`, `Faculty`, `Staff`, `GradStudent`.

Responsibilities:

- Store common identity data in `Person`.
- Provide specialized data in derived classes.
- Validate names, CNIC, contact, age, roll numbers, salary, and CGPA.
- Display information through overridden `displayInfo()` functions.

Relationships: `Student`, `Faculty`, and `Staff` inherit from `Person`. `GradStudent` inherits from `Student`.

Example usage:

```cpp
std::unique_ptr<Person> p = std::make_unique<Student>(...);
p->displayInfo();
```

## Course Module

Folder: `src/course`

Purpose: Handles courses, enrollments, capacity checks, and custom exceptions.

Classes: `Course`, `Enrollment`, `EnrollmentException`, `CapacityExceededException`.

Responsibilities:

- Store course code, title, credit hours, capacity, and enrolled count.
- Associate courses with faculty.
- Associate enrollments with students.
- Prevent duplicate or over-capacity enrollment.
- Provide overloaded operators.

Validation: Course code/title cannot be empty, credit hours and capacity must be positive, enrollment data must be valid, and capacity cannot be exceeded.

## Library Module

Folder: `src/library`

Purpose: Manages library inventory, members, borrowing, templates, smart pointers, and overdue exceptions.

Classes: `LibraryItem`, `Book`, `Journal`, `LibraryMember`, `LibraryManager`, `Library<T>`, `OverdueException`.

Responsibilities:

- Store polymorphic items through `unique_ptr<LibraryItem>`.
- Register members.
- Issue and return items.
- Track borrowed item IDs.
- Demonstrate template search with `Library<T>` and `searchByTitle<T>()`.

Validation: Item IDs, titles, member data, author, ISBN, publisher, volume, issue, and publication year are validated.

## Finance Module

Folder: `src/finance`

Purpose: Handles financial records, salary, fees, invoices, counters, summaries, and CSV persistence.

Classes: `FinancialRecord`, `SalaryRecord`, `FeeRecord`, `Invoice`, `FinanceManager`.

Responsibilities:

- Store common financial record data.
- Calculate salary net pay.
- Track fee paid status.
- Store invoices and invoice line items.
- Save/load salary, fee, and invoice data.
- Generate finance summaries using a friend function.

Validation: IDs, dates, employee/student names, salary values, fee amounts, and invoice fields are validated.

## Hostel Module

Folder: `src/hostel`

Purpose: Demonstrates hostel room allocation using multiple inheritance, virtual inheritance, composition, and aggregation.

Classes: `BaseEntity`, `Accommodation`, `Reportable`, `Room`, `HostelBlock`, `HostelManager`.

Responsibilities:

- Store hostel entity identity.
- Allocate and vacate rooms.
- Generate hostel reports.
- Own hostel blocks and rooms.
- Store occupant roll numbers without owning student objects.

Validation: Room number cannot be empty, room type must be Single/Double/Triple, floor and capacity must be positive, and occupants cannot exceed capacity.

## Reports and Utilities Module

Folder: `src/utils`

Purpose: Provides reporting, validation utilities, CSV helpers, and campus-wide persistence.

Classes and structs: `ReportGenerator`, `UtilityManager`, `CsvUtils`, `CampusPersistence`, `StudentSummary`, `FacultySummary`, `CourseSummary`, `LibrarySummary`, `FeeSummary`, `HostelSummary`, `CampusReportData`.

Responsibilities:

- Generate campus reports.
- Export and load `data/scms_report.txt`.
- Validate email, CNIC, phone, numeric input, and strings.
- Prepare CSV files and parse CSV rows.
- Save/load data for all modules.

## Main Program

File: `src/main.cpp`

Purpose: Integrates all modules through menu options and automated test modes.

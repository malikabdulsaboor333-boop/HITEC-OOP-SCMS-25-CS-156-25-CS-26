# HITEC University Smart Campus Management System (SCMS)

## Project Information

| Field | Details |
| --- | --- |
| Project Title | Smart Campus Management System (SCMS) |
| Students | Abdul Saboor, Abdullah Sajjid |
| Roll Numbers | 25-CS-156, 25-CS-026 |
| Course | Object Oriented Programming |
| Instructor | Mohsin Shahzad |
| University | HITEC University |
| Language Standard | C++17 |

## Project Objective

The Smart Campus Management System is a modular C++17 project built for the Object-Oriented Programming course. Its objective is to demonstrate practical use of OOP concepts in a campus environment. The project models people, courses, library operations, finance records, hostel room allocation, reports, utilities, and CSV/TXT persistence.

The system is not a database application. Instead, it uses standard C++ classes, STL containers, smart pointers, exceptions, templates, file streams, and namespace-based utilities. The implementation is designed to be understandable for viva discussion and suitable for instructor evaluation.

## System Overview

The application starts from `src/main.cpp`, which provides a console menu and automated verification modes. Each module has separate `.h` and `.cpp` files. Data is saved in `data/` as CSV or TXT files. Documentation and UML artifacts are stored in `docs/`.

The main program demonstrates every module by creating objects, calling major functions, saving records, loading records, and printing results. It also includes command-line options for self-testing and persistence verification.

## Module Overview

| Module | Folder | Responsibility |
| --- | --- | --- |
| Person | `src/person` | Abstract person hierarchy with students, undergraduate students, faculty, and staff. |
| Course | `src/course` | Courses, enrollments, capacity checks, custom exceptions, and operator overloading. |
| Library | `src/library` | Library items, books, journals, members, borrowing, templates, and smart pointers. |
| Finance | `src/finance` | Salary records, fee records, invoices, static counters, friend summary, and CSV persistence. |
| Hostel | `src/hostel` | Room allocation, blocks, composition, aggregation, multiple inheritance, and virtual inheritance. |
| Reports/Utilities | `src/utils` | Reports, validation utilities, CSV helpers, campus persistence, lambdas, namespaces, and smart pointers. |

## Features List

- Abstract base classes and pure virtual functions.
- Runtime polymorphism using base-class pointers.
- Single inheritance, multilevel inheritance, multiple inheritance, and virtual inheritance.
- Encapsulation with private/protected data and public interfaces.
- Operator overloading in the course and finance modules.
- Custom exception classes for enrollment capacity and overdue library items.
- Rule of Three in `FeeRecord`.
- Rule of Five in `Invoice`.
- Class template `Library<T>` and function template `searchByTitle<T>()`.
- Composition in `FinanceManager`, `HostelManager`, `HostelBlock`, and `LibraryManager`.
- Aggregation through faculty/student pointers and roll-number-based hostel occupants.
- Smart pointers through `std::unique_ptr` and `std::shared_ptr`.
- STL algorithms and lambdas for sorting, searching, filtering, and counting.
- Namespaces: `SCMS::Reports`, `SCMS::Utils`, and `SCMS::Persistence`.
- Campus-wide CSV/TXT persistence under `data/`.
- UML source and rendered PNG in `docs/UML/`.

## Technology Stack

- C++17
- GCC / MinGW `g++`
- Standard Library only
- STL containers: `vector`, `set`, `map`
- Smart pointers: `unique_ptr`, `shared_ptr`
- File I/O: `ifstream`, `ofstream`
- `std::filesystem` for data folder preparation
- Markdown, Mermaid, PlantUML, and PNG documentation artifacts

## Generated Data Files

The persistence system prepares files such as `students.csv`, `courses.csv`, `library_items.csv`, `scms_finance_audit.csv`, `invoices.csv`, `hostel_allocations.csv`, and `scms_report.txt`. Invalid CSV rows are skipped safely during loading.

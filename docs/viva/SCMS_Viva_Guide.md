# SCMS Viva Guide

## 1. Project Overview

### What is SCMS?

The Smart Campus Management System (SCMS) is a C++17 console application that
models six university domains:

1. Person management
2. Course and enrollment management
3. Library management
4. Finance and payroll
5. Hostel management
6. Reporting and utilities

The project is organized as separate modules under `src/`. Each module focuses
on specific object-oriented programming concepts while the main program
demonstrates their integration.

### Purpose

SCMS was built to:

- represent university entities as classes;
- demonstrate core and advanced C++ OOP concepts;
- validate data at class boundaries;
- persist campus records in CSV and text files;
- exercise runtime polymorphism, templates, exceptions, STL, and RAII; and
- provide a single menu-driven demonstration program.

### Why a console application?

A console interface keeps the academic focus on object design, relationships,
algorithms, validation, persistence, and C++ behavior. A graphical interface
would introduce an unrelated UI framework and could hide the OOP concepts that
the project is meant to demonstrate. The menu in `src/main.cpp` still provides
clear module selection, error handling, and repeatable demonstrations.

### Why CSV persistence?

CSV is human-readable, portable, supported by `std::fstream`, and easy to
inspect during evaluation. It requires no external database or library. The
project protects CSV fields with escaping and parsing helpers, validates numeric
fields, skips malformed rows, and creates required data files automatically.

CSV is appropriate for this educational, single-process application. It would
not replace a transactional database in a concurrent production system.

## 2. System Interaction

```text
main.cpp
  |
  +-- creates and demonstrates module objects
  +-- calls public class interfaces
  +-- saves data through SCMS::Persistence::CampusPersistence
  +-- reloads persisted data for verification
  +-- feeds summary data to SCMS::Reports::ReportGenerator
```

The modules are not merged into one large class. They remain cohesive and
interact through public interfaces:

- `Course` can associate with `Faculty` and enrolled student roll numbers.
- `Enrollment` associates a `Student` and a `Course`.
- `LibraryManager` manages polymorphic `LibraryItem` objects and members.
- `FinanceManager` owns salary, fee, and invoice records.
- `HostelManager` owns hostel blocks; blocks own rooms; rooms retain student
  roll numbers rather than owning `Student` objects.
- `ReportGenerator` receives summary data instead of reaching into private
  module state.
- `CampusPersistence` serializes and reconstructs module data.

## 3. Fast Architecture Map

| Module | Main classes | Main concepts |
|---|---|---|
| Person | `Person`, `Student`, `Faculty`, `Staff`, `UndergradStudent` | abstraction, single and multilevel inheritance, polymorphism |
| Course | `Course`, `Enrollment`, exceptions | association, operators, exceptions, `set` |
| Library | `LibraryItem`, `Book`, `Journal`, `LibraryMember`, `LibraryManager`, `Library<T>` | abstraction, polymorphism, templates, smart pointers |
| Finance | `FinancialRecord`, `SalaryRecord`, `FeeRecord`, `Invoice`, `FinanceManager` | inheritance, composition, static data, friend functions, copy/move semantics |
| Hostel | `BaseEntity`, `Accommodation`, `Reportable`, `Room`, `HostelBlock`, `HostelManager` | multiple and virtual inheritance, composition, aggregation |
| Utilities | `ReportGenerator`, `UtilityManager`, `CampusPersistence` | nested namespaces, lambdas, algorithms, smart pointers, file I/O |

## 4. Runtime Story

At startup, `main()` asks `CampusPersistence` to ensure that the data directory
and required files exist. It then either:

- executes a command-line verification mode; or
- displays the interactive menu.

When a module option is selected, the matching demonstration function:

1. constructs valid domain objects;
2. calls the module's important operations;
3. demonstrates the intended OOP behavior;
4. saves records;
5. reloads records where applicable; and
6. catches expected custom exceptions without terminating the application.

The complete demonstration combines all module demonstrations with short-circuit
logical `&&`. Therefore, it reports success only if every demonstration returns
`true`.

## 5. Strong Viva Opening

> SCMS is a modular C++17 console application for university administration.
> I divided it into person, course, library, finance, hostel, and reporting
> modules. Each module demonstrates relevant OOP concepts rather than forcing
> every concept into one class. The system uses abstract base classes and
> runtime polymorphism for heterogeneous entities, composition for owned
> records, associations for non-owned relationships, STL containers and
> algorithms for data management, RAII and smart pointers for ownership, and
> CSV/text persistence through a dedicated nested namespace. The main program
> integrates and verifies all modules.

## 6. Five-Minute Demonstration Order

1. Show the folder structure and explain modular separation.
2. Show `Person` as an abstract base and `UndergradStudent` as multilevel
   inheritance.
3. Show `Course` operators and capacity exception handling.
4. Show `LibraryManager` storing `Book` and `Journal` through
   `std::unique_ptr<LibraryItem>`.
5. Show `FeeRecord` copy semantics and `Invoice` move semantics.
6. Draw the hostel diamond and explain virtual inheritance.
7. Show nested namespaces, lambdas, and persistence helpers.
8. Run the menu or `--self-test` and point to the generated data files.

## 7. Important Accuracy Notes

- The current multilevel class is `UndergradStudent`, not `GradStudent`.
- `Library<T>` is the class template; `searchByTitle<T>()` is the function
  template.
- `Course::operator+=` enrolls by roll number and checks capacity/duplicates.
- `Course::operator+` returns a modified copy rather than mutating the original.
- `FeeRecord` explicitly demonstrates copy construction and copy assignment.
- `Invoice` explicitly demonstrates copy and move operations.
- The hostel diamond has one shared `BaseEntity` subobject because both
  intermediate classes use virtual inheritance.
- Smart pointers are used for real ownership in the library and person
  demonstrations, not only as isolated syntax examples.
- Persistence loaders skip corrupted records; they do not silently treat bad
  numeric text as zero.

## 8. Questions Examiners Commonly Follow Up With

### Why is `Person` abstract?

The system should instantiate concrete roles such as students and faculty, not
a generic person with no role-specific display. The pure virtual
`displayInfo() const` creates that contract.

### Why is the base destructor virtual?

Derived objects can be destroyed through base pointers. A virtual destructor
ensures the complete derived destructor chain executes.

### Why use composition in managers?

The records belong to the manager's managed state and their lifetime follows
the owning container. Composition expresses that ownership more accurately than
inheritance.

### Why use virtual inheritance in the hostel module?

Without it, `HostelManager` would receive two `BaseEntity` subobjects through
`Accommodation` and `Reportable`. Virtual inheritance creates one shared base
and removes ambiguity.

### Why not store raw pointers?

Where ownership is needed, `std::unique_ptr` makes exclusive ownership explicit
and releases objects automatically. Non-owning relationships use references,
pointers with controlled lifetime, IDs, or roll numbers as appropriate.

## 9. Viva Checklist

Before the viva, be able to:

- draw all inheritance hierarchies without notes;
- distinguish composition, aggregation, and association;
- explain one successful and one rejected validation path per module;
- trace one CSV row from save to load;
- explain virtual dispatch through a base pointer;
- compare copy and move operations;
- explain why a `set` prevents duplicate course enrollment;
- identify the five STL algorithms used by the reporting utilities;
- explain the hostel diamond using object subobjects; and
- state the limitations of CSV and a console interface honestly.

## 10. Honest Project Limitations

- CSV files do not provide database transactions, concurrent updates, indexes,
  access control, or relational constraints.
- The console demonstrations are not a full interactive CRUD interface for
  every class.
- Cross-module relationships are primarily represented through IDs and public
  interfaces rather than a centralized repository.
- Persistence is suitable for local academic use, not multi-user deployment.
- Validation checks format and domain rules but is not a substitute for
  institutional identity verification.

These are design-scope limitations, not hidden failures. Explaining them clearly
shows engineering judgment.

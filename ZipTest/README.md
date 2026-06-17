# HITEC University Smart Campus Management System (SCMS)

A C++17 Object-Oriented Programming project for HITEC University. SCMS demonstrates campus workflows through modular source code, inheritance, runtime polymorphism, templates, exceptions, STL containers, smart pointers, file persistence, and reporting.

## Project Information

| Field | Details |
| --- | --- |
| Students | Abdul Saboor, Abdullah Sajjid |
| Roll Numbers | 25-CS-156, 25-CS-026 |
| Course | Object Oriented Programming |
| Instructor | Mohsin Shahzad |
| University | HITEC University |
| Language | C++17 |

## Features

- Person hierarchy with `Person`, `Student`, `Faculty`, `Staff`, and `GradStudent`.
- Course and enrollment management with operator overloading and custom exceptions.
- Library management with `Book`, `Journal`, `LibraryMember`, `LibraryManager`, `Library<T>`, smart pointers, and overdue handling.
- Finance and payroll with salary records, fee records, invoices, static counters, friend summary, Rule of Three, Rule of Five, and CSV persistence.
- Hostel management with multiple inheritance, virtual inheritance, room allocation, composition, and aggregation.
- Reports and utilities using namespaces, lambdas, STL algorithms, smart pointers, and TXT export.
- Campus-wide CSV/TXT persistence under `data/`.
- Automated self-test and persistence verification modes.
- UML and professional documentation under `docs/`.

## Folder Structure

```text
src/
├── person/
├── course/
├── library/
├── finance/
├── hostel/
├── utils/
└── main.cpp

data/
└── generated CSV/TXT persistence files

docs/
├── PROJECT_OVERVIEW.md
├── SYSTEM_ARCHITECTURE.md
├── OOP_CONCEPTS.md
├── MODULE_DOCUMENTATION.md
├── UML_DOCUMENTATION.md
├── INSTALLATION_GUIDE.md
├── VIVA_PREPARATION.md
├── TESTING_REPORT.md
└── UML/
```

## Build Instructions

From the repository root in PowerShell:

```powershell
$sources = Get-ChildItem src -Recurse -Filter *.cpp
g++ -std=c++17 -Wall -Wextra $sources.FullName -o scms.exe
```

Strict build:

```powershell
$sources = Get-ChildItem src -Recurse -Filter *.cpp
g++ -std=c++17 -Wall -Wextra -Werror $sources.FullName -o scms.exe
```

## Run Instructions

Interactive menu:

```powershell
.\scms.exe
```

Automated checks:

```powershell
.\scms.exe --self-test
.\scms.exe --persistence-seed
.\scms.exe --persistence-verify
.\scms.exe --persistence-append-test
```

## OOP Concepts Implemented

- Classes and objects
- Encapsulation
- Single, multilevel, multiple, and virtual inheritance
- Abstract classes and pure virtual functions
- Runtime polymorphism
- Operator overloading
- Friend functions and friend class
- Static members
- Rule of Three and Rule of Five
- Function templates and class templates
- Composition and aggregation
- Smart pointers
- Lambda expressions
- Namespaces and nested namespaces
- File I/O
- Exceptions
- STL containers and algorithms
- Validation

## Screenshots Placeholders

Add screenshots here if required by the instructor:

```text
[Main Menu Screenshot]
[Module Demonstration Screenshot]
[Persistence Files Screenshot]
[UML Diagram Screenshot]
```

## Documentation

Professional documentation is available under `docs/`. UML source and rendered image artifacts are available under `docs/UML/`.

## Author Information

Prepared by Abdul Saboor and Abdullah Sajjid for Object Oriented Programming at HITEC University under the supervision of Mohsin Shahzad.

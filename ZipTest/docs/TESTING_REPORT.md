# Testing Report

## Compilation Verification

Standard build command:

```powershell
$sources = Get-ChildItem src -Recurse -Filter *.cpp
g++ -std=c++17 -Wall -Wextra $sources.FullName -o scms.exe
```

Strict build command:

```powershell
$sources = Get-ChildItem src -Recurse -Filter *.cpp
g++ -std=c++17 -Wall -Wextra -Werror $sources.FullName -o scms.exe
```

Expected result: zero errors and zero warnings.

## Runtime Verification

Main command:

```powershell
.\scms.exe
```

The program displays a menu for Person, Course, Library, Finance, Hostel, Reports, Complete Demonstration, and Exit.

## Automated Verification Modes

| Command | Purpose | Expected Result |
| --- | --- | --- |
| `.\scms.exe --self-test` | Runs every module demonstration | `SCMS SELF-TEST: PASS` |
| `.\scms.exe --persistence-seed` | Writes canonical CSV/TXT data | `SCMS PERSISTENCE SEED: PASS` |
| `.\scms.exe --persistence-verify` | Reloads saved data | `SCMS PERSISTENCE RELOAD: PASS` |
| `.\scms.exe --persistence-append-test` | Tests append mode | `SCMS PERSISTENCE APPEND: PASS` |

## Module Tests

Person module: creates `Student`, `Faculty`, `Staff`, and `GradStudent` through `unique_ptr<Person>` and checks runtime polymorphism.

Course module: tests valid enrollment, capacity overflow, duplicate prevention, faculty association, and overloaded operators.

Library module: tests adding `Book`/`Journal`, registering a member, issuing and returning a book, template `Library<Book>`, and overdue exception behavior.

Finance module: tests salary, fee, invoice, discount operator, friend summary, CSV persistence, invoice persistence, and static counters.

Hostel module: tests block creation, room creation, allocation, report generation, vacation, multiple inheritance, and diamond-problem resolution.

Reports/utilities module: tests report generation, TXT export/load, email validation, smart pointer factories, lambdas, and STL algorithms.

## Exception Tests

- `CapacityExceededException` is tested when course capacity is exceeded.
- `EnrollmentException` protects invalid enrollment/course data.
- `OverdueException` is tested for overdue library items.
- `std::invalid_argument` protects invalid values throughout validation methods.

## Persistence Tests

The system creates and reloads CSV/TXT data under `data/`. Persistence includes people, courses, enrollments, library items, library members, borrowings, hostel blocks, rooms, allocations, finance records, invoices, finance summary, and report text.

## Final Results

| Area | Status |
| --- | --- |
| Compilation | PASS |
| Runtime menu | PASS |
| Person module | PASS |
| Course module | PASS |
| Library module | PASS |
| Finance module | PASS |
| Hostel module | PASS |
| Reports/utilities | PASS |
| CSV/TXT persistence | PASS |
| Exception handling | PASS |
| Validation | PASS |

Final status: submission-ready when compiled and executed from the repository root.

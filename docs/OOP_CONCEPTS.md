# Object-Oriented Programming Concepts

This document maps required OOP concepts to the actual SCMS source code.

## 1. Classes

Definition: A class is a blueprint containing data and functions.

Where used: `Student`, `Course`, `LibraryManager`, `FinanceManager`, `Room`, `ReportGenerator`, and others.

Example:

```cpp
class Student : public Person {
private:
    std::string rollNo;
    std::string department;
    float cgpa;
};
```

## 2. Objects

Objects are class instances. `main.cpp` creates objects such as `Course course(...)`, `LibraryManager manager`, and `HostelManager manager`.

## 3. Encapsulation

Data is private or protected and accessed through public functions. Example: `Student` keeps `rollNo`, `department`, and `cgpa` private and exposes getters/setters.

## 4. Inheritance

Inheritance appears in person, library, finance, hostel, and exception hierarchies.

```text
Student -> Person
Book -> LibraryItem
SalaryRecord -> FinancialRecord
```

## 5. Multilevel Inheritance

`UndergradStudent -> Student -> Person` demonstrates multilevel inheritance.

## 6. Multiple Inheritance

`HostelManager` inherits from both `Accommodation` and `Reportable`.

```cpp
class HostelManager : public Accommodation, public Reportable
```

## 7. Virtual Inheritance

`Accommodation` and `Reportable` virtually inherit from `BaseEntity`, solving the diamond problem.

## 8. Abstract Classes

`Person`, `LibraryItem`, `BaseEntity`, `Accommodation`, and `Reportable` are abstract because they define pure virtual functions.

## 9. Runtime Polymorphism

`Person` pointers call derived `displayInfo()` functions. `LibraryManager` stores `Book` and `Journal` as `unique_ptr<LibraryItem>`. Hostel interface pointers call overridden functions on `HostelManager`.

## 10. Operator Overloading

Implemented operators:

- `Course::operator+=`
- `Course::operator+`
- `Course::operator==`
- `operator<<` for `Course`
- `FeeRecord::operator-=`

## 11. Friend Functions

`generateFinanceSummary()` accesses private finance data. `operator<<` is a friend of `Course`.

## 12. Static Members

Static counters exist in `SalaryRecord`, `FeeRecord`, and `Invoice`.

## 13. Rule of Three

`FeeRecord` defines copy constructor, copy assignment operator, and destructor.

## 14. Rule of Five

`Invoice` defines copy constructor, copy assignment, move constructor, move assignment, and destructor.

## 15. Function Templates

`searchByTitle<T>()` searches a vector of objects by title.

## 16. Class Templates

`Library<T>` stores typed library items and maintains `vector`, `map`, and `set` structures.

## 17. Composition

Strong ownership relationships:

- `FinanceManager` owns salary, fee, and invoice records.
- `HostelManager` owns hostel blocks.
- `HostelBlock` owns rooms.
- `LibraryManager` owns library items and members.

## 18. Aggregation

Non-owning relationships:

- `Course` references `Faculty`.
- `Enrollment` references `Student`.
- `Room` stores student roll numbers.

## 19. Smart Pointers

`unique_ptr` is used for `Person`, `LibraryItem`, and `ReportGenerator`. `shared_ptr` is used for `UtilityManager`.

## 20. Lambdas

Lambdas are used with STL algorithms for sorting students, filtering overdue records, counting unpaid fees, searching collections, and persistence parsing.

## 21. Namespaces

The project defines `SCMS::Reports`, `SCMS::Utils`, and `SCMS::Persistence`.

## 22. File I/O

File I/O is implemented using `ifstream` and `ofstream` in Finance, Reports, CsvUtils, and CampusPersistence.

## 23. Exceptions

Custom exceptions include `EnrollmentException`, `CapacityExceededException`, and `OverdueException`. Validation also uses `std::invalid_argument`.

## 24. STL Containers

The project uses `vector`, `set`, `map`, smart pointers, and STL algorithms throughout.

## 25. Validation

Validation checks non-empty IDs, positive age, valid CGPA, valid capacity, positive amounts, supported room types, duplicate prevention, and safe CSV numeric parsing.

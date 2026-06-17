# Module Explanations

## Module 1: Person Hierarchy

### Instructor Requirement

Demonstrate abstraction, encapsulation, single inheritance, multilevel
inheritance, constructor chaining, virtual functions, runtime polymorphism, and
a virtual destructor.

### Actual Classes

- `Person`: abstract base class
- `Student`: derives from `Person`
- `Faculty`: derives from `Person`
- `Staff`: derives from `Person`
- `UndergradStudent`: derives from `Student`

### Relationships

```text
Person
|-- Student
|   `-- UndergradStudent
|-- Faculty
`-- Staff
```

### Responsibilities

`Person` owns common identity fields and declares `displayInfo() const` as pure
virtual. Derived classes add role-specific data and implement display behavior.
`UndergradStudent` adds a project title and academic advisor while preserving
the `Person -> Student -> UndergradStudent` multilevel chain.

### Validation

Setters and constructors reject invalid common or role-specific data, including
empty identifiers and invalid numeric values such as non-positive age or
out-of-range CGPA.

### Design Choice

Common data belongs in `Person` to avoid duplication. Role-specific data remains
private in each derived class. Runtime polymorphism lets one container hold
different roles through `Person` pointers.

### Example

```cpp
std::unique_ptr<Person> person =
    std::make_unique<Student>(/* validated values */);
person->displayInfo();
```

The call resolves to `Student::displayInfo()` at runtime.

## Module 2: Course and Enrollment

### Instructor Requirement

Demonstrate encapsulation, operator overloading, custom exceptions, and
associations between students, courses, and faculty.

### Actual Classes

- `Course`
- `Enrollment`
- `EnrollmentException`
- `CapacityExceededException`

### Relationships

- A `Course` can hold a non-owning association to a `Faculty` instructor.
- An `Enrollment` associates a student and a course.
- Course membership is represented by student roll numbers in a `std::set`.

### Major Operations

- `Course::operator+=`: enrolls a roll number into the current course.
- `Course::operator+`: returns a copied course with an additional enrollment.
- `Course::operator==`: compares course codes.
- `operator<<`: writes formatted course information to a stream.
- `Enrollment::displayEnrollmentInfo()`: displays association data.

### Validation

Course codes/titles cannot be empty, credit hours and capacity must be valid,
enrollment data must be complete, grades must be accepted values, duplicate
roll numbers are rejected, and enrollment beyond capacity throws
`CapacityExceededException`.

### Design Choice

The `set` naturally enforces uniqueness. Custom exceptions express domain
failures more precisely than generic return codes. Operators are used only where
their meaning remains understandable.

## Module 3: Library Management

### Instructor Requirement

Demonstrate abstraction, inheritance, runtime polymorphism, dynamic binding,
STL containers, templates, and exception handling.

### Actual Classes and Templates

- `LibraryItem`: abstract base class
- `Book`, `Journal`: concrete items
- `LibraryMember`
- `LibraryManager`
- `OverdueException`
- `Library<T>`: class template
- `searchByTitle<T>()`: function template

### Relationships

`LibraryManager` owns `Book` and `Journal` instances through
`std::unique_ptr<LibraryItem>`. It also manages member values. A member stores
borrowed item IDs, not item objects.

### Major Operations

- add, remove, and search for items;
- register and search for members;
- issue and return items;
- display inventory;
- template-based collection and title search.

### State Consistency

Issuing requires an existing member and available item. A successful issue marks
the item unavailable and adds its ID to the member. Returning reverses both
changes. Invalid operations throw exceptions instead of partially changing
state.

### Validation

IDs and names/titles must be non-empty. Book and journal numeric fields are
validated. Duplicate items and members are rejected.

### Design Choice

`unique_ptr` gives the manager exclusive ownership while enabling heterogeneous
storage. Templates provide reusable compile-time behavior for typed item
collections without duplicating classes.

## Module 4: Finance and Payroll

### Instructor Requirement

Demonstrate encapsulation, inheritance, composition, static members, friend
functions, validation, copy semantics, move semantics, operators, and file I/O.

### Actual Classes

- `FinancialRecord`
- `SalaryRecord`
- `FeeRecord`
- `Invoice`
- `FinanceManager`

### Relationships

`SalaryRecord` and `FeeRecord` derive from `FinancialRecord`.
`FinanceManager` contains vectors of salary records, fee records, and invoices.
This is composition because the manager owns the stored values.

### Major Operations

- salary calculation: basic salary + allowance - deduction;
- paid-fee total calculation;
- invoice line-item and total management;
- search/remove/display records;
- CSV save/load;
- friend-generated finance summary.

### Copy and Move Semantics

`FeeRecord` explicitly defines copy construction and assignment to demonstrate
Rule-of-Three-style copy control. `Invoice` defines destructor, copy
construction/assignment, and move construction/assignment, demonstrating the
Rule of Five even though its STL members already manage memory safely.

### Static Members

Salary, fee, and invoice classes maintain class-wide counters. A static member
belongs to the class rather than a single instance. Invoice persistence also
restores the counter so newly generated IDs do not collide with loaded data.

### Friend Usage

`generateFinanceSummary()` is declared as a friend where it needs direct access
to manager-owned financial data. Friendship is deliberately narrow and is not
inheritance.

### Validation

IDs, descriptions, names, and dates must be present. Amounts and salary
components obey domain constraints. Deductions cannot produce invalid financial
state. Invalid CSV rows are skipped during loading.

## Module 5: Hostel Management

### Instructor Requirement

Demonstrate abstract classes, multiple inheritance, virtual inheritance,
diamond-problem resolution, composition, aggregation, runtime polymorphism, STL
containers, and room allocation.

### Actual Classes

- `BaseEntity`: abstract common base
- `Accommodation`: abstract virtual base path
- `Reportable`: abstract virtual base path
- `Room`
- `HostelBlock`
- `HostelManager`

### Diamond Structure

```text
          BaseEntity
          /        \
  Accommodation  Reportable
          \        /
          HostelManager
```

Both intermediate classes inherit `virtual public BaseEntity`. Therefore,
`HostelManager` contains one shared `BaseEntity` subobject.

### Composition

`HostelManager` owns `HostelBlock` values, and each `HostelBlock` owns `Room`
values. Their lifetimes are controlled by the containing objects.

### Aggregation

`Room` stores student roll numbers as occupants. It refers to externally
existing students but does not own or destroy `Student` objects.

### Allocation Flow

1. Find block.
2. Find room.
3. validate student roll number.
4. reject duplicate assignment.
5. check capacity.
6. add occupant.

Vacating verifies the same hierarchy and removes the roll number safely.

### Validation

Entity IDs, block names, room numbers, and room types are validated. Floors and
capacities must be positive. Supported room types and their capacities are
consistent, and occupancy cannot exceed capacity.

## Module 6: Reports, Utilities, and Persistence

### Instructor Requirement

Demonstrate user-defined and nested namespaces, smart pointers, lambdas, STL
algorithms, formatted reporting, reusable validation, and modern C++17 design.

### Actual Namespaces and Classes

- `SCMS::Reports::ReportGenerator`
- `SCMS::Reports::CampusReportData` and summary structures
- `SCMS::Utils::UtilityManager`
- `SCMS::Persistence::CsvUtils`
- `SCMS::Persistence::CampusPersistence`

### Reporting

The report generator receives summary structures and returns formatted strings
for students, courses, library, finance, hostel, and the consolidated campus
report. It can export and reload text reports.

### Utilities

Static utility functions format text, validate numeric input, email, CNIC, and
phone values, obtain the current date, change case, and trim whitespace.

### Lambdas and Algorithms

The reporting/utilities code uses lambdas with algorithms to sort students by
GPA, locate overdue records, copy/filter unpaid fees, count matching records,
and process collections.

### Smart Pointers

The integration demonstration creates a report generator with `unique_ptr` and
shares a utility manager with `shared_ptr`. Library and person demonstrations
also use smart pointers for meaningful object ownership.

### Persistence

`CampusPersistence` centralizes data-folder setup and module save/load
operations. `CsvUtils` handles escaping, parsing, headers, append mode, and safe
numeric conversion. This keeps file-format concerns out of most domain classes.

## Cross-Module Design Summary

| Relationship | Actual example |
|---|---|
| Single inheritance | `Student -> Person` |
| Multilevel inheritance | `UndergradStudent -> Student -> Person` |
| Multiple inheritance | `HostelManager -> Accommodation, Reportable` |
| Virtual inheritance | both hostel interfaces virtually inherit `BaseEntity` |
| Composition | manager vectors; `HostelBlock` owns rooms |
| Aggregation | room occupant roll numbers |
| Association | course/instructor and enrollment/student/course links |
| Runtime polymorphism | `Person*`, `LibraryItem*`, hostel base pointers |
| Compile-time polymorphism | templates and overloaded operators |

## Module Viva Strategy

For each module, answer in this order:

1. State its responsibility.
2. Name its classes.
3. Draw its relationships.
4. identify its main validation rule.
5. identify its principal OOP concept.
6. trace one operation from input to state change and persistence.

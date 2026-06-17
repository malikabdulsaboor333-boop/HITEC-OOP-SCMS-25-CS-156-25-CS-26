# `main.cpp` Breakdown

## 1. Role of `main.cpp`

`src/main.cpp` is the integration and demonstration layer. It does not define
domain classes. It includes their public headers, constructs representative
objects, exercises each module, invokes persistence, catches exceptions, and
provides a menu plus command-line verification modes.

## 2. Include Groups

The file includes:

- person headers for `Student`, `Faculty`, `Staff`, and
  `UndergradStudent`;
- course headers for `Course`, `Enrollment`, and custom exceptions;
- library headers for items, members, manager, exceptions, and templates;
- finance headers for records, invoices, manager, and summary support;
- hostel headers for rooms, blocks, interfaces, and manager;
- utility headers for reports, validation, and persistence; and
- standard headers such as I/O, memory, containers, strings, and exceptions.

Including public headers allows the compiler to see declarations. Definitions
remain in `.cpp` files and are joined by the linker.

## 3. Anonymous Namespace

Helper constants and demonstration functions are placed in an anonymous
namespace. This gives them internal linkage: they are visible only inside
`main.cpp` and cannot collide with symbols in other translation units.

## 4. Function-by-Function Explanation

### `void printSplash()`

**Syntax:** A free function returning `void` and accepting no parameters.

**Purpose:** Prints the SCMS branding and introductory banner.

**Control flow:** Straight-line output statements.

**Runtime behavior:** Called once before the interactive menu. It has no
persistent state and does not modify any module.

### `void printMenu()`

**Purpose:** Displays numbered module choices, the complete demonstration
choice, and the exit choice.

**Control flow:** Straight-line output.

**Runtime behavior:** Called on every menu-loop iteration so the user can make a
new selection.

### `bool demonstratePersonModule()`

**Purpose:** Demonstrates the person hierarchy.

**Important syntax:**

```cpp
std::vector<std::unique_ptr<Person>>
```

Concrete objects are owned through abstract base pointers. Calling
`displayInfo()` uses virtual dispatch and invokes the correct override.

**Control flow:**

1. Construct student, faculty, staff, and undergraduate-student objects.
2. Store them polymorphically.
3. Display each object through `Person`.
4. Save person records.
5. Reload persisted records.
6. Return a Boolean verification result.

**Runtime behavior:** Demonstrates abstraction, inheritance, multilevel
inheritance, ownership through `unique_ptr`, and persistence.

### `bool demonstrateCourseModule()`

**Purpose:** Demonstrates course enrollment, associations, operators, and
exceptions.

**Control flow:**

1. Construct a faculty member and students.
2. Construct a course and associate its instructor.
3. Create enrollment records.
4. Use `operator+` and `operator+=` to enroll roll numbers.
5. Compare course objects with `operator==`.
6. print a course with `operator<<`.
7. save and reload course/enrollment data.
8. deliberately test capacity handling in a `try/catch`.

**Runtime behavior:** Capacity or duplicate failures become custom exceptions
instead of invalid object state.

### `bool demonstrateLibraryModule()`

**Purpose:** Demonstrates an abstract item hierarchy, library operations,
templates, smart pointers, and overdue exceptions.

**Control flow:**

1. Create a `LibraryManager`.
2. Add `Book` and `Journal` objects as
   `std::unique_ptr<LibraryItem>`.
3. Register a member.
4. Issue an item and update availability/borrowed IDs.
5. Save and reload library data.
6. Return an item.
7. exercise `OverdueException`.
8. demonstrate `Library<Book>` and title searching.

**Runtime behavior:** The manager owns heterogeneous items safely and keeps item
availability consistent with member borrowing state.

### `bool demonstrateFinanceModule()`

**Purpose:** Demonstrates finance records, calculations, copy/move behavior,
static counters, friend access, and CSV persistence.

**Control flow:**

1. Construct salary and fee records.
2. Copy a `FeeRecord` and apply `operator-=`.
3. Construct and move an `Invoice`.
4. Add records to `FinanceManager`.
5. Save and reload CSV data.
6. calculate totals and produce a finance summary.
7. display or verify static counters.

**Runtime behavior:** Validation prevents invalid monetary records. Containers
own records by value, while explicit copy/move functions make object semantics
visible for academic evaluation.

### `bool demonstrateHostelModule()`

**Purpose:** Demonstrates multiple inheritance, virtual inheritance, room
allocation, composition, aggregation, and polymorphism.

**Control flow:**

1. Construct rooms and add them to a block.
2. Add the block to `HostelManager`.
3. access the manager through `Accommodation*`, `Reportable*`, and
   `BaseEntity*`.
4. allocate a room.
5. save and reload hostel data.
6. generate a report.
7. vacate the room.
8. verify that both inheritance paths lead to the same `BaseEntity` address.

**Runtime behavior:** Virtual calls dispatch to `HostelManager`; one virtual
base prevents the diamond ambiguity.

### `bool demonstrateReportsModule()`

**Purpose:** Demonstrates nested namespaces, report formatting, smart pointers,
utility validation, lambdas, algorithms, and report persistence.

**Control flow:**

1. Create `ReportGenerator` with `std::unique_ptr`.
2. Create or access `UtilityManager` with `std::shared_ptr`.
3. populate summary structures.
4. generate student, course, library, finance, hostel, and campus text.
5. export and reload the report.
6. call validators such as email validation.

**Runtime behavior:** Reporting consumes structured summaries and returns
formatted strings without violating module encapsulation.

### `bool runCompleteDemonstration()`

**Purpose:** Runs all six module demonstrations.

**Syntax concept:** The return expression combines Boolean results with `&&`.

**Control flow:** Logical AND short-circuits. If one module returns `false`,
later operands may not execute.

**Runtime behavior:** Returns `true` only when all executed module checks pass.

### `bool verifyPersistedData()`

**Purpose:** Proves that previously saved records survive a process restart.

**Control flow:**

1. Load each module's files.
2. search for known identifiers and expected counts.
3. combine checks into a final Boolean result.

**Runtime behavior:** This mode reads existing files rather than relying on
in-memory objects created during the same run.

### `bool testAppendPersistence()`

**Purpose:** Verifies append-mode behavior.

**Control flow:**

1. Save additional valid records using append mode.
2. reload the affected files.
3. search for the appended identifiers.
4. return whether all appended records can be recovered.

**Runtime behavior:** Confirms that appending does not erase the existing CSV
header or earlier rows.

### `bool runSelectedOption(int choice)`

**Purpose:** Central dispatcher for menu selections.

**Syntax concept:** A `switch` selects one branch based on an integer.

**Control flow:** Each `case` calls one demonstration and returns its result.
The default branch reports invalid input.

**Runtime behavior:** Keeps menu input separate from module implementation.

### `int main(int argc, char* argv[])`

**Purpose:** Program entry point.

**Parameters:**

- `argc` is the number of command-line arguments.
- `argv` is an array of C-style argument strings.

**Startup flow:**

1. Ensure the data directory and required files exist.
2. Inspect optional command-line mode.
3. Run self-test, seed, verification, or append-test mode when requested.
4. Otherwise print the splash and start the menu loop.

**Menu flow:**

1. Print menu.
2. read an integer choice.
3. recover from invalid stream input by clearing error flags and discarding the
   bad line.
4. exit on the exit choice.
5. dispatch valid choices.
6. catch `std::exception` so a module error does not abruptly terminate the
   whole program.

**Return value:** Conventionally, `0` means success and a non-zero value means
failure in command-line verification modes.

## 5. Input Validation in the Menu

Formatted extraction can fail when the user types letters instead of a number.
The program checks the stream state, calls `clear()` to reset failure flags, and
uses `ignore()` to discard invalid input. This prevents an infinite loop.

## 6. Why the Demonstrations Return `bool`

A demonstration does more than print. It performs checks and reports success or
failure to the caller. This makes the same functions useful for interactive
use and automated self-verification.

## 7. Why Exceptions Are Caught Near Integration

Domain classes throw when an operation is invalid. `main.cpp` catches exceptions
at a boundary where an error can be reported to the user and the program can
continue. This separates error detection from presentation.

## 8. Likely Viva Questions

1. **Why use a `switch`?** It clearly maps one integer menu choice to one action.
2. **Why use an anonymous namespace?** It gives helper symbols internal linkage.
3. **Why return `bool` from demos?** It supports repeatable verification.
4. **Why pass through base pointers?** To prove runtime polymorphism.
5. **Why clear and ignore `std::cin`?** To recover from invalid formatted input.
6. **What does short-circuiting mean?** Later `&&` operands are not evaluated
   after the first false operand.
7. **Why support command-line modes?** They make persistence and complete-system
   checks repeatable without navigating the interactive menu.

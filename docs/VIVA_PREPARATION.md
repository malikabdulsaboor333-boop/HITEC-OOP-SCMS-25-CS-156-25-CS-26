# Viva Preparation

## 50 Likely Viva Questions and Answers

1. What is SCMS?

SCMS is a C++17 Smart Campus Management System that demonstrates OOP concepts through person, course, library, finance, hostel, reporting, utility, and persistence modules.

2. What is the main objective of the project?

The objective is to implement a modular campus system that visibly demonstrates classes, objects, inheritance, polymorphism, templates, exceptions, file handling, and STL usage.

3. Which file starts the application?

`src/main.cpp` starts the application and provides the menu plus automated test modes.

4. What is an abstract class?

An abstract class has at least one pure virtual function and cannot be instantiated directly.

5. Which classes are abstract in SCMS?

`Person`, `LibraryItem`, `BaseEntity`, `Accommodation`, and `Reportable`.

6. Why is `Person` abstract?

A generic person is incomplete in this system. Real objects are `Student`, `Faculty`, `Staff`, and `UndergradStudent`.

7. What is runtime polymorphism?

Runtime polymorphism means the correct overridden function is chosen at runtime through a base pointer or reference.

8. Where is runtime polymorphism used?

`Person` pointers call `displayInfo()`, `LibraryItem` pointers call item display functions, and hostel interface pointers call `HostelManager` functions.

9. What is encapsulation?

Encapsulation hides data members and exposes controlled functions. Most classes use private data with getters and setters.

10. Give an example of single inheritance.

`Student`, `Faculty`, and `Staff` inherit from `Person`.

11. Give an example of multilevel inheritance.

`UndergradStudent -> Student -> Person`.

12. Give an example of multiple inheritance.

`HostelManager` inherits from `Accommodation` and `Reportable`.

13. What is virtual inheritance?

Virtual inheritance prevents duplicate base subobjects in a diamond hierarchy.

14. Where is virtual inheritance used?

`Accommodation` and `Reportable` virtually inherit from `BaseEntity`.

15. What is the diamond problem?

It happens when one class inherits the same base class through multiple paths. SCMS resolves it in the hostel hierarchy.

16. What is composition?

Composition means strong ownership. Example: `HostelBlock` owns `Room` objects.

17. What is aggregation?

Aggregation means non-owning association. Example: `Course` references `Faculty` through a pointer.

18. Why does `Room` store roll numbers?

The hostel module should not own `Student` objects. It stores roll numbers to represent aggregation safely.

19. What does `Course::operator+=` do?

It enrolls a student after validation, duplicate checking, and capacity checking.

20. What does `Course::operator==` compare?

It compares two courses by course code.

21. What does `FeeRecord::operator-=` do?

It applies a positive discount to a fee record while keeping the amount positive.

22. What is a friend function?

A friend function can access private class members. `generateFinanceSummary()` is a friend function.

23. Which class has a friend class?

`Invoice` declares `FinanceManager` as a friend class.

24. Why does `Invoice` need Rule of Five?

It demonstrates copy and move semantics for an object that owns a vector of line items.

25. Where is Rule of Three used?

`FeeRecord` defines copy constructor, copy assignment, and destructor.

26. Where are static members used?

`SalaryRecord::totalSalaryRecords`, `FeeRecord::totalFeeRecords`, and `Invoice::invoiceCounter`.

27. What template class exists?

`Library<T>` in `src/library/Library.h`.

28. What function template exists?

`searchByTitle<T>()`, which searches a vector for a matching title.

29. Why use `unique_ptr<LibraryItem>`?

It safely owns polymorphic `Book` and `Journal` objects without raw `new` or `delete`.

30. Where is `shared_ptr` used?

`UtilityManager::createShared()` returns a `std::shared_ptr<UtilityManager>`.

31. Which namespaces exist?

`SCMS::Reports`, `SCMS::Utils`, and `SCMS::Persistence`.

32. Where are lambdas used?

They are used with STL algorithms for sorting, searching, filtering, counting, and persistence parsing.

33. Which custom exceptions exist?

`EnrollmentException`, `CapacityExceededException`, and `OverdueException`.

34. When is `CapacityExceededException` used?

When course enrollment exceeds maximum capacity.

35. What does `LibraryManager` do?

It owns library items and members, and supports item search, issue, return, inventory display, and overdue checking.

36. What does `FinanceManager` do?

It owns salary records, fee records, and invoices, and supports searching, summaries, and persistence.

37. What does `HostelManager` do?

It manages hostel blocks, room allocation, room vacation, and hostel reports.

38. What does `ReportGenerator` do?

It generates formatted reports for students, faculty, courses, library, finance, hostel, and the full campus report.

39. What does `UtilityManager` do?

It validates numeric input, email, CNIC, phone, and provides string formatting and date/time helpers.

40. What does `CsvUtils` do?

It creates parent folders, ensures files exist, writes CSV headers, escapes CSV text, parses rows, and validates numeric conversion.

41. What does `CampusPersistence` do?

It saves and loads campus data for person, course, library, hostel, and finance summary modules.

42. What files are generated in `data/`?

CSV files for people, courses, enrollments, library, hostel, finance, invoices, and a text report file `scms_report.txt`.

43. How are corrupted CSV rows handled?

Loaders skip malformed rows safely instead of crashing.

44. What is constructor chaining?

Derived constructors call base constructors, such as `Student` calling `Person`.

45. Why are header guards used?

They prevent the same header from being included multiple times.

46. Why are declarations and definitions separated?

Headers expose class declarations, while `.cpp` files contain implementations, improving organization and compile clarity.

47. How do you build the project?

Collect all `.cpp` files and compile with `g++ -std=c++17 -Wall -Wextra`.

48. How do you run the self-test?

Run `.\scms.exe --self-test`.

49. What is the strongest OOP demonstration?

The hostel hierarchy clearly demonstrates multiple inheritance, virtual inheritance, abstraction, composition, and aggregation together.

50. What could be improved in the future?

A future version could add a full interactive CRUD interface and richer reporting, while keeping the existing OOP design.

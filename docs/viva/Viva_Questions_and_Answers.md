# 100 SCMS Viva Questions and Answers

## Project and Architecture

### Q1. What is the Smart Campus Management System?

SCMS is a modular C++17 console application that models person, course,
library, finance, hostel, reporting, utility, and persistence responsibilities
for a university. It is designed primarily to demonstrate OOP concepts through
working, integrated code.

### Q2. Why was the project divided into modules?

Each module has one cohesive domain responsibility and a focused set of OOP
concepts. This reduces coupling, makes classes easier to test, and avoids one
large class knowing every detail of the system.

### Q3. Why did you use C++17?

C++17 provides the language and standard-library features used by the project,
including `std::filesystem`, smart pointers, lambdas, algorithms, and modern
move semantics. It also matches the required compilation standard.

### Q4. Why is the application console based?

The console keeps attention on object design, validation, algorithms, and
persistence instead of a GUI framework. It also makes the demonstration
portable and easy to compile with a standard C++ toolchain.

### Q5. How do the modules interact?

`main.cpp` integrates them through public APIs. Relationships use public
interfaces, IDs, or non-owning associations, while reports receive summary
structures and persistence serializes each module without exposing arbitrary
private data.

### Q6. What is the role of `main.cpp`?

It is the composition root and demonstration controller. It creates objects,
calls module operations, catches integration-level exceptions, drives the menu,
and runs persistence verification modes.

### Q7. What is cohesion?

Cohesion measures how closely the responsibilities inside a module belong
together. `FinanceManager`, for example, manages finance records rather than
also allocating hostel rooms, so its cohesion is high.

### Q8. What is coupling?

Coupling is the degree of dependency between modules. SCMS reduces unnecessary
coupling by using public interfaces and summary/ID data instead of making every
class directly access every other class.

### Q9. What is a translation unit?

A translation unit is a `.cpp` file after preprocessing its included headers.
Each SCMS `.cpp` is compiled independently, and the linker combines resulting
object code.

### Q10. Why separate `.h` and `.cpp` files?

Headers expose declarations and contracts; `.cpp` files hide implementation.
This supports separate compilation, readable interfaces, and controlled
dependencies.

## Classes, Encapsulation, and Construction

### Q11. What is a class?

A class is a user-defined type that groups state and behavior. In SCMS,
`Course` groups course data with enrollment, comparison, output, and validation
operations.

### Q12. What is an object?

An object is a concrete runtime instance of a class. Two `Course` objects have
the same structure but hold independent course codes, capacities, and
enrollments.

### Q13. How is encapsulation implemented?

State is private or protected, and callers use public constructors, getters,
setters, and domain operations. This lets classes validate changes before
committing them.

### Q14. Why not make all data public?

Public data could be changed without checking invariants. A caller could make a
room capacity negative or set an invalid CGPA, leaving the object unreliable.

### Q15. What is the difference between private and protected?

Private members are accessible only to the class and its friends. Protected
members are also accessible in derived classes; `Person` uses protected common
state for its role hierarchy.

### Q16. What is a default constructor?

A default constructor can be called without arguments. Classes that provide one
still ensure the resulting state follows the implementation's chosen defaults
or subsequent validation rules.

### Q17. What is a parameterized constructor?

It receives values needed to initialize a meaningful object. SCMS parameterized
constructors validate IDs, names, amounts, capacities, and other domain data.

### Q18. Why use initialization lists?

Members and base classes are initialized before the constructor body.
Initialization lists avoid constructing then assigning, and they are mandatory
for some member/base types.

### Q19. What is constructor chaining?

A derived constructor invokes a base constructor before initializing its own
part. `UndergradStudent` initializes `Student`, which initializes `Person`.

### Q20. What is the constructor order in multilevel inheritance?

Construction runs from the most general base toward the most derived class:
`Person`, then `Student`, then `UndergradStudent`. Destruction occurs in the
reverse order.

### Q21. Why validate in a constructor?

It prevents an object from being born in an invalid state. Operations can then
rely on invariants rather than repeatedly checking whether basic fields were
ever valid.

### Q22. Why validate in setters as well?

An initially valid object can become invalid later if mutation is unchecked.
Setters apply the same domain constraints to subsequent changes.

### Q23. What is const correctness?

It marks operations that do not modify observable state and prevents accidental
changes. SCMS getters, display operations, comparisons, searches, and report
generation use `const` where appropriate.

### Q24. Why return some getters by const reference?

For larger objects such as strings or vectors, a const reference can avoid a
copy while preventing the caller from modifying internal state through that
reference. The owning object's lifetime must still outlive the reference.

### Q25. What is an invariant?

An invariant is a rule that remains true for every valid object. Examples are
“room occupancy does not exceed capacity” and “course code is non-empty.”

## Inheritance, Abstraction, and Polymorphism

### Q26. Why is `Person` abstract?

A generic person has no role-specific display behavior in this model.
`displayInfo() const = 0` requires concrete roles to supply meaningful output
and prevents direct `Person` construction.

### Q27. What is a pure virtual function?

It is a virtual function declared with `= 0`. It defines a required interface
that concrete derived classes must implement unless they also remain abstract.

### Q28. Can an abstract class have implemented functions?

Yes. It can have constructors, data, ordinary methods, and even definitions for
some virtual functions. Abstractness only prevents direct instantiation.

### Q29. What is single inheritance in SCMS?

`Student`, `Faculty`, and `Staff` each directly inherit one base, `Person`.
`Book` and `Journal` similarly inherit only `LibraryItem`.

### Q30. What is multilevel inheritance in SCMS?

`UndergradStudent` derives from `Student`, which derives from `Person`. It
reuses both common identity and student academic state before adding its own
project and advisor fields.

### Q31. What is multiple inheritance in SCMS?

`HostelManager` directly inherits from both `Accommodation` and `Reportable`.
It therefore implements two independent abstract contracts.

### Q32. What is the diamond problem?

It occurs when two base paths inherit the same ancestor and a final class
inherits both paths. Without virtual inheritance, `HostelManager` would contain
two `BaseEntity` subobjects and base-member access could be ambiguous.

### Q33. How is the diamond problem resolved?

`Accommodation` and `Reportable` virtually inherit `BaseEntity`. Both paths
then share one virtual base subobject inside `HostelManager`.

### Q34. Who constructs a virtual base?

The most-derived class constructs it. Therefore, the `HostelManager`
constructor is responsible for initializing its shared `BaseEntity`.

### Q35. What is runtime polymorphism?

It is selecting a virtual override based on the object's dynamic type during
execution. Calling `displayInfo()` through `Person*` invokes the correct
student, faculty, staff, or undergraduate version.

### Q36. What is static type?

Static type is the type known from the variable declaration, such as
`Person*`. It determines which members are available at compile time.

### Q37. What is dynamic type?

Dynamic type is the actual most-derived object, such as `Student`, addressed by
a base pointer/reference. It determines which virtual override executes.

### Q38. What is virtual dispatch?

Virtual dispatch is the runtime mechanism that maps a virtual call to the
override for the dynamic type. Implementations commonly use a virtual table,
although the C++ standard specifies behavior rather than a required layout.

### Q39. Why use the `override` keyword?

It asks the compiler to confirm that a function truly overrides a virtual base
function. A mismatch such as omitted `const` becomes a compile error instead of
a subtle hidden overload.

### Q40. Why are polymorphic base destructors virtual?

Deleting a derived object through a base pointer must run the entire derived
destructor chain. A non-virtual base destructor would make such deletion
undefined behavior.

### Q41. What is object slicing?

Slicing occurs when a derived object is copied into a base object by value, so
the derived portion is lost. SCMS uses base pointers/smart pointers for
heterogeneous polymorphic collections to avoid slicing.

### Q42. What is an interface-like abstract class?

It primarily declares required virtual operations and little or no concrete
state. `Accommodation` and `Reportable` act as interface-like capabilities in
the hostel module.

## Relationships and Ownership

### Q43. What is composition?

Composition is strong ownership: the part's lifetime is controlled by the
whole. `HostelBlock` owns its `Room` values, and finance/library managers own
their contained records or smart-pointer objects.

### Q44. What is aggregation?

Aggregation is a weaker relationship where referenced entities exist
independently. A room stores student roll numbers but does not own or destroy
student objects.

### Q45. What is association?

Association is a general connection without implied ownership. `Enrollment`
connects a student roll number with a course code, semester, and grade.

### Q46. Why is `HostelBlock` composed of rooms rather than inherited from room?

A block has rooms; it is not a specialized room. Composition models the real
relationship and lets one block manage many room values.

### Q47. Why does a room store roll numbers?

The hostel module needs assignment identity, not ownership of complete
`Student` objects. Roll numbers reduce coupling and prevent duplicate ownership
of person data.

### Q48. What is a non-owning pointer?

It points to an object whose lifetime is managed elsewhere. A course's faculty
association does not delete the faculty object, so its validity depends on the
external object's lifetime.

### Q49. What is RAII?

Resource Acquisition Is Initialization ties a resource's lifetime to an
object's lifetime. Vectors, strings, streams, and smart pointers automatically
release their resources when scope ends.

### Q50. Why avoid raw `new` and `delete`?

Manual ownership is easy to leak or double-delete, especially during
exceptions. `make_unique`, containers, and value members express ownership and
clean up automatically.

## Operators, Friends, Static State, and Semantics

### Q51. What does `Course::operator+=` do?

It enrolls a student roll number into the current course. It validates the roll
number, duplicate state, and remaining capacity before increasing enrollment.

### Q52. What does `Course::operator+` do?

It creates a copy of a course, applies enrollment to the copy, and returns it.
The original course remains unchanged.

### Q53. How does `Course::operator==` compare courses?

It compares their course codes, because the course code is the chosen identity
key. The operation is const because comparison should not mutate either course.

### Q54. Why is `operator<<` a non-member friend?

The left operand is `std::ostream`, which cannot be changed to add a member
operator. A non-member supports natural `output << course` syntax; friendship
provides access if needed.

### Q55. What does `FeeRecord::operator-=` demonstrate?

It demonstrates a validated compound assignment on a domain type. The operator
changes the current object and returns a reference, matching normal compound
assignment conventions.

### Q56. What is a friend function?

It is a non-member function explicitly granted access to private/protected
members. Friendship is narrow privilege, not inheritance or membership.

### Q57. Is friendship inherited?

No. A friend of a base class is not automatically a friend of derived classes,
and friendship is neither transitive nor automatically mutual.

### Q58. What is a static data member?

It is one class-wide value shared by all instances. SCMS uses static counters
for record/invoice totals rather than one counter inside every object.

### Q59. Why persist the invoice counter?

After restart, a reset counter could generate an invoice number that conflicts
with a loaded invoice. Restoring the persisted maximum preserves identifier
continuity.

### Q60. What is a copy constructor?

It creates a new object from an existing object of the same type. `FeeRecord`
and `Invoice` provide explicit copy behavior that preserves independent value
state.

### Q61. What is copy assignment?

It replaces the state of an already existing object with another object's
state. A correct operator handles self-assignment and returns `*this`.

### Q62. What is the Rule of Three?

If a resource-managing type needs one of destructor, copy constructor, or copy
assignment, it often needs all three. `FeeRecord` demonstrates explicit copy
control, although its standard value members are already safely copyable.

### Q63. What is move construction?

It initializes a new object by transferring resources from a temporary or
expiring object. `Invoice` moves its strings and line-item vector rather than
requiring full copies.

### Q64. What is move assignment?

It releases/replaces the target's current state and transfers state from an
expiring source. The moved-from source must remain valid and destructible.

### Q65. Why mark move operations `noexcept`?

STL containers may prefer copying if moving could throw. `noexcept` communicates
that transfer is safe and supports more efficient container reallocation.

### Q66. What is the Rule of Five?

It extends the Rule of Three with move constructor and move assignment.
`Invoice` explicitly defines destructor, copy constructor/assignment, and move
constructor/assignment.

### Q67. What is the Rule of Zero?

It recommends relying on standard value members and smart pointers so no custom
special member functions are needed. It is usually preferable in production
unless custom ownership or an academic demonstration requires explicit control.

## Templates, STL, and Algorithms

### Q68. What is a class template?

A class template is a blueprint parameterized by type. `Library<T>` can create
a typed library such as `Library<Book>` without duplicating the class design.

### Q69. What is a function template?

A function template generates type-specific functions from one definition.
`searchByTitle<T>()` works for compatible item types that expose the operations
its implementation uses.

### Q70. Why are template definitions usually in headers?

The compiler must see the complete definition when instantiating a template for
a particular type. A declaration alone in a header often causes linker errors
unless explicit instantiations are supplied.

### Q71. What is compile-time polymorphism?

It is selecting/generating behavior during compilation, as with templates and
overloaded operators. It differs from virtual dispatch, which selects behavior
at runtime.

### Q72. Why use `vector`?

It provides contiguous, automatically managed dynamic storage and efficient
iteration. SCMS frequently traverses complete collections and appends records,
which suits `vector`.

### Q73. Why use `set` for enrollments?

A set maintains unique roll numbers and returns whether insertion succeeded.
That directly supports duplicate prevention with logarithmic lookup/insertion.

### Q74. Why use `map`?

A map connects unique keys to values. Library loading uses an item ID to retain
and later restore the item's availability state.

### Q75. What does `std::find_if` do?

It returns the first iterator whose element satisfies a predicate, or `end()` if
none does. SCMS uses it for searches in manager collections and report data.

### Q76. What does `std::sort` require?

It requires random-access iterators and a strict weak ordering comparator.
SCMS supplies a lambda to order student summaries by GPA.

### Q77. What does `std::copy_if` do?

It copies only elements for which a predicate returns true into an output
range. Reporting uses it to build filtered data such as unpaid fee records.

### Q78. What does `std::count_if` do?

It counts elements satisfying a predicate without creating another collection.
SCMS uses it for conditions such as unpaid fees or occupied rooms.

### Q79. Explain the erase-remove idiom.

`remove_if` rearranges retained elements and returns a new logical end; it does
not shrink a vector. Calling `erase(newEnd, end)` removes the trailing elements.

### Q80. What is a lambda capture?

It specifies external variables available inside a lambda. A CSV row handler
can capture a destination vector by reference so valid reconstructed objects
are appended to that vector.

## Exceptions, Validation, and Persistence

### Q81. Why use custom exceptions?

They communicate domain-specific failure. `CapacityExceededException` is more
meaningful than an unexplained `false` and can be caught separately from other
enrollment errors.

### Q82. What custom exceptions exist?

The course module includes `EnrollmentException` and
`CapacityExceededException`. The library module includes
`OverdueException`; standard exceptions handle many validation failures.

### Q83. Why catch exceptions by const reference?

It avoids copying the exception and preserves its dynamic type. `const` also
prevents accidental modification in the handler.

### Q84. What is exception safety in an allocation operation?

All failure conditions should be checked before mutation, or changes should be
rolled back if a later step fails. This prevents a room or library transaction
from being only half updated.

### Q85. Why use CSV?

It is readable, easy to inspect, supported with standard streams, and requires
no external service. It is appropriate for a local academic demonstration.

### Q86. How are data files created?

`CampusPersistence::ensureDataFiles()` asks `CsvUtils` to create the `data`
directory and missing files with their headers. It runs at application startup.

### Q87. How does append mode preserve headers?

The output helper checks whether the file is absent or empty. It writes a
header only in that case; otherwise it appends rows after the existing content.

### Q88. How are commas inside fields handled?

`CsvUtils::escape()` quotes fields when necessary and doubles embedded quotes.
`parseLine()` respects those quoted regions while splitting.

### Q89. How does loading handle corrupted rows?

It validates field count and conversions before construction. Invalid rows or
constructor exceptions are skipped, while valid rows continue loading.

### Q90. Why load hostel blocks before rooms?

Rooms require an existing parent block, and allocations require an existing
room. Loading in dependency order preserves referential consistency.

### Q91. Why use separate library borrowing records?

Items and members are independent entities, while borrowing is a relationship
between them. A separate file avoids repeating complete item/member details and
allows the relationship to be replayed after both sides load.

### Q92. What is serialization?

Serialization converts object state into a storable representation. SCMS writes
selected public state as CSV/text and reconstructs objects through validated
constructors and operations.

### Q93. What is deserialization risk?

Stored data is untrusted and may be malformed, incomplete, duplicated, or out
of range. SCMS therefore checks types, field counts, duplicates, and class
validation before accepting rows.

## Namespaces, Smart Pointers, Reports, and Verification

### Q94. Why use namespaces?

Namespaces group related names and prevent collisions. The project separates
`SCMS::Reports`, `SCMS::Utils`, and `SCMS::Persistence`.

### Q95. What does `unique_ptr` mean?

It expresses exclusive ownership of one dynamically allocated object. It cannot
be copied, but it can be moved, and it deletes its object automatically.

### Q96. What does `shared_ptr` mean?

It expresses shared ownership through a reference count. The object is destroyed
when the last owning `shared_ptr` is released; it should be used only when
ownership is genuinely shared.

### Q97. Why store library items as `unique_ptr<LibraryItem>`?

The manager exclusively owns heterogeneous `Book` and `Journal` objects. Base
smart pointers preserve virtual dispatch and automatically destroy complete
derived objects.

### Q98. How are consolidated reports generated?

`ReportGenerator` receives structured module summaries, applies algorithms for
ordering/filtering, formats sections, and combines them into a campus report.
It exports the result to `data/scms_report.txt`.

### Q99. How does the program verify persistence after restart?

Dedicated command-line flows load existing files and search for known IDs and
counts without relying on the previous process's memory. Another flow appends
records and reloads them.

### Q100. What would you improve for a production deployment?

I would replace CSV with a transactional database, add authentication and
authorization, use repository/service interfaces, introduce automated unit and
integration tests, add concurrency controls and logging, and expose a secured
API or GUI. I would preserve the domain validation and ownership principles
already demonstrated.

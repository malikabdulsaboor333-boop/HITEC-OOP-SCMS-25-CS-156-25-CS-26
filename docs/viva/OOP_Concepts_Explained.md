# OOP Concepts Explained Through SCMS

This guide explains concepts that are present in the actual project. Small
syntax fragments are illustrative extracts of the project's design; constructor
arguments are shortened where their full values are not relevant.

## 1. Classes and Objects

**Definition:** A class defines data and behavior. An object is a runtime
instance of that class.

**Analogy:** A university admission form is a blueprint; each completed form is
an individual object.

**C++ syntax:**

```cpp
class Course {
public:
    void displayCourseInfo() const;
};

Course programmingFundamentals;
```

**SCMS use:** Every domain concept, including `Student`, `Course`, `Book`,
`Invoice`, `Room`, and `ReportGenerator`, is represented by a class.

**Why/advantages:** Classes group valid state with the operations that preserve
it. This reduces accidental misuse and makes modules easier to reason about.

**Viva prompt:** What is the difference between a class declaration and an
object definition?

## 2. Encapsulation

**Definition:** Encapsulation hides representation and exposes controlled public
operations.

**Analogy:** A bank account exposes deposit and withdrawal operations but does
not let a customer directly rewrite the stored balance.

**C++ syntax:**

```cpp
class Room {
private:
    int maxCapacity;

public:
    int getMaxCapacity() const;
    void setMaxCapacity(int capacity);
};
```

**SCMS use:** Domain data is private or protected; callers use constructors,
getters, setters, and operations. For example, occupants are changed through
`addOccupant()` and `removeOccupant()`.

**Why/advantages:** Validation remains centralized and invalid state is harder
to create.

**Viva prompt:** Why is a public setter still encapsulation?

## 3. Access Specifiers

**Definition:** `public`, `protected`, and `private` control where members can be
accessed.

**Analogy:** Public areas of a campus are open, protected offices are available
to authorized staff, and private records are restricted to their owner.

**SCMS use:** `Person` keeps shared fields protected for derived roles. Concrete
role fields remain private. Public functions form the API.

**Why/advantages:** Access reflects ownership and extension needs without
exposing all implementation details.

**Viva prompt:** Why are `Person` fields protected while `Student` fields are
private?

## 4. Abstraction

**Definition:** Abstraction exposes essential behavior while hiding
implementation detail.

**Analogy:** A library member requests “issue this book” without manually
updating every internal collection.

**C++ syntax:**

```cpp
class Person {
public:
    virtual void displayInfo() const = 0;
    virtual ~Person();
};
```

**SCMS use:** `Person`, `LibraryItem`, `BaseEntity`, `Accommodation`, and
`Reportable` define contracts that concrete classes fulfill.

**Why/advantages:** Calling code depends on stable capabilities rather than
concrete implementation.

**Viva prompt:** Can a class be abstract without having data members?

## 5. Pure Virtual Functions and Abstract Classes

**Definition:** A pure virtual function is declared with `= 0`. A class with at
least one unimplemented pure virtual function cannot be instantiated.

**Analogy:** A university policy says every reportable unit must generate a
report, but each unit decides how.

**SCMS use:** `Person::displayInfo()`, `LibraryItem::displayInfo()`,
accommodation operations, and `Reportable::generateReport()` establish required
behavior.

**Why/advantages:** The compiler enforces implementation of the contract.

**Viva prompt:** Why can a pure virtual class still have a constructor?

## 6. Single Inheritance

**Definition:** One derived class inherits from one direct base class.

**Analogy:** A student is one specialized kind of person.

**C++ syntax:**

```cpp
class Student : public Person {
    // ...
};
```

**SCMS use:** `Student`, `Faculty`, and `Staff` each directly inherit
`Person`; `Book` and `Journal` each inherit `LibraryItem`.

**Why/advantages:** Common state and behavior are reused while derived classes
specialize their role.

**Viva prompt:** What does public inheritance mean semantically?

## 7. Multilevel Inheritance

**Definition:** A class derives from a class that is itself derived.

**Analogy:** An undergraduate student is a student, and every student is a
person.

**C++ syntax:**

```cpp
class Student : public Person {};
class UndergradStudent : public Student {};
```

**SCMS use:** `Person -> Student -> UndergradStudent`.

**Why/advantages:** Undergraduate-specific fields are added without copying
person or student state.

**Viva prompt:** In what order do constructors run in a multilevel hierarchy?

## 8. Multiple Inheritance

**Definition:** A class directly inherits from more than one base class.

**Analogy:** A hostel manager performs accommodation operations and also has a
reporting responsibility.

**C++ syntax:**

```cpp
class HostelManager : public Accommodation, public Reportable {
    // ...
};
```

**SCMS use:** `HostelManager` implements both abstract interfaces.

**Why/advantages:** It combines two independent contracts in one concrete
administrator.

**Viva prompt:** What ambiguity can multiple inheritance introduce?

## 9. Virtual Inheritance

**Definition:** Virtual inheritance makes multiple inheritance paths share one
base-class subobject.

**Analogy:** Two departments refer to the same employee identity rather than
creating two identities for one manager.

**C++ syntax:**

```cpp
class Accommodation : virtual public BaseEntity {};
class Reportable : virtual public BaseEntity {};
```

**SCMS use:** Both hostel interfaces virtually inherit `BaseEntity`.
`HostelManager` therefore has one entity ID and one `BaseEntity` identity.

**Why/advantages:** It resolves the diamond problem and removes ambiguous base
member access.

**Viva prompt:** Which constructor initializes a virtual base?

## 10. Constructor Chaining and Initialization Lists

**Definition:** Base and member initialization happens before the constructor
body. A derived constructor invokes an appropriate base constructor.

**Analogy:** A student identity must exist before student-specific registration
details can be added.

**C++ syntax:**

```cpp
Student::Student(/* values */)
    : Person(/* common values */),
      rollNo(/* value */),
      department(/* value */),
      cgpa(/* value */) {}
```

**SCMS use:** Derived records initialize their base portions, and classes
initialize members using lists.

**Why/advantages:** It is required for bases without default constructors,
avoids redundant default construction/assignment, and supports const/reference
members.

**Viva prompt:** What is the actual initialization order?

## 11. Virtual Functions and Runtime Polymorphism

**Definition:** A virtual call through a base pointer/reference is resolved
according to the object's runtime type.

**Analogy:** Calling “display details” on an identity card produces the correct
student, faculty, or staff format.

**C++ syntax:**

```cpp
Person* person = &student;
person->displayInfo();
```

**SCMS use:** Person roles, library items, financial records, and hostel
interfaces are called polymorphically.

**Why/advantages:** Heterogeneous objects can share one interface without type
switches.

**Viva prompt:** What is static type versus dynamic type?

## 12. Virtual Destructors

**Definition:** A virtual base destructor ensures destruction begins with the
most-derived type when deletion occurs through a base pointer.

**Analogy:** Closing a university department requires closing its specialized
resources before removing its generic registration.

**C++ syntax:**

```cpp
virtual ~LibraryItem();
```

**SCMS use:** Polymorphic bases have virtual destructors.

**Why/advantages:** It prevents incomplete destruction and undefined behavior.

**Viva prompt:** Is a virtual destructor necessary when no polymorphic deletion
ever occurs?

## 13. Function Overriding

**Definition:** A derived class supplies a new implementation with the same
virtual function signature.

**C++ syntax:**

```cpp
void displayInfo() const override;
```

**SCMS use:** Every concrete person and library item overrides the corresponding
display contract. `HostelManager` overrides its abstract interface operations.

**Why/advantages:** `override` lets the compiler detect signature mistakes.

**Viva prompt:** What happens if `const` is omitted from an override?

## 14. Operator Overloading

**Definition:** Operator overloading defines an operator for a user-defined
type while retaining understandable semantics.

**Analogy:** Comparing course codes with `==` resembles comparing built-in
values.

**SCMS use:**

- `Course::operator+=` mutates enrollment.
- `Course::operator+` returns an enrolled copy.
- `Course::operator==` compares course code identity.
- `operator<<` prints course information.
- `FeeRecord::operator-=` applies a fee deduction/adjustment according to its
  validated implementation.

**Why/advantages:** It creates expressive syntax when the operation has a clear
domain meaning.

**Viva prompt:** Why should `operator==` usually be `const`?

## 15. Friend Functions and Classes

**Definition:** A friend is a non-member function or class granted access to
private/protected members.

**Analogy:** An authorized auditor can inspect records without becoming a
finance record.

**SCMS use:** Stream output and finance summary behavior use narrowly declared
friend access; `FinanceManager` has privileged invoice access where declared.

**Why/advantages:** It supports symmetric non-member operations or tightly
coupled auditing while avoiding unnecessary public getters.

**Risk:** Friendship weakens encapsulation if granted broadly.

**Viva prompt:** Is a friend function inherited or a class member?

## 16. Static Data Members

**Definition:** A static data member belongs to the class and is shared by all
instances.

**Analogy:** A university-wide count of issued invoices is not owned by one
invoice.

**C++ syntax:**

```cpp
class Invoice {
    static int invoiceCounter;
};
```

**SCMS use:** Salary, fee, and invoice record counters track class-wide
creation. Invoice loading restores the counter safely.

**Why/advantages:** Shared class state is kept with the responsible type rather
than in a global variable.

**Viva prompt:** Where is a non-inline static data member defined?

## 17. Copy Semantics and the Rule of Three

**Definition:** If a type manages a resource and needs a custom destructor,
copy constructor, or copy assignment, it often needs all three.

**Analogy:** Duplicating a file folder should produce an independent folder, not
two labels pointing at one destructible paper set.

**SCMS use:** `FeeRecord` explicitly defines copy construction and copy
assignment. Its `std::string` and value members already copy independently; the
explicit functions make the copy behavior visible and preserve complete base
and derived state.

**Important accuracy:** The class does not manually allocate heap memory, so
the standard members already provide safe value copying. “Deep copy” here means
independent value state, not hand-written copying of a raw buffer.

**Viva prompt:** When is the Rule of Zero better than the Rule of Three?

## 18. Move Semantics and the Rule of Five

**Definition:** C++11 added move construction and move assignment. A
resource-owning class that customizes special members may need destructor, copy
constructor, copy assignment, move constructor, and move assignment.

**Analogy:** Moving an archive transfers its contents instead of photocopying
every page.

**C++ syntax:**

```cpp
Invoice(Invoice&& other) noexcept;
Invoice& operator=(Invoice&& other) noexcept;
```

**SCMS use:** `Invoice` defines the five special member functions and moves its
STL-managed line-item state.

**Why/advantages:** Moving can avoid expensive copies and `noexcept` allows STL
containers to move more confidently.

**Viva prompt:** What state must a moved-from object have?

## 19. Class Templates

**Definition:** A class template describes a family of classes parameterized by
a type.

**Analogy:** One catalog design can catalog books, journals, or another item
type.

**C++ syntax:**

```cpp
template <typename T>
class Library {
    std::vector<T> items;
};
```

**SCMS use:** `Library<T>` provides typed library storage and related
operations.

**Why/advantages:** Type-safe reuse occurs at compile time without base-pointer
overhead.

**Viva prompt:** Why are template definitions commonly kept in headers?

## 20. Function Templates

**Definition:** A function template generates type-specific functions from one
definition.

**C++ syntax:**

```cpp
template <typename T>
const T* searchByTitle(const std::vector<T>& items,
                       const std::string& title);
```

**SCMS use:** `searchByTitle<T>()` searches typed library item collections.

**Why/advantages:** One algorithm works for multiple compatible item types.

**Viva prompt:** What requirement must `T` satisfy in this function?

## 21. Composition

**Definition:** Composition is a strong “has-a” relationship where the owner
controls the contained object's lifetime.

**Analogy:** A hostel block contains its rooms as part of its own structure.

**SCMS use:** `HostelBlock` contains `Room` values; managers contain their
record collections; `LibraryManager` owns item pointers.

**Why/advantages:** It models ownership directly and benefits from automatic
destruction.

**Viva prompt:** Why is `HostelBlock` not derived from `Room`?

## 22. Aggregation and Association

**Definition:** Aggregation is a weaker “has-a” relationship where related
objects can exist independently. Association is a general connection without
ownership.

**Analogy:** A room lists students assigned to it, but the students continue to
exist when the room record is removed.

**SCMS use:** Room occupant roll numbers represent non-owning student
aggregation. Course/instructor and enrollment/student/course links are
associations.

**Why/advantages:** It avoids false ownership and circular lifetime problems.

**Viva prompt:** How does storing an ID differ from owning an object?

## 23. Smart Pointers and RAII

**Definition:** Smart pointers manage dynamically allocated object lifetimes.
RAII ties resource release to object destruction.

**Analogy:** A registered custodian automatically returns a key when their
assignment ends.

**SCMS use:** `unique_ptr<LibraryItem>` gives exclusive item ownership;
`unique_ptr<Person>` manages polymorphic person examples; report utilities
demonstrate `unique_ptr` and `shared_ptr`.

**Why/advantages:** No raw `new/delete`, explicit ownership, exception-safe
cleanup, and fewer leaks.

**Viva prompt:** When would `shared_ptr` be inappropriate?

## 24. Exception Handling

**Definition:** Exceptions transfer control from an error detection point to a
matching handler.

**C++ syntax:**

```cpp
try {
    course += rollNo;
} catch (const CapacityExceededException& error) {
    std::cerr << error.what();
}
```

**SCMS use:** Domain validation uses standard exceptions and custom
`EnrollmentException`, `CapacityExceededException`, and
`OverdueException`.

**Why/advantages:** It separates normal results from exceptional failure and
preserves valid state.

**Viva prompt:** Why catch exceptions by `const` reference?

## 25. STL Containers

**Definition:** Standard containers provide tested generic data structures.

**SCMS use:**

- `vector`: ordered dynamic collections throughout the project;
- `map`: keyed lookups in template/library support;
- `set`: unique values, including enrolled roll numbers;
- smart-pointer containers: polymorphic owned collections.

**Why/advantages:** They provide RAII, iterators, algorithms, and predictable
complexity without manual memory management.

**Viva prompt:** Why is `set` appropriate for duplicate prevention?

## 26. STL Algorithms and Lambdas

**Definition:** Algorithms perform operations over iterator ranges. Lambdas are
local callable objects.

**C++ syntax:**

```cpp
std::sort(students.begin(), students.end(),
          [](const auto& left, const auto& right) {
              return left.cgpa > right.cgpa;
          });
```

**SCMS use:** `sort`, `find_if`, `count_if`, `for_each`, `copy_if`,
`remove_if`, and related algorithms process reports, searches, and removals.

**Why/advantages:** The code states the operation directly and reduces
index/iterator mistakes.

**Viva prompt:** What can a lambda capture?

## 27. Namespaces and Nested Namespaces

**Definition:** Namespaces group names and prevent collisions.

**C++ syntax:**

```cpp
namespace SCMS {
namespace Reports {
class ReportGenerator;
}
}
```

**SCMS use:** Reports, utilities, and persistence are separated as
`SCMS::Reports`, `SCMS::Utils`, and `SCMS::Persistence`.

**Why/advantages:** Intent is visible and generic names such as `UtilityManager`
do not pollute the global namespace.

**Viva prompt:** Does a namespace create an object?

## 28. File I/O and Serialization

**Definition:** File I/O reads and writes persistent byte/text streams.
Serialization converts object state into a storage format.

**SCMS use:** `fstream`, `ifstream`, and `ofstream` save CSV records and text
reports. `CsvUtils` escapes fields and parses rows.

**Why/advantages:** Data can survive program termination without external
dependencies.

**Viva prompt:** Why must CSV fields containing commas or quotes be escaped?

## 29. Const Correctness

**Definition:** `const` expresses and enforces that an operation does not modify
observable object state.

**SCMS use:** Getters, searches on const objects, display functions, comparison
operators, and report generation use `const`.

**Why/advantages:** It documents intent, allows calls on const objects, and
prevents accidental mutation.

**Viva prompt:** What is the difference between `const T*` and `T* const`?

## 30. Validation and Class Invariants

**Definition:** An invariant is a condition that must remain true for every
valid object.

**Analogy:** A room cannot have more registered occupants than beds.

**SCMS use:** Constructors and setters validate IDs, names, dates, money,
capacities, CGPA, room types, and occupancy. Operations check availability,
duplicates, and capacity before mutation.

**Why/advantages:** Invalid state is rejected at the boundary and later methods
can rely on established assumptions.

**Viva prompt:** Why validate in both constructors and setters?

## 31. Compile-Time vs Runtime Polymorphism

**Compile-time:** Templates and overloaded operators are selected/generated by
the compiler.

**Runtime:** Virtual functions are dispatched using the object's dynamic type.

**SCMS examples:**

- compile-time: `Library<Book>`, `searchByTitle<Book>()`, `operator==`;
- runtime: `Person*->displayInfo()`, `LibraryItem*->displayInfo()`,
  `Reportable*->generateReport()`.

**Trade-off:** Compile-time polymorphism offers type-specific optimization but
requires compile-time knowledge. Runtime polymorphism supports heterogeneous
collections through a stable base interface.

**Viva prompt:** Can a template function also call virtual functions?

## 32. Separation of Declaration and Definition

**Definition:** Headers expose class declarations; `.cpp` files provide
non-template function definitions.

**SCMS use:** Each normal class has a guarded header and corresponding
implementation. Template definitions remain available from their headers
because instantiation requires the definition.

**Why/advantages:** It supports separate compilation, cleaner interfaces, and
reduced rebuild coupling.

**Viva prompt:** What error occurs when a declared function has no linked
definition?

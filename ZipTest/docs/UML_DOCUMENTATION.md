# UML Documentation

The full UML artifact set is located in `docs/UML/`.

Files:

- `class_diagram.mmd`: Mermaid class diagram source.
- `class_diagram.puml`: PlantUML class diagram source.
- `class_diagram.md`: UML explanation and fallback hierarchy.
- `class_diagram.png`: rendered UML image.

## Mermaid UML Overview

```mermaid
classDiagram
direction TB
Person <|-- Student
Person <|-- Faculty
Person <|-- Staff
Student <|-- GradStudent
EnrollmentException <|-- CapacityExceededException
LibraryItem <|-- Book
LibraryItem <|-- Journal
FinancialRecord <|-- SalaryRecord
FinancialRecord <|-- FeeRecord
FinancialRecord <|-- Invoice
BaseEntity <|.. Accommodation : virtual public
BaseEntity <|.. Reportable : virtual public
Accommodation <|-- HostelManager
Reportable <|-- HostelManager
FinanceManager *-- SalaryRecord
FinanceManager *-- FeeRecord
FinanceManager *-- Invoice
LibraryManager *-- LibraryItem
LibraryManager *-- LibraryMember
HostelManager *-- HostelBlock
HostelBlock *-- Room
Course o-- Faculty
Enrollment o-- Student
Room o-- Student : roll numbers only
```

The full Mermaid source is available in `docs/UML/class_diagram.mmd`.

## PlantUML UML Overview

```plantuml
@startuml
abstract class Person
class Student
class Faculty
class Staff
class GradStudent
Person <|-- Student
Person <|-- Faculty
Person <|-- Staff
Student <|-- GradStudent
abstract class LibraryItem
LibraryItem <|-- Book
LibraryItem <|-- Journal
FinancialRecord <|-- SalaryRecord
FinancialRecord <|-- FeeRecord
FinancialRecord <|-- Invoice
BaseEntity <|.. Accommodation : virtual public
BaseEntity <|.. Reportable : virtual public
Accommodation <|-- HostelManager
Reportable <|-- HostelManager
@enduml
```

The full PlantUML source is available in `docs/UML/class_diagram.puml`.

## Inheritance Diagram

```text
Person
├── Student
│   └── GradStudent
├── Faculty
└── Staff

LibraryItem
├── Book
└── Journal

FinancialRecord
├── SalaryRecord
├── FeeRecord
└── Invoice
```

## Composition Diagram

```text
LibraryManager
├── vector<unique_ptr<LibraryItem>>
└── vector<LibraryMember>

FinanceManager
├── vector<SalaryRecord>
├── vector<FeeRecord>
└── vector<Invoice>

HostelManager
└── vector<HostelBlock>
    └── vector<Room>
```

## Aggregation Diagram

```text
Course ---- Faculty        non-owning pointer
Enrollment ---- Student    non-owning pointer
Room ---- Student          stores roll numbers only
LibraryMember ---- Item    stores item IDs only
```

## Multiple and Virtual Inheritance Diagram

```text
          BaseEntity
          /        \
 virtual /          \ virtual
        /            \
Accommodation    Reportable
        \            /
         \          /
        HostelManager
```

## Template Usage

`Library<T>` is a class template. `searchByTitle<T>()` is a function template that works with title-bearing objects.

## Friend Relationships

- `Course` declares `operator<<` as a friend.
- Finance records and manager use `generateFinanceSummary()` as a friend function.
- `Invoice` declares `FinanceManager` as a friend class for controlled invoice counter restoration.

# SCMS UML Class Diagram

This document describes the class diagram exported for the HITEC University
Smart Campus Management System. The diagram is based only on the current
source files under `src/**/*.h` and `src/**/*.cpp`.

Generated artifacts:

- `class_diagram.mmd`: Mermaid class diagram source.
- `class_diagram.puml`: PlantUML class diagram source.
- `class_diagram.png`: Rendered fallback UML image.
- `class_diagram.md`: This documentation file.

## Text-Based UML Hierarchy

```text
Person (abstract)
├── Student
│   └── GradStudent
├── Faculty
└── Staff

EnrollmentException
└── CapacityExceededException

LibraryItem (abstract)
├── Book
└── Journal

FinancialRecord
├── SalaryRecord
├── FeeRecord
└── Invoice

BaseEntity (abstract)
├── Accommodation (virtual public BaseEntity)
│   └── HostelManager
└── Reportable (virtual public BaseEntity)
    └── HostelManager

Library<T> is a template class.
searchByTitle<T>() is a function template.
```

## Composition Relationships

```text
LibraryManager *-- LibraryItem
LibraryManager *-- LibraryMember
FinanceManager *-- SalaryRecord
FinanceManager *-- FeeRecord
FinanceManager *-- Invoice
HostelManager *-- HostelBlock
HostelBlock *-- Room
CampusReportData *-- StudentSummary
CampusReportData *-- FacultySummary
CampusReportData *-- CourseSummary
CampusReportData *-- LibrarySummary
CampusReportData *-- FeeSummary
CampusReportData *-- HostelSummary
Library<T> *-- T
```

## Aggregation and Association Relationships

```text
Course o-- Faculty
Enrollment o-- Student
Room o-- Student roll numbers
LibraryMember o-- LibraryItem IDs
CampusPersistence ..> Person, Course, Enrollment, LibraryManager,
                       HostelManager, FinanceManager, CsvUtils
ReportGenerator ..> CampusReportData
```

## Multiple and Virtual Inheritance

```text
BaseEntity <|.. Accommodation : virtual public
BaseEntity <|.. Reportable : virtual public
Accommodation <|-- HostelManager
Reportable <|-- HostelManager
```

`HostelManager` uses multiple inheritance through `Accommodation` and
`Reportable`. Both interfaces virtually inherit from `BaseEntity`, resolving
the diamond problem.

## Friend Relationships

```text
Course ..> operator<< : friend function
FinanceManager ..> generateFinanceSummary() : friend function
FinancialRecord ..> generateFinanceSummary() : friend function
SalaryRecord ..> generateFinanceSummary() : friend function
FeeRecord ..> generateFinanceSummary() : friend function
Invoice ..> FinanceManager : friend class
```

## OOP Concept Mapping

| Concept | Actual Code Mapping |
| --- | --- |
| Abstract class | `Person`, `LibraryItem`, `BaseEntity`, `Accommodation`, `Reportable` |
| Pure virtual functions | `displayInfo()`, `allocateRoom()`, `vacateRoom()`, `generateReport()` |
| Single inheritance | `Student`, `Faculty`, `Staff`, `Book`, `Journal`, finance records |
| Multilevel inheritance | `GradStudent -> Student -> Person` |
| Multiple inheritance | `HostelManager -> Accommodation + Reportable` |
| Virtual inheritance | `Accommodation : virtual public BaseEntity`, `Reportable : virtual public BaseEntity` |
| Runtime polymorphism | `Person`, `LibraryItem`, `Accommodation`, `Reportable`, `BaseEntity` pointers/references |
| Composition | Managers owning vectors of objects or smart pointers |
| Aggregation | Faculty/student references and roll-number relationships |
| Templates | `Library<T>`, `searchByTitle<T>()` |
| Friend usage | `operator<<`, `generateFinanceSummary()`, `FinanceManager` friendship with `Invoice` |
| Smart pointers | `unique_ptr`, `shared_ptr` |
| Namespaces | `SCMS::Reports`, `SCMS::Utils`, `SCMS::Persistence` |

## Rendering Note

No local Mermaid CLI, PlantUML, Graphviz, or Java executable was available in
the environment when this artifact was generated. Therefore, `class_diagram.png`
is a rendered fallback image produced from the same source-code-derived class
hierarchy and relationship summary. The Mermaid and PlantUML source files are
ready to paste into Mermaid Live or PlantUML for tool-rendered versions.

# STL and Standard Libraries Explained

## 1. `iostream`

**Purpose:** Console input/output through `std::cin`, `std::cout`, and
`std::cerr`.

**Syntax:**

```cpp
std::cout << "SCMS";
std::cin >> choice;
```

**Project use:** Menus, class display functions, reports, and error messages.

**Viva question:** What is the difference between `std::cout` and
`std::cerr`?

## 2. `string`

**Purpose:** Safe, resizable text storage.

**Syntax:**

```cpp
std::string courseCode;
```

**Project use:** Names, IDs, dates, titles, CSV fields, reports, and room
occupants.

**Viva question:** Why prefer `std::string` over a raw character array?

## 3. `vector`

**Purpose:** Contiguous dynamic sequence.

**Syntax:**

```cpp
std::vector<Room> rooms;
rooms.push_back(room);
```

**Project use:** Manager collections, room occupants, invoice line items,
report rows, and polymorphic smart-pointer collections.

**Complexity:** Random access is constant time; appending is amortized constant
time; middle insertion/removal is linear.

**Viva question:** When can `vector` reallocation invalidate pointers?

## 4. `map`

**Purpose:** Ordered unique key/value mapping, generally implemented as a
balanced tree.

**Syntax:**

```cpp
std::map<std::string, bool> availability;
```

**Project use:** Library persistence temporarily maps item IDs to availability;
the library template also demonstrates keyed indexing.

**Complexity:** Search, insertion, and removal are logarithmic.

**Viva question:** How does `map` differ from `unordered_map`?

## 5. `set`

**Purpose:** Ordered collection of unique values.

**Syntax:**

```cpp
std::set<std::string> enrolledRollNumbers;
```

**Project use:** Prevents duplicate enrollment and duplicate loaded finance
identifiers; used in template/library support.

**Complexity:** Search, insertion, and removal are logarithmic.

**Viva question:** Why can insertion's Boolean result detect duplicates?

## 6. `memory`

**Purpose:** Smart pointers and memory utilities.

**Syntax:**

```cpp
auto item = std::make_unique<Book>(/* values */);
auto utility = std::make_shared<UtilityManager>();
```

**Project use:** Exclusive polymorphic ownership of people/library items and
smart-pointer demonstrations in reports/utilities.

**Viva question:** What is the ownership difference between `unique_ptr` and
`shared_ptr`?

## 7. `algorithm`

**Purpose:** Generic operations over iterator ranges.

### Actual algorithms

| Algorithm | Project purpose |
|---|---|
| `std::sort` | sort student summaries by GPA |
| `std::find_if` | locate records/items/blocks and overdue entries |
| `std::count_if` | count occupied rooms or unpaid fee records |
| `std::for_each` | format/report collections |
| `std::copy_if` | filter matching/unpaid records into another collection |
| `std::remove_if` | erase blocks/rooms matching an ID |
| `std::all_of` | verify all required data files were prepared |

**Erase-remove syntax:**

```cpp
items.erase(
    std::remove_if(items.begin(), items.end(), predicate),
    items.end());
```

`remove_if` moves retained elements forward; `erase` actually shrinks the
container.

**Viva question:** Why does `remove_if` not reduce vector size itself?

## 8. Lambda Expressions

**Purpose:** Define short callable behavior near the algorithm using it.

**Syntax:**

```cpp
[capture](const Type& value) -> bool {
    return condition;
}
```

**Actual uses:**

1. Compare student summaries for GPA sorting.
2. Identify an overdue library record with `find_if`.
3. filter unpaid fee records with `copy_if`.
4. count unpaid fees with `count_if`.
5. load CSV rows with handlers that capture destination collections.

**Capture:** `[&people]` captures a collection by reference so the handler can
append reconstructed objects. A captureless comparator needs no external state.

**Viva question:** What is the danger of returning a lambda that captured a
local variable by reference?

## 9. `fstream`

**Purpose:** File input/output streams.

**Types:**

- `std::ifstream`: input
- `std::ofstream`: output
- `std::fstream`: input and output

**Project use:** CSV persistence, invoice files, finance audit data, and text
report export/load.

**Viva question:** Why check a stream immediately after opening?

## 10. `exception` and `stdexcept`

**Purpose:** Standard exception interfaces and common exception types.

**Project use:** `std::exception` is caught at integration boundaries;
`std::invalid_argument` and custom exceptions report validation/domain errors.
Custom exceptions derive from standard exception classes.

**Syntax:**

```cpp
throw std::invalid_argument("Room number cannot be empty.");
```

**Viva question:** Why should destructors generally not allow exceptions to
escape?

## 11. `filesystem`

**Purpose:** Portable filesystem paths and directory operations in C++17.

**Project use:** `CsvUtils` creates parent directories before opening output
files and checks file existence/size.

**Viva question:** Which C++ standard introduced `std::filesystem`?

## 12. `sstream`

**Purpose:** Treat a string as an input/output stream.

**Project use:** Build formatted reports and parse/format text without repeated
string concatenation.

**Syntax:**

```cpp
std::ostringstream output;
output << "Total: " << total;
return output.str();
```

**Viva question:** Why can an output string stream improve formatted text
construction?

## 13. `iomanip`

**Purpose:** Stream formatting manipulators.

**Project use:** Financial precision, percentages, aligned output, and date/time
formatting.

**Syntax:**

```cpp
output << std::fixed << std::setprecision(2) << amount;
```

**Viva question:** Does `setprecision(2)` always mean two decimal places?

## 14. `chrono` and Time Support

**Purpose:** Type-safe clocks and durations.

**Project use:** Utility date generation obtains current time and formats the
calendar date.

**Viva question:** What is the distinction between a time point and a duration?

## 15. `cctype`

**Purpose:** Character classification and conversion.

**Project use:** Upper/lower conversion, trimming, and format validation.

**Safety note:** Character functions should receive an `unsigned char` value
converted to `int` to avoid undefined behavior for negative signed characters.

**Viva question:** Why is `std::toupper` not itself a whole-string function?

## 16. `limits`

**Purpose:** Numeric type properties and stream cleanup bounds.

**Project use:** `main()` discards invalid input through the maximum stream size;
CSV integer parsing checks numeric limits.

**Syntax:**

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

**Viva question:** Why is ignoring only one character insufficient after bad
input?

## 17. `utility`

**Purpose:** General utilities, especially `std::move` and pairs.

**Project use:** Move semantics for invoices/managers and transferring loaded
collections without unnecessary copies.

**Viva question:** Does `std::move` physically move an object?

## 18. Iterators

Algorithms receive iterator ranges `[begin, end)`. `begin` points at the first
element; `end` points one position past the last. This half-open convention
works for empty collections and makes range length consistent.

**Project use:** Every STL algorithm call operates through iterators, even when
the code does not explicitly name the iterator type.

**Viva question:** Why must the predicate not invalidate iterators unexpectedly?

## 19. Choosing Containers in SCMS

- Use `vector` where ordered traversal and compact ownership matter.
- Use `set` where uniqueness is the core requirement.
- Use `map` where a value must be found by a key.
- Use smart pointers inside containers where the collection owns polymorphic
  objects.

The project does not choose containers merely to satisfy a checklist; each
container supports a concrete behavior.

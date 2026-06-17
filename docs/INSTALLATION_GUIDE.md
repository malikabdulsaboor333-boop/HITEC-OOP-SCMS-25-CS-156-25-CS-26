# Installation Guide

## Requirements

- Windows PowerShell or another shell capable of running `g++`.
- C++17-compatible compiler.
- Recommended compiler: MinGW-w64 or GCC-compatible `g++`.
- No external libraries are required.

## Compiler Check

```powershell
g++ --version
```

The compiler must support C++17 features such as smart pointers, lambdas, STL algorithms, file streams, and `std::filesystem`.

## Build Instructions

From the repository root:

```powershell
$sources = Get-ChildItem src -Recurse -Filter *.cpp
g++ -std=c++17 -Wall -Wextra $sources.FullName -o scms.exe
```

Strict build:

```powershell
$sources = Get-ChildItem src -Recurse -Filter *.cpp
g++ -std=c++17 -Wall -Wextra -Werror $sources.FullName -o scms.exe
```

## Run Instructions

Interactive menu:

```powershell
.\scms.exe
```

Automated checks:

```powershell
.\scms.exe --self-test
.\scms.exe --persistence-seed
.\scms.exe --persistence-verify
.\scms.exe --persistence-append-test
```

## Folder Structure

```text
HITEC_OOP_SCMS/
├── src/
├── data/
├── docs/
├── README.md
└── PROJECT_RULES.md
```

## Data Folder

The program prepares the `data/` folder automatically through `CampusPersistence::ensureDataFiles()`. Run the executable from the repository root so relative file paths resolve correctly.

## Troubleshooting

Problem: `g++ is not recognized`.

Solution: Install MinGW-w64 or add the compiler's `bin` folder to PATH.

Problem: `std::filesystem` errors.

Solution: Use a compiler with C++17 filesystem support.

Problem: Program creates a different `data/` folder.

Solution: Start the executable from the project root.

Problem: UML image looks simplified.

Solution: The PNG is a local fallback render. Use `docs/UML/class_diagram.mmd` or `docs/UML/class_diagram.puml` for Mermaid/PlantUML rendering.

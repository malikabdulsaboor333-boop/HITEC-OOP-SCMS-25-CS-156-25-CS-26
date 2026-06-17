# SCMS Development Rules

## General Rules

1. Use C++17.
2. Keep declarations in .h files.
3. Keep implementations in .cpp files.
4. Never combine multiple modules into one file.
5. Never modify completed modules unless explicitly instructed.
6. Use header guards in every header file.
7. Follow instructor requirements exactly.
8. Use STL containers where appropriate.
9. Use clear OOP design and proper inheritance.
10. Code must compile with:

```bash
g++ -std=c++17 -Wall -Wextra
```

## Project Structure

Only create files inside the correct module folder.

Modules:

- src/person
- src/course
- src/library
- src/finance
- src/hostel
- src/utils

Do not create files outside these folders unless explicitly instructed.

## Coding Standards

- Use PascalCase for class names.
- Use camelCase for variables and methods.
- Use const correctness where appropriate.
- Avoid code duplication.
- Write clean and maintainable code.

## Module Rules

When implementing a module:

- Only modify files inside the target module.
- Do not edit previously completed modules.
- Create both .h and .cpp files.
- Provide complete implementations, not placeholders.

## Documentation

After generating code:

1. Explain each file created.
2. Explain the class hierarchy.
3. Verify compilation under C++17.
/**
 * @file Book.h
 * @brief Book class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Inheritance, encapsulation, method overriding, and
 * dynamic binding.
 */

#ifndef SCMS_LIBRARY_BOOK_H
#define SCMS_LIBRARY_BOOK_H

#include "LibraryItem.h"

#include <string>

class Book : public LibraryItem {
public:
    Book();
    Book(const std::string& newItemId,
         const std::string& newTitle,
         bool newIsAvailable,
         const std::string& newAuthor,
         const std::string& newIsbn,
         int newPublicationYear);
    ~Book() override;

    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
    int getPublicationYear() const;

    void setAuthor(const std::string& newAuthor);
    void setIsbn(const std::string& newIsbn);
    void setPublicationYear(int newPublicationYear);

    void displayInfo() const override;

private:
    void validateBookData() const;

    static constexpr const char* defaultItemId = "DEFAULT_BOOK";
    static constexpr const char* defaultTitle = "Untitled Book";
    static constexpr const char* defaultAuthor = "Unknown Author";
    static constexpr const char* defaultIsbn = "UNASSIGNED_ISBN";
    static constexpr int defaultPublicationYear = 1;
    static constexpr int minimumPublicationYear = 0;

    std::string author;
    std::string isbn;
    int publicationYear;
};

#endif

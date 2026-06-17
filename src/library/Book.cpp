/**
 * @file Book.cpp
 * @brief Book class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Inheritance, encapsulation, method overriding, and
 * dynamic binding.
 */

#include "Book.h"

#include <iostream>
#include <stdexcept>

Book::Book()
    : Book(defaultItemId,
           defaultTitle,
           true,
           defaultAuthor,
           defaultIsbn,
           defaultPublicationYear) {
}

Book::Book(const std::string& newItemId,
           const std::string& newTitle,
           bool newIsAvailable,
           const std::string& newAuthor,
           const std::string& newIsbn,
           int newPublicationYear)
    : LibraryItem(newItemId, newTitle, newIsAvailable),
      author(newAuthor),
      isbn(newIsbn),
      publicationYear(newPublicationYear) {
    validateBookData();
}

Book::~Book() = default;

const std::string& Book::getAuthor() const {
    return author;
}

const std::string& Book::getIsbn() const {
    return isbn;
}

int Book::getPublicationYear() const {
    return publicationYear;
}

void Book::setAuthor(const std::string& newAuthor) {
    if (newAuthor.empty()) {
        throw std::invalid_argument("Book author cannot be empty.");
    }
    author = newAuthor;
}

void Book::setIsbn(const std::string& newIsbn) {
    if (newIsbn.empty()) {
        throw std::invalid_argument("Book ISBN cannot be empty.");
    }
    isbn = newIsbn;
}

void Book::setPublicationYear(int newPublicationYear) {
    if (newPublicationYear <= minimumPublicationYear) {
        throw std::invalid_argument("Publication year must be positive.");
    }
    publicationYear = newPublicationYear;
}

void Book::displayInfo() const {
    std::cout << "Book Information\n"
              << "Item ID: " << itemId << '\n'
              << "Title: " << title << '\n'
              << "Available: " << (isAvailable ? "Yes" : "No") << '\n'
              << "Author: " << author << '\n'
              << "ISBN: " << isbn << '\n'
              << "Publication Year: " << publicationYear << '\n';
}

void Book::validateBookData() const {
    if (author.empty() || isbn.empty()) {
        throw std::invalid_argument("Book author and ISBN cannot be empty.");
    }
    if (publicationYear <= minimumPublicationYear) {
        throw std::invalid_argument("Publication year must be positive.");
    }
}

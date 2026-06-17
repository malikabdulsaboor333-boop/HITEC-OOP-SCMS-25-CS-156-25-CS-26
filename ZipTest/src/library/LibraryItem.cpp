/**
 * @file LibraryItem.cpp
 * @brief LibraryItem abstract base class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Abstraction, encapsulation, virtual functions, and
 * runtime polymorphism.
 */

#include "LibraryItem.h"

#include <stdexcept>

LibraryItem::LibraryItem(const std::string& newItemId,
                         const std::string& newTitle,
                         bool newIsAvailable)
    : itemId(newItemId),
      title(newTitle),
      isAvailable(newIsAvailable) {
    validateItemData();
}

LibraryItem::~LibraryItem() = default;

const std::string& LibraryItem::getItemId() const {
    return itemId;
}

const std::string& LibraryItem::getTitle() const {
    return title;
}

bool LibraryItem::getIsAvailable() const {
    return isAvailable;
}

void LibraryItem::setItemId(const std::string& newItemId) {
    if (newItemId.empty()) {
        throw std::invalid_argument("Library item ID cannot be empty.");
    }
    itemId = newItemId;
}

void LibraryItem::setTitle(const std::string& newTitle) {
    if (newTitle.empty()) {
        throw std::invalid_argument("Library item title cannot be empty.");
    }
    title = newTitle;
}

void LibraryItem::setIsAvailable(bool newIsAvailable) {
    isAvailable = newIsAvailable;
}

void LibraryItem::validateItemData() const {
    if (itemId.empty()) {
        throw std::invalid_argument("Library item ID cannot be empty.");
    }
    if (title.empty()) {
        throw std::invalid_argument("Library item title cannot be empty.");
    }
}

/**
 * @file Journal.cpp
 * @brief Journal class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Inheritance, encapsulation, method overriding, and
 * dynamic binding.
 */

#include "Journal.h"

#include <iostream>
#include <stdexcept>

Journal::Journal()
    : Journal(defaultItemId,
              defaultTitle,
              true,
              defaultPublisher,
              defaultVolume,
              defaultIssue) {
}

Journal::Journal(const std::string& newItemId,
                 const std::string& newTitle,
                 bool newIsAvailable,
                 const std::string& newPublisher,
                 int newVolume,
                 int newIssue)
    : LibraryItem(newItemId, newTitle, newIsAvailable),
      publisher(newPublisher),
      volume(newVolume),
      issue(newIssue) {
    validateJournalData();
}

Journal::~Journal() = default;

const std::string& Journal::getPublisher() const {
    return publisher;
}

int Journal::getVolume() const {
    return volume;
}

int Journal::getIssue() const {
    return issue;
}

void Journal::setPublisher(const std::string& newPublisher) {
    if (newPublisher.empty()) {
        throw std::invalid_argument("Journal publisher cannot be empty.");
    }
    publisher = newPublisher;
}

void Journal::setVolume(int newVolume) {
    if (newVolume <= minimumPositiveValue) {
        throw std::invalid_argument("Journal volume must be positive.");
    }
    volume = newVolume;
}

void Journal::setIssue(int newIssue) {
    if (newIssue <= minimumPositiveValue) {
        throw std::invalid_argument("Journal issue must be positive.");
    }
    issue = newIssue;
}

void Journal::displayInfo() const {
    std::cout << "Journal Information\n"
              << "Item ID: " << itemId << '\n'
              << "Title: " << title << '\n'
              << "Available: " << (isAvailable ? "Yes" : "No") << '\n'
              << "Publisher: " << publisher << '\n'
              << "Volume: " << volume << '\n'
              << "Issue: " << issue << '\n';
}

void Journal::validateJournalData() const {
    if (publisher.empty()) {
        throw std::invalid_argument("Journal publisher cannot be empty.");
    }
    if (volume <= minimumPositiveValue || issue <= minimumPositiveValue) {
        throw std::invalid_argument(
            "Journal volume and issue must be positive.");
    }
}

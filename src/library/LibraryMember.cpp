/**
 * @file LibraryMember.cpp
 * @brief LibraryMember class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation and STL container usage.
 */

#include "LibraryMember.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

LibraryMember::LibraryMember()
    : LibraryMember(defaultMemberId, defaultMemberName) {
}

LibraryMember::LibraryMember(const std::string& newMemberId,
                             const std::string& newMemberName)
    : memberId(newMemberId),
      memberName(newMemberName) {
    validateMemberData();
}

const std::string& LibraryMember::getMemberId() const {
    return memberId;
}

const std::string& LibraryMember::getMemberName() const {
    return memberName;
}

const std::vector<std::string>& LibraryMember::getBorrowedItems() const {
    return borrowedItems;
}

void LibraryMember::setMemberId(const std::string& newMemberId) {
    if (newMemberId.empty()) {
        throw std::invalid_argument("Library member ID cannot be empty.");
    }
    memberId = newMemberId;
}

void LibraryMember::setMemberName(const std::string& newMemberName) {
    if (newMemberName.empty()) {
        throw std::invalid_argument("Library member name cannot be empty.");
    }
    memberName = newMemberName;
}

bool LibraryMember::borrowItem(const std::string& itemId) {
    if (itemId.empty()
        || std::find(borrowedItems.begin(), borrowedItems.end(), itemId)
            != borrowedItems.end()) {
        return false;
    }

    borrowedItems.push_back(itemId);
    return true;
}

bool LibraryMember::returnItem(const std::string& itemId) {
    const auto item = std::find(borrowedItems.begin(), borrowedItems.end(), itemId);
    if (item == borrowedItems.end()) {
        return false;
    }

    borrowedItems.erase(item);
    return true;
}

void LibraryMember::displayBorrowedItems() const {
    std::cout << "Borrowed Items for " << memberName << ":\n";
    if (borrowedItems.empty()) {
        std::cout << "No borrowed items.\n";
        return;
    }

    for (const std::string& itemId : borrowedItems) {
        std::cout << itemId << '\n';
    }
}

void LibraryMember::validateMemberData() const {
    if (memberId.empty() || memberName.empty()) {
        throw std::invalid_argument(
            "Library member ID and name cannot be empty.");
    }
}

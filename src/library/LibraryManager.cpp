/**
 * @file LibraryManager.cpp
 * @brief LibraryManager class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation, STL container usage, abstraction,
 * runtime polymorphism, and dynamic binding.
 */

#include "LibraryManager.h"

#include "OverdueException.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

LibraryManager::LibraryManager() = default;

bool LibraryManager::addItem(std::unique_ptr<LibraryItem> item) {
    if (!item || item->getItemId().empty()
        || searchItemById(item->getItemId()) != nullptr) {
        return false;
    }

    items.push_back(std::move(item));
    return true;
}

bool LibraryManager::removeItem(const std::string& itemId) {
    const auto item = std::find_if(
        items.begin(),
        items.end(),
        [&itemId](const std::unique_ptr<LibraryItem>& currentItem) {
            return currentItem->getItemId() == itemId;
        });

    if (item == items.end() || !(*item)->getIsAvailable()) {
        return false;
    }

    items.erase(item);
    return true;
}

LibraryItem* LibraryManager::searchItemById(const std::string& itemId) {
    const auto item = std::find_if(
        items.begin(),
        items.end(),
        [&itemId](const std::unique_ptr<LibraryItem>& currentItem) {
            return currentItem->getItemId() == itemId;
        });

    return item == items.end() ? nullptr : item->get();
}

const LibraryItem* LibraryManager::searchItemById(const std::string& itemId) const {
    const auto item = std::find_if(
        items.begin(),
        items.end(),
        [&itemId](const std::unique_ptr<LibraryItem>& currentItem) {
            return currentItem->getItemId() == itemId;
        });

    return item == items.end() ? nullptr : item->get();
}

std::vector<LibraryItem*> LibraryManager::searchItemByTitle(
    const std::string& title) {
    std::vector<LibraryItem*> matchingItems;
    std::for_each(
        items.begin(),
        items.end(),
        [&matchingItems, &title](
            const std::unique_ptr<LibraryItem>& currentItem) {
            if (currentItem->getTitle() == title) {
                matchingItems.push_back(currentItem.get());
            }
        });

    return matchingItems;
}

std::vector<const LibraryItem*> LibraryManager::searchItemByTitle(
    const std::string& title) const {
    std::vector<const LibraryItem*> matchingItems;
    std::for_each(
        items.begin(),
        items.end(),
        [&matchingItems, &title](
            const std::unique_ptr<LibraryItem>& currentItem) {
            if (currentItem->getTitle() == title) {
                matchingItems.push_back(currentItem.get());
            }
        });

    return matchingItems;
}

bool LibraryManager::registerMember(const LibraryMember& member) {
    if (member.getMemberId().empty()
        || searchMemberById(member.getMemberId()) != nullptr) {
        return false;
    }

    members.push_back(member);
    return true;
}

bool LibraryManager::issueItem(const std::string& itemId,
                               const std::string& memberId) {
    LibraryItem* item = searchItemById(itemId);
    LibraryMember* member = searchMemberById(memberId);

    if (item == nullptr || member == nullptr || !item->getIsAvailable()
        || !member->borrowItem(itemId)) {
        return false;
    }

    item->setIsAvailable(false);
    return true;
}

bool LibraryManager::returnItem(const std::string& itemId,
                                const std::string& memberId) {
    LibraryItem* item = searchItemById(itemId);
    LibraryMember* member = searchMemberById(memberId);

    if (item == nullptr || member == nullptr || !member->returnItem(itemId)) {
        return false;
    }

    item->setIsAvailable(true);
    return true;
}

void LibraryManager::checkOverdue(int overdueDays) const {
    if (overdueDays < 0) {
        throw std::invalid_argument("Overdue days cannot be negative.");
    }
    if (overdueDays > 0) {
        throw OverdueException(
            "Library item is overdue by "
            + std::to_string(overdueDays)
            + " day(s).");
    }
}

const std::vector<std::unique_ptr<LibraryItem>>&
LibraryManager::getItems() const {
    return items;
}

const std::vector<LibraryMember>& LibraryManager::getMembers() const {
    return members;
}

void LibraryManager::displayInventory() const {
    if (items.empty()) {
        std::cout << "Library inventory is empty.\n";
        return;
    }

    for (const std::unique_ptr<LibraryItem>& item : items) {
        item->displayInfo();
        std::cout << '\n';
    }
}

LibraryMember* LibraryManager::searchMemberById(const std::string& memberId) {
    const auto member = std::find_if(
        members.begin(),
        members.end(),
        [&memberId](const LibraryMember& currentMember) {
            return currentMember.getMemberId() == memberId;
        });

    return member == members.end() ? nullptr : &(*member);
}

const LibraryMember* LibraryManager::searchMemberById(
    const std::string& memberId) const {
    const auto member = std::find_if(
        members.begin(),
        members.end(),
        [&memberId](const LibraryMember& currentMember) {
            return currentMember.getMemberId() == memberId;
        });

    return member == members.end() ? nullptr : &(*member);
}

/**
 * @file LibraryManager.h
 * @brief LibraryManager class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation, STL container usage, abstraction,
 * runtime polymorphism, and dynamic binding.
 */

#ifndef SCMS_LIBRARY_LIBRARY_MANAGER_H
#define SCMS_LIBRARY_LIBRARY_MANAGER_H

#include "LibraryItem.h"
#include "LibraryMember.h"

#include <memory>
#include <string>
#include <vector>

class LibraryManager {
public:
    LibraryManager();

    bool addItem(std::unique_ptr<LibraryItem> item);
    bool removeItem(const std::string& itemId);

    LibraryItem* searchItemById(const std::string& itemId);
    const LibraryItem* searchItemById(const std::string& itemId) const;
    std::vector<LibraryItem*> searchItemByTitle(const std::string& title);
    std::vector<const LibraryItem*> searchItemByTitle(const std::string& title) const;

    bool registerMember(const LibraryMember& member);
    bool issueItem(const std::string& itemId, const std::string& memberId);
    bool returnItem(const std::string& itemId, const std::string& memberId);
    void checkOverdue(int overdueDays) const;

    const std::vector<std::unique_ptr<LibraryItem>>& getItems() const;
    const std::vector<LibraryMember>& getMembers() const;

    void displayInventory() const;

private:
    LibraryMember* searchMemberById(const std::string& memberId);
    const LibraryMember* searchMemberById(const std::string& memberId) const;

    std::vector<std::unique_ptr<LibraryItem>> items;
    std::vector<LibraryMember> members;
};

#endif

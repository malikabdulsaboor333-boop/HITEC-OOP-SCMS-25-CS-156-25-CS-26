/**
 * @file LibraryMember.h
 * @brief LibraryMember class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Encapsulation and STL container usage.
 */

#ifndef SCMS_LIBRARY_LIBRARY_MEMBER_H
#define SCMS_LIBRARY_LIBRARY_MEMBER_H

#include <string>
#include <vector>

class LibraryMember {
public:
    LibraryMember();
    LibraryMember(const std::string& newMemberId,
                  const std::string& newMemberName);

    const std::string& getMemberId() const;
    const std::string& getMemberName() const;
    const std::vector<std::string>& getBorrowedItems() const;

    void setMemberId(const std::string& newMemberId);
    void setMemberName(const std::string& newMemberName);

    bool borrowItem(const std::string& itemId);
    bool returnItem(const std::string& itemId);
    void displayBorrowedItems() const;

private:
    void validateMemberData() const;

    static constexpr const char* defaultMemberId = "DEFAULT_MEMBER";
    static constexpr const char* defaultMemberName = "Unknown Member";

    std::string memberId;
    std::string memberName;
    std::vector<std::string> borrowedItems;
};

#endif

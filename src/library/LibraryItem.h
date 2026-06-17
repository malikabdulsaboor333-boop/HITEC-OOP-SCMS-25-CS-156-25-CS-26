/**
 * @file LibraryItem.h
 * @brief LibraryItem abstract base class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Abstraction, encapsulation, virtual functions, and
 * runtime polymorphism.
 */

#ifndef SCMS_LIBRARY_LIBRARY_ITEM_H
#define SCMS_LIBRARY_LIBRARY_ITEM_H

#include <string>

class LibraryItem {
public:
    LibraryItem(const std::string& newItemId,
                const std::string& newTitle,
                bool newIsAvailable);
    virtual ~LibraryItem();

    const std::string& getItemId() const;
    const std::string& getTitle() const;
    bool getIsAvailable() const;

    void setItemId(const std::string& newItemId);
    void setTitle(const std::string& newTitle);
    void setIsAvailable(bool newIsAvailable);

    virtual void displayInfo() const = 0;

protected:
    std::string itemId;
    std::string title;
    bool isAvailable;

private:
    void validateItemData() const;
};

#endif

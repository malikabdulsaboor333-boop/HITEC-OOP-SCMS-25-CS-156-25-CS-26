/**
 * @file Journal.h
 * @brief Journal class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Inheritance, encapsulation, method overriding, and
 * dynamic binding.
 */

#ifndef SCMS_LIBRARY_JOURNAL_H
#define SCMS_LIBRARY_JOURNAL_H

#include "LibraryItem.h"

#include <string>

class Journal : public LibraryItem {
public:
    Journal();
    Journal(const std::string& newItemId,
            const std::string& newTitle,
            bool newIsAvailable,
            const std::string& newPublisher,
            int newVolume,
            int newIssue);
    ~Journal() override;

    const std::string& getPublisher() const;
    int getVolume() const;
    int getIssue() const;

    void setPublisher(const std::string& newPublisher);
    void setVolume(int newVolume);
    void setIssue(int newIssue);

    void displayInfo() const override;

private:
    void validateJournalData() const;

    static constexpr const char* defaultItemId = "DEFAULT_JOURNAL";
    static constexpr const char* defaultTitle = "Untitled Journal";
    static constexpr const char* defaultPublisher = "Unknown Publisher";
    static constexpr int defaultVolume = 1;
    static constexpr int defaultIssue = 1;
    static constexpr int minimumPositiveValue = 0;

    std::string publisher;
    int volume;
    int issue;
};

#endif

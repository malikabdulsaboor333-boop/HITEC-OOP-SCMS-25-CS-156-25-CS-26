/**
 * @file Person.h
 * @brief Person class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Abstract class, encapsulation, pure virtual function,
 * virtual destructor, and access specifiers.
 */

#ifndef SCMS_PERSON_PERSON_H
#define SCMS_PERSON_PERSON_H

#include <string>

class Person {
public:
    Person();
    Person(const std::string& newName,
           const std::string& newCnic,
           int newAge,
           const std::string& newContact);
    virtual ~Person();

    const std::string& getName() const;
    const std::string& getCnic() const;
    int getAge() const;
    const std::string& getContact() const;

    void setName(const std::string& newName);
    void setCnic(const std::string& newCnic);
    void setAge(int newAge);
    void setContact(const std::string& newContact);

    virtual void displayInfo() const = 0;

protected:
    void displayPersonInfo() const;

    std::string name;
    std::string cnic;
    int age;
    std::string contact;

private:
    void validatePersonData() const;

    static constexpr const char* defaultName = "Unknown Person";
    static constexpr const char* defaultCnic = "00000-0000000-0";
    static constexpr const char* defaultContact = "Not Provided";
    static constexpr int defaultAge = 1;
    static constexpr int minimumAge = 0;
};

#endif

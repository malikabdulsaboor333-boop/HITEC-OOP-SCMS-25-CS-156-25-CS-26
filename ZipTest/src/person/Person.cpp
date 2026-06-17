/**
 * @file Person.cpp
 * @brief Person class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 *
 * OOP Concepts Used: Abstract class, encapsulation, pure virtual function,
 * virtual destructor, and access specifiers.
 */

#include "Person.h"

#include <iostream>
#include <stdexcept>

Person::Person()
    : Person(defaultName, defaultCnic, defaultAge, defaultContact) {
}

Person::Person(const std::string& newName,
               const std::string& newCnic,
               int newAge,
               const std::string& newContact)
    : name(newName),
      cnic(newCnic),
      age(newAge),
      contact(newContact) {
    validatePersonData();
}

Person::~Person() = default;

const std::string& Person::getName() const {
    return name;
}

const std::string& Person::getCnic() const {
    return cnic;
}

int Person::getAge() const {
    return age;
}

const std::string& Person::getContact() const {
    return contact;
}

void Person::setName(const std::string& newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Person name cannot be empty.");
    }
    name = newName;
}

void Person::setCnic(const std::string& newCnic) {
    if (newCnic.empty()) {
        throw std::invalid_argument("CNIC cannot be empty.");
    }
    cnic = newCnic;
}

void Person::setAge(int newAge) {
    if (newAge <= minimumAge) {
        throw std::invalid_argument("Age must be positive.");
    }
    age = newAge;
}

void Person::setContact(const std::string& newContact) {
    if (newContact.empty()) {
        throw std::invalid_argument("Contact cannot be empty.");
    }
    contact = newContact;
}

void Person::displayPersonInfo() const {
    std::cout << "Name: " << name << '\n'
              << "CNIC: " << cnic << '\n'
              << "Age: " << age << '\n'
              << "Contact: " << contact << '\n';
}

void Person::validatePersonData() const {
    if (name.empty()) {
        throw std::invalid_argument("Person name cannot be empty.");
    }
    if (cnic.empty()) {
        throw std::invalid_argument("CNIC cannot be empty.");
    }
    if (age <= minimumAge) {
        throw std::invalid_argument("Age must be positive.");
    }
    if (contact.empty()) {
        throw std::invalid_argument("Contact cannot be empty.");
    }
}

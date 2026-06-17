/**
 * @file FeeRecord.cpp
 * @brief FeeRecord derived class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "FeeRecord.h"

#include <iostream>
#include <stdexcept>

int FeeRecord::totalFeeRecords = FeeRecord::initialRecordCount;

FeeRecord::FeeRecord()
    : FinancialRecord(defaultRecordId,
                      defaultDescription,
                      defaultAmount,
                      defaultTransactionDate),
      studentRollNo(defaultStudentRollNo),
      studentName(defaultStudentName),
      semester(defaultSemester),
      feePaid(defaultFeePaid) {
    validateData();
    ++totalFeeRecords;
}

FeeRecord::FeeRecord(const std::string& newRecordId,
                     const std::string& newDescription,
                     double newAmount,
                     const std::string& newTransactionDate,
                     const std::string& newStudentRollNo,
                     const std::string& newStudentName,
                     const std::string& newSemester,
                     bool newFeePaid)
    : FinancialRecord(newRecordId, newDescription, newAmount, newTransactionDate),
      studentRollNo(newStudentRollNo),
      studentName(newStudentName),
      semester(newSemester),
      feePaid(newFeePaid) {
    validateData();
    ++totalFeeRecords;
}

FeeRecord::FeeRecord(const FeeRecord& other)
    : FinancialRecord(other),
      studentRollNo(other.studentRollNo),
      studentName(other.studentName),
      semester(other.semester),
      feePaid(other.feePaid) {
    ++totalFeeRecords;
}

FeeRecord& FeeRecord::operator=(const FeeRecord& other) {
    if (this != &other) {
        FinancialRecord::operator=(other);
        studentRollNo = other.studentRollNo;
        studentName = other.studentName;
        semester = other.semester;
        feePaid = other.feePaid;
    }
    return *this;
}

FeeRecord::~FeeRecord() = default;

const std::string& FeeRecord::getStudentRollNo() const {
    return studentRollNo;
}

const std::string& FeeRecord::getStudentName() const {
    return studentName;
}

const std::string& FeeRecord::getSemester() const {
    return semester;
}

bool FeeRecord::getFeePaid() const {
    return feePaid;
}

void FeeRecord::setStudentRollNo(const std::string& newStudentRollNo) {
    if (newStudentRollNo.empty()) {
        throw std::invalid_argument("Student roll number cannot be empty.");
    }

    studentRollNo = newStudentRollNo;
}

void FeeRecord::setStudentName(const std::string& newStudentName) {
    if (newStudentName.empty()) {
        throw std::invalid_argument("Student name cannot be empty.");
    }

    studentName = newStudentName;
}

void FeeRecord::setSemester(const std::string& newSemester) {
    if (newSemester.empty()) {
        throw std::invalid_argument("Semester cannot be empty.");
    }

    semester = newSemester;
}

void FeeRecord::setFeePaid(bool newFeePaid) {
    feePaid = newFeePaid;
}

void FeeRecord::validateData() const {
    FinancialRecord::validateData();

    if (studentRollNo.empty()) {
        throw std::invalid_argument("Student roll number cannot be empty.");
    }

    if (studentName.empty()) {
        throw std::invalid_argument("Student name cannot be empty.");
    }

    if (semester.empty()) {
        throw std::invalid_argument("Semester cannot be empty.");
    }
}

void FeeRecord::markPaid() {
    feePaid = true;
}

void FeeRecord::displayRecord() const {
    std::cout << "Fee Record\n"
              << "Record ID: " << getRecordId() << '\n'
              << "Description: " << getDescription() << '\n'
              << "Amount: " << getAmount() << '\n'
              << "Transaction Date: " << getTransactionDate() << '\n'
              << "Student Roll No: " << studentRollNo << '\n'
              << "Student Name: " << studentName << '\n'
              << "Semester: " << semester << '\n'
              << "Fee Paid: " << (feePaid ? "Yes" : "No") << '\n';
}

FeeRecord& FeeRecord::operator-=(double discountAmount) {
    constexpr double minimumDiscount = 0.0;
    if (discountAmount <= minimumDiscount) {
        throw std::invalid_argument("Fee discount must be positive.");
    }

    const double discountedAmount = getAmount() - discountAmount;
    if (discountedAmount <= minimumDiscount) {
        throw std::invalid_argument(
            "Fee discount must leave a positive outstanding amount.");
    }

    setAmount(discountedAmount);
    return *this;
}

int FeeRecord::getTotalFeeRecords() {
    return totalFeeRecords;
}

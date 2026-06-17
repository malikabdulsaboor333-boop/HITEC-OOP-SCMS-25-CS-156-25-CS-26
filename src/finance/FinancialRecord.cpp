/**
 * @file FinancialRecord.cpp
 * @brief FinancialRecord base class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "FinancialRecord.h"

#include <iostream>
#include <stdexcept>

FinancialRecord::FinancialRecord()
    : FinancialRecord(defaultRecordId,
                      defaultDescription,
                      defaultAmount,
                      defaultTransactionDate) {
}

FinancialRecord::FinancialRecord(const std::string& newRecordId,
                                 const std::string& newDescription,
                                 double newAmount,
                                 const std::string& newTransactionDate)
    : recordId(newRecordId),
      description(newDescription),
      amount(newAmount),
      transactionDate(newTransactionDate) {
    validateData();
}

FinancialRecord::FinancialRecord(const FinancialRecord& other) = default;

FinancialRecord& FinancialRecord::operator=(
    const FinancialRecord& other) = default;

FinancialRecord::FinancialRecord(FinancialRecord&& other) noexcept = default;

FinancialRecord& FinancialRecord::operator=(
    FinancialRecord&& other) noexcept = default;

FinancialRecord::~FinancialRecord() = default;

const std::string& FinancialRecord::getRecordId() const {
    return recordId;
}

const std::string& FinancialRecord::getDescription() const {
    return description;
}

double FinancialRecord::getAmount() const {
    return amount;
}

const std::string& FinancialRecord::getTransactionDate() const {
    return transactionDate;
}

void FinancialRecord::setRecordId(const std::string& newRecordId) {
    if (newRecordId.empty()) {
        throw std::invalid_argument("Record ID cannot be empty.");
    }

    recordId = newRecordId;
}

void FinancialRecord::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void FinancialRecord::setAmount(double newAmount) {
    if (newAmount <= minimumPositiveAmount) {
        throw std::invalid_argument("Amount must be positive.");
    }

    amount = newAmount;
}

void FinancialRecord::setTransactionDate(const std::string& newTransactionDate) {
    if (newTransactionDate.empty()) {
        throw std::invalid_argument("Transaction date cannot be empty.");
    }

    transactionDate = newTransactionDate;
}

void FinancialRecord::validateData() const {
    if (recordId.empty()) {
        throw std::invalid_argument("Record ID cannot be empty.");
    }

    if (amount <= minimumPositiveAmount) {
        throw std::invalid_argument("Amount must be positive.");
    }

    if (transactionDate.empty()) {
        throw std::invalid_argument("Transaction date cannot be empty.");
    }
}

void FinancialRecord::displayRecord() const {
    std::cout << "Financial Record\n"
              << "Record ID: " << recordId << '\n'
              << "Description: " << description << '\n'
              << "Amount: " << amount << '\n'
              << "Transaction Date: " << transactionDate << '\n';
}

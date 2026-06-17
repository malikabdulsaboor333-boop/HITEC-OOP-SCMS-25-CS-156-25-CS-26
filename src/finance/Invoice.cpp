/**
 * @file Invoice.cpp
 * @brief Invoice class implementation with Rule of Five semantics
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Invoice.h"

#include <iostream>
#include <stdexcept>
#include <utility>

int Invoice::invoiceCounter = Invoice::initialInvoiceCount;

Invoice::Invoice()
    : Invoice(defaultRecordId,
              defaultDescription,
              defaultAmount,
              defaultTransactionDate,
              defaultInvoiceNumber,
              defaultPayerName,
              {},
              false) {
}

Invoice::Invoice(const std::string& newRecordId,
                 const std::string& newDescription,
                 double newAmount,
                 const std::string& newTransactionDate,
                 const std::string& newInvoiceNumber,
                 const std::string& newPayerName,
                 const std::vector<std::string>& newLineItems,
                 bool newPaid)
    : FinancialRecord(
          newRecordId, newDescription, newAmount, newTransactionDate),
      invoiceNumber(newInvoiceNumber),
      payerName(newPayerName),
      lineItems(newLineItems),
      paid(newPaid) {
    validateData();
    ++invoiceCounter;
}

Invoice::Invoice(const Invoice& other)
    : FinancialRecord(other),
      invoiceNumber(other.invoiceNumber),
      payerName(other.payerName),
      lineItems(other.lineItems),
      paid(other.paid) {
    ++invoiceCounter;
}

Invoice& Invoice::operator=(const Invoice& other) {
    if (this != &other) {
        FinancialRecord::operator=(other);
        invoiceNumber = other.invoiceNumber;
        payerName = other.payerName;
        lineItems = other.lineItems;
        paid = other.paid;
    }
    return *this;
}

Invoice::Invoice(Invoice&& other) noexcept
    : FinancialRecord(std::move(other)),
      invoiceNumber(std::move(other.invoiceNumber)),
      payerName(std::move(other.payerName)),
      lineItems(std::move(other.lineItems)),
      paid(other.paid) {
    ++invoiceCounter;
}

Invoice& Invoice::operator=(Invoice&& other) noexcept {
    if (this != &other) {
        FinancialRecord::operator=(std::move(other));
        invoiceNumber = std::move(other.invoiceNumber);
        payerName = std::move(other.payerName);
        lineItems = std::move(other.lineItems);
        paid = other.paid;
    }
    return *this;
}

Invoice::~Invoice() = default;

const std::string& Invoice::getInvoiceNumber() const {
    return invoiceNumber;
}

const std::string& Invoice::getPayerName() const {
    return payerName;
}

const std::vector<std::string>& Invoice::getLineItems() const {
    return lineItems;
}

bool Invoice::getPaid() const {
    return paid;
}

void Invoice::setInvoiceNumber(const std::string& newInvoiceNumber) {
    if (newInvoiceNumber.empty()) {
        throw std::invalid_argument("Invoice number cannot be empty.");
    }
    invoiceNumber = newInvoiceNumber;
}

void Invoice::setPayerName(const std::string& newPayerName) {
    if (newPayerName.empty()) {
        throw std::invalid_argument("Invoice payer name cannot be empty.");
    }
    payerName = newPayerName;
}

void Invoice::setPaid(bool newPaid) {
    paid = newPaid;
}

void Invoice::addLineItem(const std::string& lineItem) {
    if (lineItem.empty()) {
        throw std::invalid_argument("Invoice line item cannot be empty.");
    }
    lineItems.push_back(lineItem);
}

void Invoice::validateData() const {
    FinancialRecord::validateData();
    if (invoiceNumber.empty() || payerName.empty()) {
        throw std::invalid_argument(
            "Invoice number and payer name cannot be empty.");
    }
}

void Invoice::displayRecord() const {
    std::cout << "Invoice\n"
              << "Record ID: " << getRecordId() << '\n'
              << "Invoice Number: " << invoiceNumber << '\n'
              << "Payer: " << payerName << '\n'
              << "Amount: " << getAmount() << '\n'
              << "Paid: " << (paid ? "Yes" : "No") << '\n'
              << "Line Items: " << lineItems.size() << '\n';
}

int Invoice::getInvoiceCounter() {
    return invoiceCounter;
}

void Invoice::restoreInvoiceCounter(int persistedCounter) {
    if (persistedCounter > invoiceCounter) {
        invoiceCounter = persistedCounter;
    }
}

/**
 * @file FinanceManager.cpp
 * @brief FinanceManager class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "FinanceManager.h"

#include "../utils/CsvUtils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>

FinanceManager::FinanceManager() = default;

bool FinanceManager::addSalaryRecord(const SalaryRecord& salaryRecord) {
    if (searchRecordById(salaryRecord.getRecordId()) != nullptr) {
        return false;
    }

    salaryRecord.validateData();
    salaryRecords.push_back(salaryRecord);
    return true;
}

bool FinanceManager::addFeeRecord(const FeeRecord& feeRecord) {
    if (searchRecordById(feeRecord.getRecordId()) != nullptr) {
        return false;
    }

    feeRecord.validateData();
    feeRecords.push_back(feeRecord);
    return true;
}

bool FinanceManager::addInvoice(const Invoice& invoice) {
    const auto duplicate = std::find_if(
        invoices.begin(),
        invoices.end(),
        [&invoice](const Invoice& currentInvoice) {
            return currentInvoice.getRecordId() == invoice.getRecordId()
                || currentInvoice.getInvoiceNumber()
                    == invoice.getInvoiceNumber();
        });
    if (duplicate != invoices.end()
        || searchRecordById(invoice.getRecordId()) != nullptr) {
        return false;
    }

    invoice.validateData();
    invoices.push_back(invoice);
    return true;
}

FinancialRecord* FinanceManager::searchRecordById(const std::string& recordId) {
    const auto salaryRecord = std::find_if(
        salaryRecords.begin(),
        salaryRecords.end(),
        [&recordId](const SalaryRecord& record) {
            return record.getRecordId() == recordId;
        });

    if (salaryRecord != salaryRecords.end()) {
        return &(*salaryRecord);
    }

    const auto feeRecord = std::find_if(
        feeRecords.begin(),
        feeRecords.end(),
        [&recordId](const FeeRecord& record) {
            return record.getRecordId() == recordId;
        });

    return feeRecord == feeRecords.end() ? nullptr : &(*feeRecord);
}

const FinancialRecord* FinanceManager::searchRecordById(
    const std::string& recordId) const {
    const auto salaryRecord = std::find_if(
        salaryRecords.begin(),
        salaryRecords.end(),
        [&recordId](const SalaryRecord& record) {
            return record.getRecordId() == recordId;
        });

    if (salaryRecord != salaryRecords.end()) {
        return &(*salaryRecord);
    }

    const auto feeRecord = std::find_if(
        feeRecords.begin(),
        feeRecords.end(),
        [&recordId](const FeeRecord& record) {
            return record.getRecordId() == recordId;
        });

    return feeRecord == feeRecords.end() ? nullptr : &(*feeRecord);
}

bool FinanceManager::removeRecord(const std::string& recordId) {
    const auto salaryRecord = std::find_if(
        salaryRecords.begin(),
        salaryRecords.end(),
        [&recordId](const SalaryRecord& record) {
            return record.getRecordId() == recordId;
        });

    if (salaryRecord != salaryRecords.end()) {
        salaryRecords.erase(salaryRecord);
        return true;
    }

    const auto feeRecord = std::find_if(
        feeRecords.begin(),
        feeRecords.end(),
        [&recordId](const FeeRecord& record) {
            return record.getRecordId() == recordId;
        });

    if (feeRecord != feeRecords.end()) {
        feeRecords.erase(feeRecord);
        return true;
    }

    return false;
}

void FinanceManager::displayAllRecords() const {
    if (salaryRecords.empty() && feeRecords.empty()) {
        std::cout << "No financial records available.\n";
        return;
    }

    for (const SalaryRecord& salaryRecord : salaryRecords) {
        const FinancialRecord& record = salaryRecord;
        record.displayRecord();
        std::cout << '\n';
    }

    for (const FeeRecord& feeRecord : feeRecords) {
        const FinancialRecord& record = feeRecord;
        record.displayRecord();
        std::cout << '\n';
    }
}

double FinanceManager::calculateTotalSalaryExpense() const {
    constexpr double initialTotalAmount = 0.0;
    double totalSalaryExpense = initialTotalAmount;

    for (const SalaryRecord& salaryRecord : salaryRecords) {
        totalSalaryExpense += salaryRecord.calculateNetSalary();
    }

    return totalSalaryExpense;
}

double FinanceManager::calculateTotalCollectedFees() const {
    constexpr double initialTotalAmount = 0.0;
    double totalCollectedFees = initialTotalAmount;

    for (const FeeRecord& feeRecord : feeRecords) {
        if (feeRecord.getFeePaid()) {
            totalCollectedFees += feeRecord.getAmount();
        }
    }

    return totalCollectedFees;
}

const std::vector<SalaryRecord>& FinanceManager::getSalaryRecords() const {
    return salaryRecords;
}

const std::vector<FeeRecord>& FinanceManager::getFeeRecords() const {
    return feeRecords;
}

const std::vector<Invoice>& FinanceManager::getInvoices() const {
    return invoices;
}

bool FinanceManager::saveToCsv(const std::string& filePath,
                               bool append) const {
    if (filePath.empty()) {
        return false;
    }

    constexpr const char* header =
        "RecordType,RecordId,Description,TransactionDate,PartyId,"
        "PartyName,Amount,AllowanceOrSemester,DeductionOrPaid";
    std::ofstream output;
    if (!SCMS::Persistence::CsvUtils::openOutput(
            output, filePath, header, append)) {
        return false;
    }

    for (const SalaryRecord& record : salaryRecords) {
        output << "SALARY,"
               << SCMS::Persistence::CsvUtils::escape(record.getRecordId())
               << ','
               << SCMS::Persistence::CsvUtils::escape(record.getDescription())
               << ','
               << SCMS::Persistence::CsvUtils::escape(
                      record.getTransactionDate())
               << ','
               << SCMS::Persistence::CsvUtils::escape(record.getEmployeeId())
               << ','
               << SCMS::Persistence::CsvUtils::escape(
                      record.getEmployeeName())
               << ','
               << record.getBasicSalary() << ','
               << record.getAllowance() << ','
               << record.getDeduction() << '\n';
    }

    for (const FeeRecord& record : feeRecords) {
        output << "FEE,"
               << SCMS::Persistence::CsvUtils::escape(record.getRecordId())
               << ','
               << SCMS::Persistence::CsvUtils::escape(record.getDescription())
               << ','
               << record.getAmount() << ','
               << SCMS::Persistence::CsvUtils::escape(
                      record.getTransactionDate())
               << ','
               << SCMS::Persistence::CsvUtils::escape(
                      record.getStudentRollNo())
               << ','
               << SCMS::Persistence::CsvUtils::escape(record.getStudentName())
               << ','
               << SCMS::Persistence::CsvUtils::escape(record.getSemester())
               << ','
               << record.getFeePaid() << '\n';
    }

    return output.good();
}

bool FinanceManager::loadFromCsv(const std::string& filePath) {
    if (filePath.empty()) {
        return false;
    }

    std::ifstream input(filePath);
    if (!input) {
        return false;
    }

    std::vector<SalaryRecord> loadedSalaryRecords;
    std::vector<FeeRecord> loadedFeeRecords;
    std::set<std::string> loadedRecordIds;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        const std::vector<std::string> fields =
            SCMS::Persistence::CsvUtils::parseLine(line);
        if (fields.empty() || fields[0] == "RecordType"
            || fields.size() != 9U) {
            continue;
        }

        try {
            if (fields[0] == "SALARY") {
                double basicSalary = 0.0;
                double allowance = 0.0;
                double deduction = 0.0;
                if (!SCMS::Persistence::CsvUtils::parseDouble(
                        fields[6], basicSalary)
                    || !SCMS::Persistence::CsvUtils::parseDouble(
                        fields[7], allowance)
                    || !SCMS::Persistence::CsvUtils::parseDouble(
                        fields[8], deduction)
                    || !loadedRecordIds.insert(fields[1]).second) {
                    continue;
                }

                loadedSalaryRecords.emplace_back(
                    fields[1],
                    fields[2],
                    fields[3],
                    fields[4],
                    fields[5],
                    basicSalary,
                    allowance,
                    deduction);
            } else if (fields[0] == "FEE") {
                double amount = 0.0;
                bool feePaid = false;
                if (!SCMS::Persistence::CsvUtils::parseDouble(
                        fields[3], amount)
                    || !SCMS::Persistence::CsvUtils::parseBool(
                        fields[8], feePaid)
                    || !loadedRecordIds.insert(fields[1]).second) {
                    continue;
                }

                loadedFeeRecords.emplace_back(
                    fields[1],
                    fields[2],
                    amount,
                    fields[4],
                    fields[5],
                    fields[6],
                    fields[7],
                    feePaid);
            }
        } catch (const std::exception&) {
            loadedRecordIds.erase(fields[1]);
        }
    }

    salaryRecords = std::move(loadedSalaryRecords);
    feeRecords = std::move(loadedFeeRecords);
    return true;
}

bool FinanceManager::saveInvoice(const std::string& filePath,
                                 const Invoice& invoice,
                                 bool append) const {
    constexpr const char* header =
        "RecordType,RecordId,Description,Amount,TransactionDate,"
        "InvoiceNumber,PayerName,Paid,InvoiceCounter,LineItemCount,"
        "LineItems";
    std::ofstream output;
    if (!SCMS::Persistence::CsvUtils::openOutput(
            output, filePath, header, append)) {
        return false;
    }

    output << "INVOICE,"
           << SCMS::Persistence::CsvUtils::escape(invoice.getRecordId())
           << ','
           << SCMS::Persistence::CsvUtils::escape(invoice.getDescription())
           << ',' << invoice.getAmount() << ','
           << SCMS::Persistence::CsvUtils::escape(
                  invoice.getTransactionDate())
           << ','
           << SCMS::Persistence::CsvUtils::escape(
                  invoice.getInvoiceNumber())
           << ','
           << SCMS::Persistence::CsvUtils::escape(invoice.getPayerName())
           << ',' << invoice.getPaid() << ','
           << Invoice::getInvoiceCounter() << ','
           << invoice.getLineItems().size();
    for (const std::string& lineItem : invoice.getLineItems()) {
        output << ',' << SCMS::Persistence::CsvUtils::escape(lineItem);
    }
    output << '\n';
    return output.good();
}

bool FinanceManager::saveInvoices(const std::string& filePath,
                                  bool append) const {
    constexpr const char* header =
        "RecordType,RecordId,Description,Amount,TransactionDate,"
        "InvoiceNumber,PayerName,Paid,InvoiceCounter,LineItemCount,"
        "LineItems";
    std::ofstream output;
    if (!SCMS::Persistence::CsvUtils::openOutput(
            output, filePath, header, append)) {
        return false;
    }
    output.close();

    bool nextAppend = true;
    for (const Invoice& invoice : invoices) {
        if (!saveInvoice(filePath, invoice, nextAppend)) {
            return false;
        }
        nextAppend = true;
    }
    return true;
}

bool FinanceManager::loadInvoices(const std::string& filePath) {
    if (filePath.empty()) {
        return false;
    }

    std::ifstream input(filePath);
    if (!input) {
        return false;
    }

    std::vector<Invoice> loadedInvoices;
    std::set<std::string> recordIds;
    std::set<std::string> invoiceNumbers;
    int persistedCounter = 0;
    std::string line;

    while (std::getline(input, line)) {
        const std::vector<std::string> fields =
            SCMS::Persistence::CsvUtils::parseLine(line);
        if (fields.empty() || fields[0] == "RecordType"
            || fields[0] != "INVOICE" || fields.size() < 10U) {
            continue;
        }

        double amount = 0.0;
        bool paid = false;
        int rowCounter = 0;
        int lineItemCount = 0;
        if (!SCMS::Persistence::CsvUtils::parseDouble(fields[3], amount)
            || !SCMS::Persistence::CsvUtils::parseBool(fields[7], paid)
            || !SCMS::Persistence::CsvUtils::parseInt(
                fields[8], rowCounter)
            || !SCMS::Persistence::CsvUtils::parseInt(
                fields[9], lineItemCount)
            || lineItemCount < 0
            || fields.size()
                != 10U + static_cast<std::size_t>(lineItemCount)
            || recordIds.find(fields[1]) != recordIds.end()
            || invoiceNumbers.find(fields[5]) != invoiceNumbers.end()) {
            continue;
        }

        std::vector<std::string> lineItems(
            fields.begin() + 10, fields.end());
        try {
            loadedInvoices.emplace_back(
                fields[1],
                fields[2],
                amount,
                fields[4],
                fields[5],
                fields[6],
                lineItems,
                paid);
            recordIds.insert(fields[1]);
            invoiceNumbers.insert(fields[5]);
            persistedCounter = std::max(persistedCounter, rowCounter);
        } catch (const std::exception&) {
            continue;
        }
    }

    invoices = std::move(loadedInvoices);
    Invoice::restoreInvoiceCounter(persistedCounter);
    return true;
}

std::string generateFinanceSummary(const FinanceManager& financeManager) {
    std::ostringstream summary;

    summary << "Finance Summary Report\n"
            << "Salary Records: " << financeManager.salaryRecords.size() << '\n'
            << "Fee Records: " << financeManager.feeRecords.size() << '\n'
            << "Total Salary Expense: "
            << financeManager.calculateTotalSalaryExpense() << '\n'
            << "Total Collected Fees: "
            << financeManager.calculateTotalCollectedFees() << '\n';

    summary << "Salary Details:\n";
    for (const SalaryRecord& salaryRecord : financeManager.salaryRecords) {
        const FinancialRecord& baseRecord = salaryRecord;
        summary << baseRecord.recordId << " | "
                << salaryRecord.employeeId << " | "
                << salaryRecord.employeeName << " | "
                << salaryRecord.calculateNetSalary() << '\n';
    }

    summary << "Fee Details:\n";
    for (const FeeRecord& feeRecord : financeManager.feeRecords) {
        const FinancialRecord& baseRecord = feeRecord;
        summary << baseRecord.recordId << " | "
                << feeRecord.studentRollNo << " | "
                << feeRecord.studentName << " | "
                << baseRecord.amount << " | "
                << (feeRecord.feePaid ? "Paid" : "Unpaid") << '\n';
    }

    return summary.str();
}

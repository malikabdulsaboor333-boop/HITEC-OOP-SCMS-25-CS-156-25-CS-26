/**
 * @file FinanceManager.h
 * @brief FinanceManager class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_FINANCE_FINANCE_MANAGER_H
#define SCMS_FINANCE_FINANCE_MANAGER_H

#include "FeeRecord.h"
#include "Invoice.h"
#include "SalaryRecord.h"

#include <string>
#include <vector>

class FinanceManager {
public:
    FinanceManager();

    bool addSalaryRecord(const SalaryRecord& salaryRecord);
    bool addFeeRecord(const FeeRecord& feeRecord);
    bool addInvoice(const Invoice& invoice);

    FinancialRecord* searchRecordById(const std::string& recordId);
    const FinancialRecord* searchRecordById(const std::string& recordId) const;

    bool removeRecord(const std::string& recordId);
    void displayAllRecords() const;

    double calculateTotalSalaryExpense() const;
    double calculateTotalCollectedFees() const;
    const std::vector<SalaryRecord>& getSalaryRecords() const;
    const std::vector<FeeRecord>& getFeeRecords() const;
    const std::vector<Invoice>& getInvoices() const;

    bool saveToCsv(const std::string& filePath, bool append = false) const;
    bool loadFromCsv(const std::string& filePath);
    bool saveInvoice(const std::string& filePath,
                     const Invoice& invoice,
                     bool append = true) const;
    bool saveInvoices(const std::string& filePath,
                      bool append = false) const;
    bool loadInvoices(const std::string& filePath);

private:
    friend std::string generateFinanceSummary(const FinanceManager& financeManager);

    std::vector<SalaryRecord> salaryRecords;
    std::vector<FeeRecord> feeRecords;
    std::vector<Invoice> invoices;
};

#endif

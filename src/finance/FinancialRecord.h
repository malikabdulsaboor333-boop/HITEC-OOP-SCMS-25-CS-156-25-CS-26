/**
 * @file FinancialRecord.h
 * @brief FinancialRecord base class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_FINANCE_FINANCIAL_RECORD_H
#define SCMS_FINANCE_FINANCIAL_RECORD_H

#include <string>

class FinanceManager;

std::string generateFinanceSummary(const FinanceManager& financeManager);

class FinancialRecord {
public:
    FinancialRecord();
    FinancialRecord(const std::string& newRecordId,
                    const std::string& newDescription,
                    double newAmount,
                    const std::string& newTransactionDate);
    FinancialRecord(const FinancialRecord& other);
    FinancialRecord& operator=(const FinancialRecord& other);
    FinancialRecord(FinancialRecord&& other) noexcept;
    FinancialRecord& operator=(FinancialRecord&& other) noexcept;
    virtual ~FinancialRecord();

    const std::string& getRecordId() const;
    const std::string& getDescription() const;
    double getAmount() const;
    const std::string& getTransactionDate() const;

    void setRecordId(const std::string& newRecordId);
    void setDescription(const std::string& newDescription);
    void setAmount(double newAmount);
    void setTransactionDate(const std::string& newTransactionDate);

    virtual void validateData() const;
    virtual void displayRecord() const;

private:
    friend std::string generateFinanceSummary(const FinanceManager& financeManager);

    static constexpr const char* defaultRecordId = "DEFAULT_RECORD";
    static constexpr const char* defaultDescription = "Initial financial record";
    static constexpr const char* defaultTransactionDate = "1970-01-01";
    static constexpr double defaultAmount = 1.0;
    static constexpr double minimumPositiveAmount = 0.0;

    std::string recordId;
    std::string description;
    double amount;
    std::string transactionDate;
};

#endif

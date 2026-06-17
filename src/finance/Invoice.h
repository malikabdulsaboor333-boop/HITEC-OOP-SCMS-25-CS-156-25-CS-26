/**
 * @file Invoice.h
 * @brief Invoice class declaration with Rule of Five semantics
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_FINANCE_INVOICE_H
#define SCMS_FINANCE_INVOICE_H

#include "FinancialRecord.h"

#include <string>
#include <vector>

class Invoice : public FinancialRecord {
public:
    Invoice();
    Invoice(const std::string& newRecordId,
            const std::string& newDescription,
            double newAmount,
            const std::string& newTransactionDate,
            const std::string& newInvoiceNumber,
            const std::string& newPayerName,
            const std::vector<std::string>& newLineItems,
            bool newPaid);
    Invoice(const Invoice& other);
    Invoice& operator=(const Invoice& other);
    Invoice(Invoice&& other) noexcept;
    Invoice& operator=(Invoice&& other) noexcept;
    ~Invoice() override;

    const std::string& getInvoiceNumber() const;
    const std::string& getPayerName() const;
    const std::vector<std::string>& getLineItems() const;
    bool getPaid() const;

    void setInvoiceNumber(const std::string& newInvoiceNumber);
    void setPayerName(const std::string& newPayerName);
    void setPaid(bool newPaid);
    void addLineItem(const std::string& lineItem);

    void validateData() const override;
    void displayRecord() const override;

    static int getInvoiceCounter();

private:
    friend class FinanceManager;

    static void restoreInvoiceCounter(int persistedCounter);

    static constexpr const char* defaultRecordId = "DEFAULT_INVOICE_RECORD";
    static constexpr const char* defaultDescription = "Initial invoice";
    static constexpr const char* defaultTransactionDate = "1970-01-01";
    static constexpr const char* defaultInvoiceNumber = "DEFAULT_INVOICE";
    static constexpr const char* defaultPayerName = "Unknown Payer";
    static constexpr double defaultAmount = 1.0;
    static constexpr int initialInvoiceCount = 0;

    static int invoiceCounter;

    std::string invoiceNumber;
    std::string payerName;
    std::vector<std::string> lineItems;
    bool paid;
};

#endif

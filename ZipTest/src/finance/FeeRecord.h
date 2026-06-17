/**
 * @file FeeRecord.h
 * @brief FeeRecord derived class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_FINANCE_FEE_RECORD_H
#define SCMS_FINANCE_FEE_RECORD_H

#include "FinancialRecord.h"

#include <string>

class FeeRecord : public FinancialRecord {
public:
    FeeRecord();
    FeeRecord(const std::string& newRecordId,
              const std::string& newDescription,
              double newAmount,
              const std::string& newTransactionDate,
              const std::string& newStudentRollNo,
              const std::string& newStudentName,
              const std::string& newSemester,
              bool newFeePaid);
    FeeRecord(const FeeRecord& other);
    FeeRecord& operator=(const FeeRecord& other);
    ~FeeRecord() override;

    const std::string& getStudentRollNo() const;
    const std::string& getStudentName() const;
    const std::string& getSemester() const;
    bool getFeePaid() const;

    void setStudentRollNo(const std::string& newStudentRollNo);
    void setStudentName(const std::string& newStudentName);
    void setSemester(const std::string& newSemester);
    void setFeePaid(bool newFeePaid);

    void validateData() const override;
    void markPaid();
    void displayRecord() const override;
    FeeRecord& operator-=(double discountAmount);

    static int getTotalFeeRecords();

private:
    friend std::string generateFinanceSummary(const FinanceManager& financeManager);

    static constexpr const char* defaultRecordId = "DEFAULT_FEE_RECORD";
    static constexpr const char* defaultDescription = "Initial fee record";
    static constexpr const char* defaultTransactionDate = "1970-01-01";
    static constexpr const char* defaultStudentRollNo = "DEFAULT_ROLL_NO";
    static constexpr const char* defaultStudentName = "Initial Student";
    static constexpr const char* defaultSemester = "Initial Semester";
    static constexpr double defaultAmount = 1.0;
    static constexpr bool defaultFeePaid = false;
    static constexpr int initialRecordCount = 0;

    static int totalFeeRecords;

    std::string studentRollNo;
    std::string studentName;
    std::string semester;
    bool feePaid;
};

#endif

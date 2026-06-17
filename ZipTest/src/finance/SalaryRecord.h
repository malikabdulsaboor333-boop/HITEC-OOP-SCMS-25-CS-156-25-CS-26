/**
 * @file SalaryRecord.h
 * @brief SalaryRecord derived class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_FINANCE_SALARY_RECORD_H
#define SCMS_FINANCE_SALARY_RECORD_H

#include "FinancialRecord.h"

#include <string>

class SalaryRecord : public FinancialRecord {
public:
    SalaryRecord();
    SalaryRecord(const std::string& newRecordId,
                 const std::string& newDescription,
                 const std::string& newTransactionDate,
                 const std::string& newEmployeeId,
                 const std::string& newEmployeeName,
                 double newBasicSalary,
                 double newAllowance,
                 double newDeduction);
    ~SalaryRecord() override;

    const std::string& getEmployeeId() const;
    const std::string& getEmployeeName() const;
    double getBasicSalary() const;
    double getAllowance() const;
    double getDeduction() const;

    void setEmployeeId(const std::string& newEmployeeId);
    void setEmployeeName(const std::string& newEmployeeName);
    void setBasicSalary(double newBasicSalary);
    void setAllowance(double newAllowance);
    void setDeduction(double newDeduction);

    void validateData() const override;
    double calculateNetSalary() const;
    void displayRecord() const override;

    static int getTotalSalaryRecords();

private:
    friend std::string generateFinanceSummary(const FinanceManager& financeManager);

    void updateRecordAmount();

    static constexpr const char* defaultRecordId = "DEFAULT_SALARY_RECORD";
    static constexpr const char* defaultDescription = "Initial salary record";
    static constexpr const char* defaultTransactionDate = "1970-01-01";
    static constexpr const char* defaultEmployeeId = "DEFAULT_EMPLOYEE";
    static constexpr const char* defaultEmployeeName = "Initial Employee";
    static constexpr double defaultBasicSalary = 1.0;
    static constexpr double defaultAllowance = 0.0;
    static constexpr double defaultDeduction = 0.0;
    static constexpr double minimumPositiveAmount = 0.0;
    static constexpr double minimumNonNegativeAmount = 0.0;
    static constexpr int initialRecordCount = 0;

    static int totalSalaryRecords;

    std::string employeeId;
    std::string employeeName;
    double basicSalary;
    double allowance;
    double deduction;
};

#endif

/**
 * @file SalaryRecord.cpp
 * @brief SalaryRecord derived class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "SalaryRecord.h"

#include <iostream>
#include <stdexcept>

int SalaryRecord::totalSalaryRecords = SalaryRecord::initialRecordCount;

SalaryRecord::SalaryRecord()
    : FinancialRecord(defaultRecordId,
                      defaultDescription,
                      defaultBasicSalary,
                      defaultTransactionDate),
      employeeId(defaultEmployeeId),
      employeeName(defaultEmployeeName),
      basicSalary(defaultBasicSalary),
      allowance(defaultAllowance),
      deduction(defaultDeduction) {
    validateData();
    ++totalSalaryRecords;
}

SalaryRecord::SalaryRecord(const std::string& newRecordId,
                           const std::string& newDescription,
                           const std::string& newTransactionDate,
                           const std::string& newEmployeeId,
                           const std::string& newEmployeeName,
                           double newBasicSalary,
                           double newAllowance,
                           double newDeduction)
    : FinancialRecord(newRecordId,
                      newDescription,
                      newBasicSalary + newAllowance - newDeduction,
                      newTransactionDate),
      employeeId(newEmployeeId),
      employeeName(newEmployeeName),
      basicSalary(newBasicSalary),
      allowance(newAllowance),
      deduction(newDeduction) {
    validateData();
    ++totalSalaryRecords;
}

SalaryRecord::~SalaryRecord() = default;

const std::string& SalaryRecord::getEmployeeId() const {
    return employeeId;
}

const std::string& SalaryRecord::getEmployeeName() const {
    return employeeName;
}

double SalaryRecord::getBasicSalary() const {
    return basicSalary;
}

double SalaryRecord::getAllowance() const {
    return allowance;
}

double SalaryRecord::getDeduction() const {
    return deduction;
}

void SalaryRecord::setEmployeeId(const std::string& newEmployeeId) {
    if (newEmployeeId.empty()) {
        throw std::invalid_argument("Employee ID cannot be empty.");
    }

    employeeId = newEmployeeId;
}

void SalaryRecord::setEmployeeName(const std::string& newEmployeeName) {
    if (newEmployeeName.empty()) {
        throw std::invalid_argument("Employee name cannot be empty.");
    }

    employeeName = newEmployeeName;
}

void SalaryRecord::setBasicSalary(double newBasicSalary) {
    if (newBasicSalary <= minimumPositiveAmount) {
        throw std::invalid_argument("Basic salary must be positive.");
    }

    const double proposedNetSalary = newBasicSalary + allowance - deduction;
    if (proposedNetSalary <= minimumPositiveAmount) {
        throw std::invalid_argument("Net salary must be positive.");
    }

    basicSalary = newBasicSalary;
    updateRecordAmount();
}

void SalaryRecord::setAllowance(double newAllowance) {
    if (newAllowance < minimumNonNegativeAmount) {
        throw std::invalid_argument("Allowance cannot be negative.");
    }

    allowance = newAllowance;
    updateRecordAmount();
}

void SalaryRecord::setDeduction(double newDeduction) {
    if (newDeduction < minimumNonNegativeAmount) {
        throw std::invalid_argument("Deduction cannot be negative.");
    }

    const double proposedNetSalary = basicSalary + allowance - newDeduction;
    if (proposedNetSalary <= minimumPositiveAmount) {
        throw std::invalid_argument("Net salary must be positive.");
    }

    deduction = newDeduction;
    updateRecordAmount();
}

void SalaryRecord::validateData() const {
    FinancialRecord::validateData();

    if (employeeId.empty()) {
        throw std::invalid_argument("Employee ID cannot be empty.");
    }

    if (employeeName.empty()) {
        throw std::invalid_argument("Employee name cannot be empty.");
    }

    if (basicSalary <= minimumPositiveAmount) {
        throw std::invalid_argument("Basic salary must be positive.");
    }

    if (allowance < minimumNonNegativeAmount) {
        throw std::invalid_argument("Allowance cannot be negative.");
    }

    if (deduction < minimumNonNegativeAmount) {
        throw std::invalid_argument("Deduction cannot be negative.");
    }

    if (calculateNetSalary() <= minimumPositiveAmount) {
        throw std::invalid_argument("Net salary must be positive.");
    }
}

double SalaryRecord::calculateNetSalary() const {
    return basicSalary + allowance - deduction;
}

void SalaryRecord::displayRecord() const {
    std::cout << "Salary Record\n"
              << "Record ID: " << getRecordId() << '\n'
              << "Description: " << getDescription() << '\n'
              << "Transaction Date: " << getTransactionDate() << '\n'
              << "Employee ID: " << employeeId << '\n'
              << "Employee Name: " << employeeName << '\n'
              << "Basic Salary: " << basicSalary << '\n'
              << "Allowance: " << allowance << '\n'
              << "Deduction: " << deduction << '\n'
              << "Net Salary: " << calculateNetSalary() << '\n';
}

int SalaryRecord::getTotalSalaryRecords() {
    return totalSalaryRecords;
}

void SalaryRecord::updateRecordAmount() {
    setAmount(calculateNetSalary());
}

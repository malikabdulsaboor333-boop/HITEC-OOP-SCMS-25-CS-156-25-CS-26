/**
 * @file HostelManager.h
 * @brief HostelManager multiple-inheritance class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_HOSTEL_HOSTEL_MANAGER_H
#define SCMS_HOSTEL_HOSTEL_MANAGER_H

#include "Accommodation.h"
#include "HostelBlock.h"
#include "Reportable.h"

#include <cstddef>
#include <string>
#include <vector>

class HostelManager : public Accommodation, public Reportable {
public:
    HostelManager();
    explicit HostelManager(const std::string& newEntityId);
    ~HostelManager() override;

    bool addHostelBlock(const HostelBlock& hostelBlock);
    bool removeHostelBlock(const std::string& blockName);
    HostelBlock* searchBlock(const std::string& blockName);
    const HostelBlock* searchBlock(const std::string& blockName) const;

    bool allocateRoom(const std::string& blockName,
                      const std::string& roomNumber,
                      const std::string& studentRollNo) override;
    bool vacateRoom(const std::string& blockName,
                    const std::string& roomNumber,
                    const std::string& studentRollNo) override;

    void generateReport() const override;
    void displayInfo() const override;

    std::size_t getTotalBlocks() const;
    const std::vector<HostelBlock>& getHostelBlocks() const;

private:
    bool isStudentAssigned(const std::string& studentRollNo) const;

    static constexpr const char* defaultManagerId = "DEFAULT_HOSTEL_MANAGER";
    static constexpr double percentageMultiplier = 100.0;
    static constexpr double emptyOccupancyPercentage = 0.0;

    std::vector<HostelBlock> hostelBlocks;
};

#endif

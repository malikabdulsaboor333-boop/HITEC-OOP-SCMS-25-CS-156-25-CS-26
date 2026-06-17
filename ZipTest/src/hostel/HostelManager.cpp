/**
 * @file HostelManager.cpp
 * @brief HostelManager multiple-inheritance class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "HostelManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

HostelManager::HostelManager()
    : BaseEntity(defaultManagerId),
      Accommodation(),
      Reportable() {
}

HostelManager::HostelManager(const std::string& newEntityId)
    : BaseEntity(newEntityId),
      Accommodation(newEntityId),
      Reportable(newEntityId) {
}

HostelManager::~HostelManager() = default;

bool HostelManager::addHostelBlock(const HostelBlock& hostelBlock) {
    if (searchBlock(hostelBlock.getBlockName()) != nullptr) {
        return false;
    }

    hostelBlocks.push_back(hostelBlock);
    return true;
}

bool HostelManager::removeHostelBlock(const std::string& blockName) {
    const HostelBlock* block = searchBlock(blockName);
    if (block == nullptr || block->getOccupiedRooms() != 0U) {
        return false;
    }

    hostelBlocks.erase(
        std::remove_if(
            hostelBlocks.begin(),
            hostelBlocks.end(),
            [&blockName](const HostelBlock& currentBlock) {
                return currentBlock.getBlockName() == blockName;
            }),
        hostelBlocks.end());
    return true;
}

HostelBlock* HostelManager::searchBlock(const std::string& blockName) {
    const auto block = std::find_if(
        hostelBlocks.begin(),
        hostelBlocks.end(),
        [&blockName](const HostelBlock& currentBlock) {
            return currentBlock.getBlockName() == blockName;
        });

    return block == hostelBlocks.end() ? nullptr : &(*block);
}

const HostelBlock* HostelManager::searchBlock(
    const std::string& blockName) const {
    const auto block = std::find_if(
        hostelBlocks.begin(),
        hostelBlocks.end(),
        [&blockName](const HostelBlock& currentBlock) {
            return currentBlock.getBlockName() == blockName;
        });

    return block == hostelBlocks.end() ? nullptr : &(*block);
}

bool HostelManager::allocateRoom(const std::string& blockName,
                                 const std::string& roomNumber,
                                 const std::string& studentRollNo) {
    if (studentRollNo.empty() || isStudentAssigned(studentRollNo)) {
        return false;
    }

    HostelBlock* block = searchBlock(blockName);
    if (block == nullptr) {
        return false;
    }

    Room* room = block->searchRoom(roomNumber);
    if (room == nullptr || room->isFull()) {
        return false;
    }

    return room->addOccupant(studentRollNo);
}

bool HostelManager::vacateRoom(const std::string& blockName,
                               const std::string& roomNumber,
                               const std::string& studentRollNo) {
    HostelBlock* block = searchBlock(blockName);
    if (block == nullptr) {
        return false;
    }

    Room* room = block->searchRoom(roomNumber);
    if (room == nullptr) {
        return false;
    }

    return room->removeOccupant(studentRollNo);
}

void HostelManager::generateReport() const {
    std::size_t totalRooms = 0U;
    std::size_t occupiedRooms = 0U;
    std::size_t totalCapacity = 0U;
    std::size_t totalOccupants = 0U;

    for (const HostelBlock& block : hostelBlocks) {
        totalRooms += block.getTotalRooms();
        occupiedRooms += block.getOccupiedRooms();

        for (const Room& room : block.getRooms()) {
            totalCapacity += static_cast<std::size_t>(room.getMaxCapacity());
            totalOccupants += room.getOccupancyCount();
        }
    }

    const std::size_t vacantRooms = totalRooms - occupiedRooms;
    const double occupancyPercentage = totalCapacity == 0U
        ? emptyOccupancyPercentage
        : (static_cast<double>(totalOccupants)
           / static_cast<double>(totalCapacity))
            * percentageMultiplier;

    constexpr int percentagePrecision = 2;
    std::ostringstream report;
    report << "Hostel Management Report\n"
           << "Manager Entity ID: " << getEntityId() << '\n'
           << "Total Blocks: " << hostelBlocks.size() << '\n'
           << "Total Rooms: " << totalRooms << '\n'
           << "Occupied Rooms: " << occupiedRooms << '\n'
           << "Vacant Rooms: " << vacantRooms << '\n'
           << "Total Occupants: " << totalOccupants << '\n'
           << "Total Bed Capacity: " << totalCapacity << '\n'
           << "Occupancy Percentage: " << std::fixed
           << std::setprecision(percentagePrecision)
           << occupancyPercentage << "%\n\n";
    std::cout << report.str();

    for (const HostelBlock& block : hostelBlocks) {
        block.displayAllRooms();
    }
}

void HostelManager::displayInfo() const {
    std::cout << "Hostel Manager Information\n"
              << "Entity ID: " << getEntityId() << '\n'
              << "Managed Blocks: " << hostelBlocks.size() << '\n';
}

std::size_t HostelManager::getTotalBlocks() const {
    return hostelBlocks.size();
}

const std::vector<HostelBlock>& HostelManager::getHostelBlocks() const {
    return hostelBlocks;
}

bool HostelManager::isStudentAssigned(
    const std::string& studentRollNo) const {
    return std::any_of(
        hostelBlocks.begin(),
        hostelBlocks.end(),
        [&studentRollNo](const HostelBlock& block) {
            return std::any_of(
                block.getRooms().begin(),
                block.getRooms().end(),
                [&studentRollNo](const Room& room) {
                    return room.hasOccupant(studentRollNo);
                });
        });
}

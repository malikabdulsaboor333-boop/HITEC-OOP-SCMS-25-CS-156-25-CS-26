/**
 * @file HostelBlock.h
 * @brief HostelBlock composition class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_HOSTEL_HOSTEL_BLOCK_H
#define SCMS_HOSTEL_HOSTEL_BLOCK_H

#include "Room.h"

#include <cstddef>
#include <string>
#include <vector>

class HostelBlock {
public:
    HostelBlock();
    explicit HostelBlock(const std::string& newBlockName);

    const std::string& getBlockName() const;
    const std::vector<Room>& getRooms() const;
    void setBlockName(const std::string& newBlockName);

    bool addRoom(const Room& room);
    bool removeRoom(const std::string& roomNumber);
    Room* searchRoom(const std::string& roomNumber);
    const Room* searchRoom(const std::string& roomNumber) const;
    void displayAllRooms() const;
    std::size_t getTotalRooms() const;
    std::size_t getOccupiedRooms() const;

private:
    static constexpr const char* defaultBlockName = "DEFAULT_BLOCK";

    std::string blockName;
    std::vector<Room> rooms;
};

#endif

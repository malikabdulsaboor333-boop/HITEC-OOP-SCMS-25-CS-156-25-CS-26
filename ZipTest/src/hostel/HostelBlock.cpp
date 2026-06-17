/**
 * @file HostelBlock.cpp
 * @brief HostelBlock composition class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "HostelBlock.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

HostelBlock::HostelBlock()
    : blockName(defaultBlockName) {
}

HostelBlock::HostelBlock(const std::string& newBlockName)
    : blockName(newBlockName) {
    if (blockName.empty()) {
        throw std::invalid_argument("Hostel block name cannot be empty.");
    }
}

const std::string& HostelBlock::getBlockName() const {
    return blockName;
}

const std::vector<Room>& HostelBlock::getRooms() const {
    return rooms;
}

void HostelBlock::setBlockName(const std::string& newBlockName) {
    if (newBlockName.empty()) {
        throw std::invalid_argument("Hostel block name cannot be empty.");
    }

    blockName = newBlockName;
}

bool HostelBlock::addRoom(const Room& room) {
    if (searchRoom(room.getRoomNumber()) != nullptr) {
        return false;
    }

    rooms.push_back(room);
    return true;
}

bool HostelBlock::removeRoom(const std::string& roomNumber) {
    const Room* room = searchRoom(roomNumber);
    if (room == nullptr || room->getOccupancyCount() != 0U) {
        return false;
    }

    rooms.erase(
        std::remove_if(
            rooms.begin(),
            rooms.end(),
            [&roomNumber](const Room& currentRoom) {
                return currentRoom.getRoomNumber() == roomNumber;
            }),
        rooms.end());
    return true;
}

Room* HostelBlock::searchRoom(const std::string& roomNumber) {
    const auto room = std::find_if(
        rooms.begin(),
        rooms.end(),
        [&roomNumber](const Room& currentRoom) {
            return currentRoom.getRoomNumber() == roomNumber;
        });

    return room == rooms.end() ? nullptr : &(*room);
}

const Room* HostelBlock::searchRoom(const std::string& roomNumber) const {
    const auto room = std::find_if(
        rooms.begin(),
        rooms.end(),
        [&roomNumber](const Room& currentRoom) {
            return currentRoom.getRoomNumber() == roomNumber;
        });

    return room == rooms.end() ? nullptr : &(*room);
}

void HostelBlock::displayAllRooms() const {
    if (rooms.empty()) {
        std::cout << "No rooms available in block " << blockName << ".\n";
        return;
    }

    std::cout << "Hostel Block: " << blockName << '\n';
    for (const Room& room : rooms) {
        room.displayRoomInfo();
        std::cout << '\n';
    }
}

std::size_t HostelBlock::getTotalRooms() const {
    return rooms.size();
}

std::size_t HostelBlock::getOccupiedRooms() const {
    return static_cast<std::size_t>(std::count_if(
        rooms.begin(),
        rooms.end(),
        [](const Room& room) {
            return room.getOccupancyCount() > 0U;
        }));
}

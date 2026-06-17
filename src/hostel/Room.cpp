/**
 * @file Room.cpp
 * @brief Room class implementation
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#include "Room.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

Room::Room()
    : Room(defaultRoomNumber,
           defaultRoomType,
           defaultFloorNumber,
           defaultMaxCapacity) {
}

Room::Room(const std::string& newRoomNumber,
           const std::string& newRoomType,
           int newFloorNumber,
           int newMaxCapacity)
    : roomNumber(newRoomNumber),
      roomType(newRoomType),
      floorNumber(newFloorNumber),
      maxCapacity(newMaxCapacity) {
    validateData();
}

const std::string& Room::getRoomNumber() const {
    return roomNumber;
}

const std::string& Room::getRoomType() const {
    return roomType;
}

int Room::getFloorNumber() const {
    return floorNumber;
}

int Room::getMaxCapacity() const {
    return maxCapacity;
}

const std::vector<std::string>& Room::getOccupants() const {
    return occupants;
}

void Room::setRoomNumber(const std::string& newRoomNumber) {
    if (newRoomNumber.empty()) {
        throw std::invalid_argument("Room number cannot be empty.");
    }

    roomNumber = newRoomNumber;
}

void Room::setRoomType(const std::string& newRoomType) {
    if (!isSupportedRoomType(newRoomType)) {
        throw std::invalid_argument(
            "Room type must be Single, Double, or Triple.");
    }

    const int newCapacity = capacityForRoomType(newRoomType);
    if (occupants.size() > static_cast<std::size_t>(newCapacity)) {
        throw std::invalid_argument(
            "Current occupancy exceeds the selected room type capacity.");
    }

    roomType = newRoomType;
    maxCapacity = newCapacity;
}

void Room::setFloorNumber(int newFloorNumber) {
    if (newFloorNumber <= minimumPositiveValue) {
        throw std::invalid_argument("Floor number must be positive.");
    }

    floorNumber = newFloorNumber;
}

void Room::setMaxCapacity(int newMaxCapacity) {
    if (newMaxCapacity <= minimumPositiveValue) {
        throw std::invalid_argument("Room capacity must be positive.");
    }

    if (static_cast<std::size_t>(newMaxCapacity) < occupants.size()) {
        throw std::invalid_argument(
            "Room capacity cannot be lower than current occupancy.");
    }

    if (newMaxCapacity != capacityForRoomType(roomType)) {
        throw std::invalid_argument(
            "Room capacity must match its Single, Double, or Triple type.");
    }

    maxCapacity = newMaxCapacity;
}

bool Room::addOccupant(const std::string& studentRollNo) {
    if (studentRollNo.empty() || isFull() || hasOccupant(studentRollNo)) {
        return false;
    }

    occupants.push_back(studentRollNo);
    return true;
}

bool Room::removeOccupant(const std::string& studentRollNo) {
    const auto occupant = std::find(
        occupants.begin(), occupants.end(), studentRollNo);
    if (occupant == occupants.end()) {
        return false;
    }

    occupants.erase(occupant);
    return true;
}

bool Room::hasOccupant(const std::string& studentRollNo) const {
    return std::find(occupants.begin(), occupants.end(), studentRollNo)
        != occupants.end();
}

bool Room::isFull() const {
    return occupants.size() >= static_cast<std::size_t>(maxCapacity);
}

std::size_t Room::getOccupancyCount() const {
    return occupants.size();
}

void Room::displayRoomInfo() const {
    std::cout << "Room Number: " << roomNumber << '\n'
              << "Room Type: " << roomType << '\n'
              << "Floor Number: " << floorNumber << '\n'
              << "Capacity: " << maxCapacity << '\n'
              << "Occupancy: " << occupants.size() << '\n'
              << "Occupants:";

    if (occupants.empty()) {
        std::cout << " None\n";
        return;
    }

    std::cout << '\n';
    for (const std::string& occupant : occupants) {
        std::cout << "- " << occupant << '\n';
    }
}

bool Room::isSupportedRoomType(const std::string& roomType) {
    return roomType == "Single"
        || roomType == "Double"
        || roomType == "Triple";
}

int Room::capacityForRoomType(const std::string& roomType) {
    if (roomType == "Single") {
        return singleRoomCapacity;
    }
    if (roomType == "Double") {
        return doubleRoomCapacity;
    }
    if (roomType == "Triple") {
        return tripleRoomCapacity;
    }
    return minimumPositiveValue;
}

void Room::validateData() const {
    if (roomNumber.empty()) {
        throw std::invalid_argument("Room number cannot be empty.");
    }

    if (!isSupportedRoomType(roomType)) {
        throw std::invalid_argument(
            "Room type must be Single, Double, or Triple.");
    }

    if (floorNumber <= minimumPositiveValue) {
        throw std::invalid_argument("Floor number must be positive.");
    }

    if (maxCapacity <= minimumPositiveValue) {
        throw std::invalid_argument("Room capacity must be positive.");
    }

    if (maxCapacity != capacityForRoomType(roomType)) {
        throw std::invalid_argument(
            "Room capacity must match its Single, Double, or Triple type.");
    }

    if (occupants.size() > static_cast<std::size_t>(maxCapacity)) {
        throw std::invalid_argument("Room occupants cannot exceed capacity.");
    }
}

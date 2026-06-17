/**
 * @file Room.h
 * @brief Room class declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_HOSTEL_ROOM_H
#define SCMS_HOSTEL_ROOM_H

#include <cstddef>
#include <string>
#include <vector>

class Room {
public:
    Room();
    Room(const std::string& newRoomNumber,
         const std::string& newRoomType,
         int newFloorNumber,
         int newMaxCapacity);

    const std::string& getRoomNumber() const;
    const std::string& getRoomType() const;
    int getFloorNumber() const;
    int getMaxCapacity() const;
    const std::vector<std::string>& getOccupants() const;

    void setRoomNumber(const std::string& newRoomNumber);
    void setRoomType(const std::string& newRoomType);
    void setFloorNumber(int newFloorNumber);
    void setMaxCapacity(int newMaxCapacity);

    bool addOccupant(const std::string& studentRollNo);
    bool removeOccupant(const std::string& studentRollNo);
    bool hasOccupant(const std::string& studentRollNo) const;
    bool isFull() const;
    std::size_t getOccupancyCount() const;
    void displayRoomInfo() const;

private:
    static bool isSupportedRoomType(const std::string& roomType);
    static int capacityForRoomType(const std::string& roomType);
    void validateData() const;

    static constexpr const char* defaultRoomNumber = "DEFAULT_ROOM";
    static constexpr const char* defaultRoomType = "Single";
    static constexpr int defaultFloorNumber = 1;
    static constexpr int defaultMaxCapacity = 1;
    static constexpr int minimumPositiveValue = 0;
    static constexpr int singleRoomCapacity = 1;
    static constexpr int doubleRoomCapacity = 2;
    static constexpr int tripleRoomCapacity = 3;

    std::string roomNumber;
    std::string roomType;
    int floorNumber;
    int maxCapacity;
    std::vector<std::string> occupants;
};

#endif

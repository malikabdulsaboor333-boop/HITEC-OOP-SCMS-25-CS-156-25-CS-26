/**
 * @file Persistence.h
 * @brief Campus-wide CSV persistence service declaration
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_UTILS_PERSISTENCE_H
#define SCMS_UTILS_PERSISTENCE_H

#include <memory>
#include <string>
#include <vector>

class Course;
class Enrollment;
class FinanceManager;
class HostelManager;
class LibraryManager;
class Person;

namespace SCMS {
namespace Persistence {

class CampusPersistence {
public:
    static bool ensureDataFiles();

    static bool savePersons(
        const std::vector<std::unique_ptr<Person>>& people,
        bool append = false);
    static std::vector<std::unique_ptr<Person>> loadPersons();

    static bool saveCourses(const std::vector<Course>& courses,
                            const std::vector<Enrollment>& enrollments,
                            bool append = false);
    static bool loadCourses(std::vector<Course>& courses,
                            std::vector<Enrollment>& enrollments);

    static bool saveLibrary(const LibraryManager& manager,
                            bool append = false);
    static bool loadLibrary(LibraryManager& manager);

    static bool saveHostel(const HostelManager& manager,
                           bool append = false);
    static bool loadHostel(HostelManager& manager);

    static bool saveFinanceSummary(const FinanceManager& manager,
                                   bool append = false);

    static bool saveToFile(
        const std::vector<std::unique_ptr<Person>>& people,
        bool append = false);
    static bool loadFromFile(
        std::vector<std::unique_ptr<Person>>& people);
    static bool saveToFile(const std::vector<Course>& courses,
                           const std::vector<Enrollment>& enrollments,
                           bool append = false);
    static bool loadFromFile(std::vector<Course>& courses,
                             std::vector<Enrollment>& enrollments);
    static bool saveToFile(const LibraryManager& manager,
                           bool append = false);
    static bool loadFromFile(LibraryManager& manager);
    static bool saveToFile(const HostelManager& manager,
                           bool append = false);
    static bool loadFromFile(HostelManager& manager);
    static bool saveToFile(const FinanceManager& manager,
                           bool append = false);
    static bool loadFromFile(FinanceManager& manager);

    static const std::string& dataDirectory();

private:
    CampusPersistence() = delete;
};

}  // namespace Persistence
}  // namespace SCMS

#endif

/**
 * @file Library.h
 * @brief Generic library class and title-search function templates
 * @author Abdul Saboor
 * @course CS-202 Object-Oriented Programming
 * @inst HITEC University Taxila
 */

#ifndef SCMS_LIBRARY_LIBRARY_H
#define SCMS_LIBRARY_LIBRARY_H

#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <vector>

template <typename T>
const T* searchByTitle(const std::vector<T>& items,
                       const std::string& title) {
    const auto item = std::find_if(
        items.begin(),
        items.end(),
        [&title](const T& currentItem) {
            return currentItem.getTitle() == title;
        });
    return item == items.end() ? nullptr : &(*item);
}

template <typename T>
class Library {
public:
    bool addItem(const T& item) {
        if (item.getItemId().empty()
            || itemIndex.find(item.getItemId()) != itemIndex.end()) {
            return false;
        }

        items.push_back(item);
        itemIndex[item.getItemId()] = items.size() - 1U;
        titles.insert(item.getTitle());
        return true;
    }

    bool removeItem(const std::string& itemId) {
        const auto indexedItem = itemIndex.find(itemId);
        if (indexedItem == itemIndex.end()) {
            return false;
        }

        items.erase(
            items.begin()
            + static_cast<typename std::vector<T>::difference_type>(
                indexedItem->second));
        rebuildIndexes();
        return true;
    }

    const T* findById(const std::string& itemId) const {
        const auto indexedItem = itemIndex.find(itemId);
        return indexedItem == itemIndex.end()
            ? nullptr
            : &items[indexedItem->second];
    }

    const T* findByTitle(const std::string& title) const {
        return searchByTitle(items, title);
    }

    const std::vector<T>& getItems() const {
        return items;
    }

    const std::set<std::string>& getTitles() const {
        return titles;
    }

    std::size_t size() const {
        return items.size();
    }

private:
    void rebuildIndexes() {
        itemIndex.clear();
        titles.clear();
        for (std::size_t index = 0U; index < items.size(); ++index) {
            itemIndex[items[index].getItemId()] = index;
            titles.insert(items[index].getTitle());
        }
    }

    std::vector<T> items;
    std::map<std::string, std::size_t> itemIndex;
    std::set<std::string> titles;
};

#endif

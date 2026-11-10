#pragma once
#include "Item.hpp"
#include <vector>
#include <string>

class Tracker {
private:
    std::vector<Item> items;
    std::string filename;
    int nextId;

    void load();
    void save();

public:
    explicit Tracker(const std::string& storageFile);

    void addItem(ItemType type, const std::string& title, const std::string& category, double amount, const std::string& date);
    void listItems(bool filterByType = false, ItemType type = ItemType::TASK) const;
    bool markComplete(int id);
    bool deleteItem(int id);
    void displayExpenseSummary() const;
};
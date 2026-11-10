#pragma once
#include <string>

enum class ItemType { TASK, EXPENSE };

struct Item {
    int id;
    ItemType type;
    std::string title;
    std::string category;
    double amount;      // 0.0 for tasks; currency value for expenses
    bool isCompleted;   // true if task is done or expense is cleared
    std::string date;   // YYYY-MM-DD

    std::string toCSV() const;
    static Item fromCSV(const std::string& line);
};

std::string itemTypeToString(ItemType type);
ItemType stringToItemType(const std::string& str);
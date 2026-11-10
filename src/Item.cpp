#include "Item.hpp"
#include <sstream>
#include <stdexcept>
#include <iomanip>
using namespace std;

string itemTypeToString(ItemType type) {
    return (type == ItemType::TASK) ? "TASK" : "EXPENSE";
}

ItemType stringToItemType(const string& str) {
    if (str == "TASK") return ItemType::TASK;
    if (str == "EXPENSE") return ItemType::EXPENSE;
    throw invalid_argument("Unknown ItemType: " + str);
}

string Item::toCSV() const {
    ostringstream ss;
    ss << id << ","
       << itemTypeToString(type) << ","
       << title << ","
       << category << ","
       << fixed << setprecision(2) << amount << ","
       << (isCompleted ? "1" : "0") << ","
       << date;
    return ss.str();
}

Item Item::fromCSV(const string& line) {
    stringstream ss(line);
    string token;
    Item item;

    if (!getline(ss, token, ',')) throw runtime_error("Malformed CSV: missing ID");
    item.id = stoi(token);

    if (!getline(ss, token, ',')) throw runtime_error("Malformed CSV: missing Type");
    item.type = stringToItemType(token);

    if (!getline(ss, item.title, ',')) throw runtime_error("Malformed CSV: missing Title");
    if (!getline(ss, item.category, ',')) throw runtime_error("Malformed CSV: missing Category");

    if (!getline(ss, token, ',')) throw runtime_error("Malformed CSV: missing Amount");
    item.amount = stod(token);

    if (!getline(ss, token, ',')) throw runtime_error("Malformed CSV: missing Status");
    item.isCompleted = (token == "1");

    if (!getline(ss, item.date, ',')) throw runtime_error("Malformed CSV: missing Date");

    return item;
}
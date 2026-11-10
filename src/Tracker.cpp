#include "Tracker.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;

Tracker::Tracker(const string& storageFile) : filename(storageFile), nextId(1) {
    load();
}

void Tracker::load() {
    items.clear();
    ifstream file(filename);
    if (!file.is_open()) return; // File does not exist yet; will be created on first save

    string line;
    bool isHeader = true;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (isHeader) {
            isHeader = false;
            continue; // Skip CSV header row
        }
        try {
            Item item = Item::fromCSV(line);
            items.push_back(item);
            if (item.id >= nextId) {
                nextId = item.id + 1;
            }
        } catch (const exception& e) {
            cerr << "Warning: Skipped corrupted line: " << e.what() << "\n";
        }
    }
}

void Tracker::save() {
    string tempFile = filename + ".tmp";
    ofstream out(tempFile);
    if (!out.is_open()) {
        cerr << "Error: Could not write to " << tempFile << "\n";
        return;
    }

    out << "id,type,title,category,amount,isCompleted,date\n";
    for (const auto& item : items) {
        out << item.toCSV() << "\n";
    }
    out.close();

    // Atomic replacement
    remove(filename.c_str());
    rename(tempFile.c_str(), filename.c_str());
}

void Tracker::addItem(ItemType type, const string& title, const string& category, double amount, const string& date) {
    Item item{nextId++, type, title, category, amount, false, date};
    items.push_back(item);
    save();
    cout << "Successfully added (ID: " << item.id << ")\n";
}

void Tracker::listItems(bool filterByType, ItemType type) const {
    cout << "\n" << left
              << setw(6)  << "ID"
              << setw(10) << "Type"
              << setw(25) << "Title"
              << setw(15) << "Category"
              << setw(10) << "Amount"
              << setw(10) << "Status"
              << setw(12) << "Date" << "\n";
    cout << string(88, '-') << "\n";

    for (const auto& item : items) {
        if (filterByType && item.type != type) continue;

        cout << left
                  << setw(6)  << item.id
                  << setw(10) << itemTypeToString(item.type)
                  << setw(25) << item.title.substr(0, 23)
                  << setw(15) << item.category
                  << setw(10) << fixed << setprecision(2) << item.amount
                  << setw(10) << (item.isCompleted ? "[Done]" : "[Pending]")
                  << setw(12) << item.date << "\n";
    }
}

bool Tracker::markComplete(int id) {
    auto it = find_if(items.begin(), items.end(), [id](const Item& i) { return i.id == id; });
    if (it != items.end()) {
        it->isCompleted = true;
        save();
        return true;
    }
    return false;
}

bool Tracker::deleteItem(int id) {
    auto it = remove_if(items.begin(), items.end(), [id](const Item& i) { return i.id == id; });
    if (it != items.end()) {
        items.erase(it, items.end());
        save();
        return true;
    }
    return false;
}

void Tracker::displayExpenseSummary() const {
    double total = 0.0;
    map<string, double> categoryTotals;

    for (const auto& item : items) {
        if (item.type == ItemType::EXPENSE) {
            total += item.amount;
            categoryTotals[item.category] += item.amount;
        }
    }

    cout << "\n=== Expense Summary ===\n";
    cout << "Total Expenses: $" << fixed << setprecision(2) << total << "\n";
    cout << "\nBreakdown by Category:\n";
    for (const auto& [cat, sum] : categoryTotals) {
        cout << " - " << left << setw(15) << cat << ": $" << sum << "\n";
    }
}
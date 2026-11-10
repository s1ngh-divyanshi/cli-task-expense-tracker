#include "Tracker.hpp"
#include <iostream>
#include <limits>
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    cout << "\n================================\n"
         << "  CLI Task & Expense Tracker\n"
              << "================================\n"
              << "1. Add Task\n"
              << "2. Add Expense\n"
              << "3. List All Items\n"
              << "4. List Tasks Only\n"
              << "5. List Expenses Only\n"
              << "6. Mark Task as Completed\n"
              << "7. Delete Item\n"
              << "8. View Expense Summary\n"
              << "9. Exit\n"
              << "Select an option [1-9]: ";
}

int main() {
    Tracker tracker("tracker_data.csv");
    int choice = 0;

    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 9) {
            cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: { // Add Task
                string title, category, date;
                cout << "Enter task title: ";
                getline(cin, title);
                cout << "Enter category (e.g., Work, Study, Health): ";
                getline(cin, category);
                cout << "Enter due date (YYYY-MM-DD): ";
                getline(cin, date);
                tracker.addItem(ItemType::TASK, title, category, 0.0, date);
                break;
            }
            case 2: { // Add Expense
                string title, category, date;
                double amount = 0.0;
                cout << "Enter expense description: ";
                getline(cin, title);
                cout << "Enter category (e.g., Food, Travel, Rent): ";
                getline(cin, category);
                cout << "Enter amount: $";
                while (!(cin >> amount) || amount < 0) {
                    cout << "Invalid amount. Enter a positive number: $";
                    clearInputBuffer();
                }
                clearInputBuffer();
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                tracker.addItem(ItemType::EXPENSE, title, category, amount, date);
                break;
            }
            case 3:
                tracker.listItems(false);
                break;
            case 4:
                tracker.listItems(true, ItemType::TASK);
                break;
            case 5:
                tracker.listItems(true, ItemType::EXPENSE);
                break;
            case 6: {
                int id;
                cout << "Enter Task ID to complete: ";
                if (cin >> id) {
                    if (tracker.markComplete(id)) cout << "Task marked as complete.\n";
                    else cout << "Task ID not found.\n";
                }
                clearInputBuffer();
                break;
            }
            case 7: {
                int id;
                cout << "Enter Item ID to delete: ";
                if (cin >> id) {
                    if (tracker.deleteItem(id)) cout << "Item deleted.\n";
                    else cout << "Item ID not found.\n";
                }
                clearInputBuffer();
                break;
            }
            case 8:
                tracker.displayExpenseSummary();
                break;
            default:
                cout << "Choice must be between 1 and 9.\n";
                break;
        }
    }
    return 0;
}
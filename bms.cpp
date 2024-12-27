#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // for std::setw
#include <algorithm>

using namespace std;

// Structure for bakery items
struct BakeryItem {
    int id;
    string name;
    double price;
};

// Function to display available items
void displayMenu(const vector<BakeryItem>& items) {
    cout << "\n--- Bakery Menu ---\n";
    cout << setw(5) << "ID" << setw(20) << "Item" << setw(10) << "Price\n";
    cout << "-------------------------------\n";
    for (const auto& item : items) {
        cout << setw(5) << item.id
             << setw(20) << item.name
             << setw(10) << fixed << setprecision(2) << item.price << "\n";
    }
    cout << endl;
}

// Function to take an order
void takeOrder(const vector<BakeryItem>& items) {
    vector<pair<string, int>> cart; // Stores item name and quantity
    int itemId, quantity;
    char more;

    do {
        cout << "Enter the ID of the item you want to order: ";
        cin >> itemId;

        // Find item by ID
        auto it = find_if(items.begin(), items.end(),
                          [itemId](const BakeryItem& item) { return item.id == itemId; });

        if (it != items.end()) {
            cout << "Enter quantity for " << it->name << ": ";
            cin >> quantity;
            cart.emplace_back(it->name, quantity);
        } else {
            cout << "Invalid item ID. Try again.\n";
        }

        cout << "Do you want to order more items? (y/n): ";
        cin >> more;
    } while (more == 'y' || more == 'Y');

    // Display the bill
    double total = 0;
    cout << "\n--- Your Order ---\n";
    for (const auto& order : cart) {
        auto it = find_if(items.begin(), items.end(),
                          [order](const BakeryItem& item) { return item.name == order.first; });
        double cost = it->price * order.second;
        total += cost;
        cout << setw(20) << order.first
             << setw(10) << order.second
             << setw(10) << cost << "\n";
    }
    cout << "-------------------------------\n";
    cout << setw(30) << "Total: " << total << "\n";
}

int main() {
    // Bakery menu
    vector<BakeryItem> items = {
        {1, "Chocolate Cake", 15.50},
        {2, "Croissant", 2.75},
        {3, "Cupcake", 3.50},
        {4, "Bread Loaf", 4.00},
        {5, "Doughnut", 1.25}
    };

    int choice;

    while (true) {
        cout << "\n--- Bakery Management System ---\n";
        cout << "1. Display Menu\n";
        cout << "2. Take Order\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayMenu(items);
            break;
        case 2:
            takeOrder(items);
            break;
        case 3:
            cout << "Thank you for using the Bakery Management System!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}



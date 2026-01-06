#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Item {
public:
    string name;
    string category;
    double price;
    int stock;

    Item(string n, string c, double p, int s) : name(n), category(c), price(p), stock(s) {}
};

class VendingMachine {
private:
    vector<Item> items;

public:
    VendingMachine() {
        items.push_back(Item("Coke", "Cold Drinks", 1.50, 5));
        items.push_back(Item("Water", "Cold Drinks", 1.00, 5));
        items.push_back(Item("Coffee", "Hot Drinks", 2.00, 5));
        items.push_back(Item("Tea", "Hot Drinks", 1.80, 5));
        items.push_back(Item("Chocolate Bar", "Snacks", 1.20, 5));
        items.push_back(Item("Crisps", "Snacks", 1.10, 5));
        items.push_back(Item("Biscuits", "Snacks", 1.40, 5));
    }

    void showMenu() {
        cout << "\n===== VENDING MACHINE MENU =====\n";
        string currentCategory = "";
        for (int i = 0; i < items.size(); i++) {
            if (items[i].category != currentCategory) {
                currentCategory = items[i].category;
                cout << "\n-- " << currentCategory << " --\n";
            }
            cout << i + 1 << ". " << items[i].name << " (GBP" << items[i].price << ")  Stock: " << items[i].stock << "\n";
        }
        cout << "\nSelect an item number or 0 to finish: ";
    }

    bool validChoice(int choice) {
        return choice > 0 && choice <= items.size();
    }

    bool inStock(int choice) {
        return items[choice - 1].stock > 0;
    }

    void dispense(int choice) {
        items[choice - 1].stock--;
        cout << "\nDispensing: " << items[choice - 1].name << "\n";
    }

    double getPrice(int choice) {
        return items[choice - 1].price;
    }

    string getSuggestion(int choice) {
        string c = items[choice - 1].category;
        if (c == "Hot Drinks") return "Suggested item: Biscuits (GBP 1.40)";
        if (c == "Cold Drinks") return "Suggested item: Crisps (GBP 1.10)";
        if (c == "Snacks") return "Suggested item: Water (GBP 1.00)";
        return "";
    }
};

int main() {
    VendingMachine vm;
    double money;
    cout << "Enter money inserted (GBP): ";
    cin >> money;

    bool shopping = true;
    while (shopping) {
        vm.showMenu();
        int choice;
        cin >> choice;

        if (choice == 0) {
            shopping = false;
            break;
        }

        if (!vm.validChoice(choice)) {
            cout << "Invalid selection.\n";
            continue;
        }

        if (!vm.inStock(choice)) {
            cout << "Item out of stock.\n";
            continue;
        }

        double price = vm.getPrice(choice);

        if (money < price) {
            cout << "Not enough money.\n";
            continue;
        }

        vm.dispense(choice);
        money -= price;

        cout << "Remaining balance: GBP" << money << "\n";
        cout << vm.getSuggestion(choice) << "\n";

        char more;
        cout << "Buy another item? (y/n): ";
        cin >> more;
        if (more == 'n' || more == 'N') shopping = false;
    }

    cout << "\nChange returned: GBP" << money << "\n";
    cout << "Thank you for using the vending machine.\n";
    return 0;
}

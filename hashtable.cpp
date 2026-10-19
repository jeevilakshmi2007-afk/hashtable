#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class HashTable {
private:
    int size;
    vector<int> table;
    vector<bool> occupied;

    int hashIndex(int x) const {
        return ((x % size) + size) % size;   // also safe for negative numbers
    }

public:
    HashTable(int s) : size(s), table(s, 0), occupied(s, false) {}

    // INSERT x (linear probing: (index + 1) % size)
    void insertKey(int x) {
        int index = hashIndex(x);
        for (int i = 0; i < size; i++) {
            if (occupied[index] && table[index] == x) {
                cout << "Account " << x << " already exists at index "
                     << index << ".\n";
                return;
            }
            if (!occupied[index]) {
                table[index] = x;
                occupied[index] = true;
                cout << "Account " << x << " inserted at index "
                     << index << ".\n";
                return;
            }
            index = (index + 1) % size;
        }
        cout << "Hash table is FULL. Cannot insert " << x << ".\n";
    }

    // SEARCH x
    void searchKey(int x) const {
        int index = hashIndex(x);
        for (int i = 0; i < size; i++) {
            if (!occupied[index]) break;          // empty slot: not present
            if (table[index] == x) {
                cout << "Account " << x << " FOUND at index "
                     << index << ".\n";
                return;
            }
            index = (index + 1) % size;
        }
        cout << "Account " << x << " NOT found.\n";
    }

    // DISPLAY
    void display() const {
        cout << "\nIndex : Account Number\n";
        for (int i = 0; i < size; i++) {
            cout << "  " << i << "   : ";
            if (occupied[i]) cout << table[i];
            else cout << "-";
            cout << "\n";
        }
    }
};

int main() {
    int size;
    cout << "Enter table size: ";
    if (!(cin >> size) || size <= 0) {
        cout << "Invalid table size.\n";
        return 1;
    }

    HashTable ht(size);
    int choice = 0, x;

    do {
        cout << "\n===== BANK HASH TABLE MENU =====\n";
        cout << "1. INSERT x\n";
        cout << "2. SEARCH x\n";
        cout << "3. DISPLAY\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number between 1 and 4.\n";
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
            case 2:
                cout << "Enter account number: ";
                if (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid account number.\n";
                    break;
                }
                if (choice == 1) ht.insertKey(x);
                else ht.searchKey(x);
                break;
            case 3:
                ht.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Enter 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}

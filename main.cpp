#include <iostream>
#include <windows.h> // To use SetConsoleTextAttribute function
#include <cstdlib> // To use rand function
#include <unistd.h> // To use sleep function
#include <iomanip> // To use setw function
using namespace std;

struct Item {
    int id;
    string name;
    int price;
};

class LinkedList {
private:
    struct Node {
        Item data;
        Node* next;
    };

    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addItem(const Item& newItem) {
        Node* newNode = new Node;
        newNode->data = newItem;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        cout << "\n\n\t\t\t\tItem added successfully ";
        for (int i = 0; i < 1; i++) {
                cout << "=>";
                sleep(1);
        }
    }

    void removeItem(const int& id) {
        if (head == nullptr) {
            cout << "\t\t\t\tItem not found!\n";
            for (int i = 0; i < 1; i++) {
                cout << "=>";
                sleep(1);
            }

            return;
        }

        if (head->data.id == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "\t\t\t\tItem removed successfully!\n";
            for (int i = 0; i < 1; i++) {
                cout << "=>";
                sleep(1);
            }

            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data.id == id) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                cout << "\t\tItem removed successfully!\n";
                return;
            }
            current = current->next;
        }

        cout << "\t\tItem not found!\n";
    }

    void generateInvoice() const {
        int totalAmount = 0.0;

        cout << "\t\tInvoice:\n";
        cout << "\t\t-------------------------\n";

        Node* current = head;
        while (current != nullptr) {
            cout << current->data.name << ": $" << current->data.price << "\n";
            totalAmount += current->data.price;
            current = current->next;
        }

        cout << "\t\t-------------------------\n";
        cout << "\t\tTotal amount: $" << totalAmount << "\n";
    }
    bool displayAllItems() {
        Node* current = head;
        if (current == nullptr) {
            return false;
        }
        cout << "\n\n\n\n";
        cout << "\t\t\t\t| ID   | Name           | Price      |\n";
        cout << "\t\t\t\t-------------------------------------\n";
        while (current != nullptr) {
            cout << "\t\t\t\t| " << setw(4) << left << current->data.id << " | "
                << setw(14) << left << current->data.name << " | "
                << "RS: " << setw(6) << fixed << current->data.price << " |\n";
            current = current->next;
        }
        return true;
    }



};


void displayMenu() {
    cout << "\n\n";
    cout << "\t\t\t\t******************************************\n";
    cout << "\t\t\t\t*        Billing Management System       *\n";
    cout << "\t\t\t\t******************************************\n";
    cout << "\t\t\t\t* 1. Add item                            *\n";
    cout << "\t\t\t\t* 2. Remove item                         *\n";
    cout << "\t\t\t\t* 3. Display items                       *\n";
    cout << "\t\t\t\t* 4. Generate invoice                    *\n";
    cout << "\t\t\t\t*                                        *\n";
    cout << "\t\t\t\t* 0. Exit                                *\n";
    cout << "\t\t\t\t*                                        *\n";
    cout << "\t\t\t\t******************************************\n";
}

int main() {
    fflush(stdout);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    LinkedList bill;
    int choice;
    do {
        system("cls");
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
        displayMenu();
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                cout << "\n\n";

                cout << "\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN  );
                system("cls");
                Item newItem;
                newItem.id = rand() % 10000 + 1000;
                cout << "\n\n\n\n";
                cout << "\t\t\t\tEnter item name: ";
                cin >> newItem.name;

                cout << "\t\t\t\tEnter item price: ";
                cin >> newItem.price;
                cout << "\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                bill.addItem(newItem);
                break;
            }
            case 2: {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE );
                if(!bill.displayAllItems()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\n\n\t\t\t\t\tEnter (Y) to Get back: ";
                    char btn;
                    cin >> btn;
                    if (btn == 'y' || btn == 'Y') {}
                    break;
                }
                int id;
                cout << "Enter item ID to remove: ";
                cin >> id;
                bill.removeItem(id);
                system("cls");
                cout << "\n\n\n\n";
                cout << "\t\t\t\tThe updated list is: \n\n\n\n";
                if(!bill.displayAllItems()) {
                    cout << "\n\n\t\t\t\tOops! - No more Items are left list\n\n";
                    cout << "\n\n\t\t\t\t\tEnter (Y) to Get back: ";
                    char btn;
                    cin >> btn;
                    if (btn == 'y' || btn == 'Y') {}
                    break;
                }
                break;
            }

            case 3: 
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN  );
                if (!bill.displayAllItems()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\t\t\t\t\tEnter (Y) to Get back: ";
                    char btn;
                    cin >> btn;
                    if (btn == 'y' || btn == 'Y') {}
                    break;
                }
                cout << "\n\n\t\t\t\t\tEnter (Y) to Get back: ";
                char btn;
                cin >> btn;
                if (btn == 'y' || btn == 'Y') {}
                break;
            case 4:
                bill.generateInvoice();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
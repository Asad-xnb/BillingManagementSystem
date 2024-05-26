#include <iostream>
#include <windows.h> // To use SetConsoleTextAttribute function
#include <cstdlib> // To use rand function
#include <unistd.h> // To use sleep function
#include <iomanip> // To use setw function
#include <ctime> // To use time function
using namespace std;

struct Item {
    string id;
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

    void removeItem(const string& id) {
        if (id == "n" || id == "N") {
            return;
        }
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
        srand(time(0));
        long long invoiceID = rand() % 9000000000 + 1000000000;
        int totalAmount = 0;

        cout << "\n\n\t\t\t\tInvoice ID: " <<  invoiceID << endl;
        cout << "\t\t\t\t-------------------------------------\n";
        cout << "\t\t\t\t| Name           | Price            |\n";
        cout << "\t\t\t\t-------------------------------------\n";
        cout << "\t\t\t\t|                                   |\n";
        cout << "\t\t\t\t|                                   |\n";

        Node* current = head;
         while (current != nullptr) {
            cout << "\t\t\t\t| " << setw(15) << left << current->data.name << "  RS: " << setw(12) << fixed << current->data.price << " |\n";
            totalAmount += current->data.price;
            current = current->next;
        }
        cout << "\t\t\t\t|                                   |\n";
        cout << "\t\t\t\t|                                   |\n";
        cout << "\t\t\t\t-------------------------------------\n";
        cout << "\t\t\t\tTotal amount:              RS: " << setw(10) << fixed << totalAmount << " \n";
        cout << "\t\t\t\t-------------------------------------\n";
    }

    bool itemsAvailable() {
        return head != nullptr;
    }

    bool displayAllItems() {
        Node* current = head;
        if (current == nullptr) {
            return false;
        } else {
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
    }



};


void displayMenu() {
    cout << "\n\n";
    cout << "\t\t\t\t******************************************\n";
    cout << "\t\t\t\t*        Billing Management System       *\n";
    cout << "\t\t\t\t******************************************\n";
    cout << "\t\t\t\t* 1. Add item                            *\n";
    cout << "\t\t\t\t* 2. Remove item                         *\n";
    cout << "\t\t\t\t* 3. Update item                         *\n";
    cout << "\t\t\t\t* 4. Display items                       *\n";
    cout << "\t\t\t\t* 5. Generate invoice                    *\n";
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
                newItem.id = to_string(rand() % 10000 + 1000);
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
                system("cls");
                if(!bill.itemsAvailable()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                } else {
                    cout << "\n\n\n\n";
                    cout << "\t\t\t\tThe current list:\n";
                    bill.displayAllItems();
                    string id;
                    cout << "\n\n\t\t\tEnter item ID to remove or (n) to go back: ";
                    cin >> id;
                    bill.removeItem(id); 
                    system("cls");
                    cout << "\n\n\n\n";
                    cout << "\t\t\t\tThe updated list: \n\n\n\n";
                    if(!bill.itemsAvailable()) {
                        cout << "\n\n\t\t\t\tOops! - No more Items are left list\n\n";
                    } else {
                        bill.displayAllItems();
                    }
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                }
            }

            case 3: 
                system("cls");
                cout << "\n\n\n\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN  );
                if(!bill.itemsAvailable()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                } else {
                    cout << "\n\n\n\n";
                    cout << "\t\t\t\tThe current list:\n";
                    bill.displayAllItems();
                    string id;
                    cout << "\n\n\t\t\tEnter item ID to update or (n) to go back: ";
                    cin >> id;
                    bill.removeItem(id);
                    Item newItem;
                    newItem.id = id;
                    cout << "\n\n\t\t\t\tEnter new item name: ";
                    cin >> newItem.name;

                    cout << "\t\t\t\tEnter new item price: ";
                    cin >> newItem.price;
                    cout << "\t\t\t\t\tLoading";
                    for (int i = 0; i < 2; i++) {
                        cout << ".";
                        sleep(1);
                    }
                    bill.addItem(newItem);
                    break;
                }
            case 4: 
                system("cls");
                cout << "\n\n\n\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE  );
                if (!bill.itemsAvailable()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                } else {
                    cout << "\n\n\n\n";
                    bill.displayAllItems();
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                }
                    
            case 5:
                system("cls");
                cout << "\n\n\n\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN  );
                if(!bill.itemsAvailable()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                } else {
                    bill.generateInvoice();
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                }
            case 0:
                cout << "\n\n\n\n\t\t\tExiting...\n";
                break;
            default:
                cout << "\n\n\n\n\t\t\tInvalid choice! Please try again.\n";
                cout << "\n\n\t\t\tPress Enter to continue... ";
                cin.ignore();
                cin.get();
                break;
        }
    } while (choice != 0);

    return 0;
}
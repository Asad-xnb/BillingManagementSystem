#include <iostream>
#include <windows.h> // To use SetConsoleTextAttribute function
#include <cstdlib> // To use rand function
#include <unistd.h> // To use sleep function
#include <iomanip> // To use setw function
#include <ctime> // To use time function
#include <fstream> // To use file handling
#include <sstream> // To use stringstream

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
    void updateItem(const string& id, const string& newName, const int& newPrice) {
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

        Node* current = head;
        do {
            if (current->data.id == id) {
                current->data.name = newName;
                current->data.price = newPrice;
                cout << "\t\t\t\tItem updated successfully ";
                for (int i = 0; i < 1; i++) {
                    cout << "=>";
                    sleep(1);
                }
                return;
            }
            current = current->next;
        } while (current != nullptr);

        cout << "\t\tItem not found!\n";
    }
    void clearAllItems() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void generateInvoice() {
        system("cls");
        srand(time(0));
        long long invoiceID = rand() % 9000000000 + 1000000000;
        int totalAmount = 0;

        cout << "\n\n\t\t\t\tInvoice ID: " <<  invoiceID << endl;
        cout << "\t\t\t\t-------------------------------------\n";
        cout << "\t\t\t\t| Name           | Price            |\n";
        cout << "\t\t\t\t-------------------------------------\n";
        cout << "\t\t\t\t|                                   |\n";

        Node* current = head;
         while (current != nullptr) {
            cout << "\t\t\t\t| " << setw(15) << left << current->data.name << "  RS: " << setw(12) << fixed << current->data.price << " |\n";
            totalAmount += current->data.price;
            current = current->next;
        }
        cout << "\t\t\t\t|                                   |\n";
        cout << "\t\t\t\t-------------------------------------\n";
        cout << "\t\t\t\tTotal amount:              RS: " << setw(10) << fixed << totalAmount << " \n";
        cout << "\t\t\t\t-------------------------------------\n";

        string filename = "Invoice_database/" + to_string(invoiceID) + ".txt";
        ofstream file(filename);

        if (file.is_open()) {
            file << "Invoice ID: " << invoiceID << endl;
            file << "-------------------------------------\n";
            file << "| Name           | Price            |\n";
            file << "-------------------------------------\n";
            file << "|                                   |\n";
            Node* current = head;
            while (current != nullptr) {
                file << "| " << setw(15) << left << current->data.name << "  RS: " << setw(12) << fixed << current->data.price << " |\n";
                current = current->next;
            }
            file << "|                                   |\n";
            file << "-------------------------------------\n";
            file << "Total amount:              RS: " << setw(10) << fixed << totalAmount << " \n";
            file << "-------------------------------------\n";
            file.close();
        }

        clearAllItems();
        cout << "\n\n\t\t\t\tPress Enter to continue... ";
        cin.get();
    }

    void checkout() {
        cout << "\n\n\n\n";
        cout << "\t\t\t\t******************************************\n";
        cout << "\t\t\t\t*          Enter Credit Card Details     *\n";
        cout << "\t\t\t\t******************************************\n";

        string cardNumber, date, cvc;

        cout << "\t\t\t\t| Enter card number: ";
        cin >> cardNumber;
        cout << "\t\t\t\t------------------------------------------\n";

        cout << "\t\t\t\t| Expiry date (mm/yy): ";
        cin >> date;
        cout << "\t\t\t\t------------------------------------------\n";

        cout << "\t\t\t\t| Enter CVC: ";
        cin >> cvc;
        cout << "\t\t\t\t------------------------------------------\n";

        cout << "\n\n\t\t\t\tProcessing payment";
        for (int i = 0; i < 3; ++i) {
            cout << ".";
            sleep(1);
        }
        cout << "\n";

        if (validateCardDetails(cardNumber, cvc)) {
            cout << "\n\n\t\t\t\tPayment successful!\n";
            cout << "\t\t\t\tThank you for shopping with us!\n";
            cout << "\t\t\t\tPress Enter to Generate Invoice... ";
            cin.ignore();
            cin.get();
            generateInvoice();
        } else {
            char again;
            cout << "\n\n\t\t\t\tPayment failed: Invalid card details!\n";
            cout << "\t\t\t\tWould you like to try again? (y/n): ";
            cin >> again;
            if (again == 'y' || again == 'Y') {
                system("cls");
                checkout();
            } else {
                cout << "\n\n\t\t\t\tThank you for shopping with us!\n";
                cout << "\t\t\t\tPress Enter to continue... ";
                cin.ignore();
                cin.get();
                return;
            }
        }
    }

    string customHash(const string& str) {
        long hash = 0;
        for (char c : str) {
            hash += c;
        }

        hash = (hash * 31) % 100000;

        stringstream ss;
        ss << hash;
        return ss.str();
    }

    bool validateCardDetails(const string& cardNumber, const string& cvc) {
        string hashedCardNumber = customHash(cardNumber);
        string hashedCvc = customHash(cvc);

        ifstream file("CreditCard_Database.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t separator = line.find(' ');
                if (separator != string::npos) {
                    string storedHashedCardNumber = line.substr(0, separator);
                    string storedHashedCvc = line.substr(separator + 1);
                    if (storedHashedCardNumber == hashedCardNumber && storedHashedCvc == hashedCvc) {
                        return true;
                    }
                }
            }
            file.close();
        }
        return false;
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
    bool searchItem(const string& id) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.id == id) {
                return true;
            }
            current = current->next;
        }
        return false;
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
    cout << "\t\t\t\t* 5. Checkout                            *\n";
    cout << "\t\t\t\t*                                        *\n";
    cout << "\t\t\t\t* 6. Clear The Bill                      *\n";
    cout << "\t\t\t\t* 0. Exit                                *\n";
    cout << "\t\t\t\t*                                        *\n";
    cout << "\t\t\t\t******************************************\n";
}

int main() {
    fflush(stdin);
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

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                system("cls");

                Item newItem;

                newItem.id = to_string(rand() % 10000 + 1000);

                cout << "\n\n";
                cout << "\t\t\t\t******************************\n";
                cout << "\t\t\t\t*        Add New Item        *\n";
                cout << "\t\t\t\t******************************\n\n";

                cout << "\t\t\t\tEnter item name: ";
                cin.ignore();
                getline(cin, newItem.name);

                cout << "\t\t\t\tEnter item price: ";
                cin >> newItem.price;

                cout << "\n\n";
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
            case 3: {
                system("cls");
                cout << "\n\n\n\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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
                    if (id == "n" || id == "N") {
                        break;
                    } else {
                        if (!bill.searchItem(id)){
                            cout << "\t\t\t\tItem not found!\n";
                            cout << "\n\n\t\t\tPress Enter to continue... ";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        string newName;
                        int newPrice;
                        cout << "\t\t\t\tUpdate name: ";
                        cin.ignore();
                        getline(cin, newName);
                        cout << "\t\t\t\tUpdate price: ";
                        cin >> newPrice;
                        bill.updateItem(id, newName, newPrice);
                        cout << "\n\n\t\t\tPress Enter to continue... ";
                        cin.ignore();
                        cin.get();
                        break;
                    }

                }
            }
            case 4: {
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
            }
            case 5: {
                system("cls");
                cout << "\n\n\n\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN  );
                if(!bill.itemsAvailable()) {
                    cout << "\n\n\t\t\t\tNo items found!\n\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                } else {
                    bill.checkout();
                    break;
                }
            }
            case 6: {
                system("cls");
                cout << "\n\n\n\t\t\t\t\tLoading";
                for (int i = 0; i < 2; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                if(!bill.itemsAvailable()) {
                    cout << "\n\n\t\t\t\tNo Bill found!\n\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                } else {
                    cout << "\n\n\n\n";
                    bill.clearAllItems();
                    cout << "\n\n\t\t\t\tBill cleared successfully!\n";
                    cout << "\n\n\t\t\tPress Enter to continue... ";
                    cin.ignore();
                    cin.get();
                    break;
                }
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


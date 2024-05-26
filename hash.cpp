#include <iostream>
#include <fstream>
#include <unistd.h> 
#include <sstream>
using namespace std;

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


void storeHashedCardDetails(const string& cardNumber, const string& cvc) {
    cout << "\t\t\t\tHashing credit card details";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        sleep(1);
    }

    string hashedCardNumber = customHash(cardNumber);
    string hashedCvc = customHash(cvc);
    cout << "\n\n\t\t\t\tHashed credit card details: " << hashedCardNumber << " " << hashedCvc << endl;

    ofstream file("hashed_card_numbers.txt", ios::app);
    if (file.is_open()) {
        file << hashedCardNumber << " " << hashedCvc << endl;
        file.close();
        cout << "\t\t\t\tHashed credit card details stored successfully!\n";
    } else {
        cout << "\t\t\t\tFailed to open file for storing hashed credit card details.\n";
    }
}

int main() {
    storeHashedCardDetails("40877451", "084");
    storeHashedCardDetails("30517126", "091");
    storeHashedCardDetails("70974152", "899");
    storeHashedCardDetails("67814821", "017");
    return 0;
}
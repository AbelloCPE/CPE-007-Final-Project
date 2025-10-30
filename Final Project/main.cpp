#include <iostream>
#include "login.h"
#include "addFood.h"
#include "logFood.h"
#include "viewReport.h"
using namespace std;

int main() {
    int choice;

    do {
        cout << "=== Login & Registration ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}

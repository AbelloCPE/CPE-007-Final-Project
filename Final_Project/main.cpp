#include <iostream>
#include "UserManager.h"
using namespace std;

int main() {
    UserManager userManager;
    int choice;

    while (choice != 5){
        cout << "\n====== LOGIN SYSTEM ======\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Update Password\n";
        cout << "4. Display Users\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userManager.createAccount();
                break;
            case 2:
                userManager.login();
                break;
            case 3:
                userManager.updatePassword();
                break;
            case 4:
                userManager.displayUsers();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }; 

    return 0;
}

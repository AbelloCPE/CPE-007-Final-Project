#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "login.h"
#include "addFood.h"
#include "logFood.h"
#include "viewReport.h"
using namespace std;

// FOR SYSTEM CLEAR
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int main() {
    int choice;

    do {
        system(CLEAR); // THIS CLEARS THE SCREEN EACH TIME IT RUNS

        cout << setw(110) << "=================== LOGIN & REGISTRATION MENU ===================\n\n";
        cout << setw(80) << "1. Register\n";
        cout << setw(77) << "2. Login\n";
        cout << setw(77) << "3. Exit\n\n";
        cout << setw(77) << "Enter choice: ";
        cin >> choice;
        
        // THIS HANDLES ERRORS ON INPUT SUCH AS IF YOU ARAE GOING TO INPUT Q on 1-3 IT WILL JUST RETURN 
        if (cin.fail()){
			cin.clear();
        	cin.ignore(10000, '\n');
        	system(CLEAR);
        	cout << "Invalid input! Please enter a number between 1 and 3.\n";
        	cout << "\nPress Enter to continue...";
        	cin.ignore();
        	system(CLEAR);
        	continue;
	}

        system(CLEAR); // Clear again before showing new section

        switch (choice) {
            case 1:
                cout << setw(110) << "=================== REGISTER USER ===================\n\n";
                registerUser();
                break;

            case 2:
                cout << setw(110) << "=================== LOGIN ===================\n\n";
                loginUser();
                break;

            case 3:
                cout << setw(110) << "Exiting program...\n";
                break;

            default:
                cout << setw(100) << "Invalid choice. Try again.\n";
        }

        if (choice != 3) {
            cout << "\n" << setw(50)
                 << "Press Enter to return to the main menu...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 3);

    return 0;
}


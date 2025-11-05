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
        
        cout << "\033[36m"R"(
 _   _       _        _     _____               _    
| \ | |_   _| |_ _ __(_)   |_   _| __ __ _  ___| | __
|  \| | | | | __| '__| |_____| || '__/ _` |/ __| |/ /
| |\  | |_| | |_| |  | |_____| || | | (_| | (__|   < 
|_| \_|\__,_|\__|_|  |_|     |_||_|  \__,_|\___|_|\_\
		)" << '\n' << "\033[0m";
        
        
        
        cout << "=================== \033[36mLOGIN & REGISTRATION MENU\033[0m ===================\n\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        // THIS HANDLES ERRORS ON INPUT SUCH AS IF YOU ARAE GOING TO INPUT Q on 1-3 IT WILL JUST RETURN 
        if (cin.fail()){
			cin.clear();
        	cin.ignore(10000, '\n');
        	system(CLEAR);
        	cout << "\033[31mInvalid input! Please enter a number between 1 and 3.\033[0m\n";
        	cout << "\nPress Enter to continue...";
        	cin.ignore();
        	system(CLEAR);
        	continue;
	}

        system(CLEAR); // Clear again before showing new section

        switch (choice) {
            case 1:
                cout << "=================== \033[36mREGISTER USER\033[0m ===================\n\n";
                registerUser();
                break;

            case 2:
                cout << "=================== \033[36mLOGIN\033[0m ===================\n\n";
                loginUser();
                break;

            case 3:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "\033[31mInvalid choice. Try again.\033[0m\n";
        }

        if (choice != 3) {
            cout << "\n" << "Press Enter to return to the main menu...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 3);

    return 0;
}


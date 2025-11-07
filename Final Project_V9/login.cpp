#include "login.h"
#include "userprofile.h"
#include "foodlog.h"
#include "dietoption.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void registerUser() {
    string username, password, gender;
    int age;
    double weight, height;
    double bmi, bmr;

    cout << "=== \033[36mUSER REGISTRATION\033[0m ===\n";
    
    cin.ignore();
    cout << "Enter username: ";
    getline(cin, username);
    
    cout << "Enter password: ";
    cin >> password;

    cout << "\n--- PROFILE INFORMATION ---\n";
    
    while(true){
	    cout << "Enter age: ";
		cin >> age;
	if (cin.fail() || age <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid input. Please enter a valid number for age.\033[0m\n";
        } else break;
    }
    
    while(true){
	    cout << "Enter weight (kg): ";
	    cin >> weight;
    if (cin.fail() || weight <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid input. Please enter a valid number for weight.\033[0m\n";
        } else break;
    }
    
    while (true) {
        cout << "Enter height (cm): ";
        cin >> height;
        if (cin.fail() || height <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid input. Please enter a valid number for height.\033[0m\n";
        } else break;
    }

    do {
        cout << "Enter gender (male/female): ";
        cin >> gender;
        for (auto &c : gender) c = tolower(c);
        if (gender != "male" && gender != "female") {
            cout << "\033[31mInvalid input. Please type 'male' or 'female'.\033[0m\n";
        }
    } while (gender != "male" && gender != "female");

    double height_m = height / 100.0;
    bmi = weight / (height_m * height_m);

    string bmiStatus;
    if (bmi < 18.5)
        bmiStatus = "Underweight";
    else if (bmi < 24.9)
        bmiStatus = "Normal weight";
    else if (bmi < 29.9)
        bmiStatus = "Overweight";
    else
        bmiStatus = "Obese";

    if (gender == "male")
        bmr = 88.36 + (13.4 * weight) + (4.8 * height) - (5.7 * age);
    else
        bmr = 447.6 + (9.2 * weight) + (3.1 * height) - (4.3 * age);

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << " " << age << " "
             << weight << " " << height << " " << gender << " "
             << fixed << setprecision(2) << bmi << " " << bmr << endl;
        file.close();
    }

    createUserProfileFile(username, password, age, weight, height, gender, bmi, bmiStatus, bmr);

	system("cls");
    cout << "\n=== \033[36mREGISTRATION COMPLETE\033[0m ===\n";
    cout << "Username: " << username << endl;
    cout << "BMI: " << fixed << setprecision(2) << bmi << " (" << bmiStatus << ")\n";
    cout << "BMR: " << fixed << setprecision(2) << bmr << " kcal/day\n";
    cout << "\033[32mRegistration successful!\033[0m\n\n";
}

void forgotPassword(){
	string username, password;
    string fileUser, filePass, gender;
    int age;
    double weight, height, bmi, bmr;
    bool found = false;
    
    cout << "=== \033[36mFORGOT PASSWORD\033[0m ===\n";
    cout << "Enter your username: ";
    cin >> username;
    
	ifstream file("users.txt");
    if (!file) {
        cout << "\033[31mNo registered users found.\033[0m\n";
        return;
    }

    while (file >> fileUser >> filePass >> age >> weight >> height >> gender >> bmi >> bmr) {
        if (fileUser == username) {
            cout << "\033[32mYour password is: " << filePass << "\033[0m\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\033[31mUsername not found.\033[0m\n";
    }
}



void loginUser() {
    string username, password;
    string fileUser, filePass, gender;
    int age;
    double weight, height, bmi, bmr;
    bool found = false;

    cout << "=== \033[36mUSER LOGIN\033[0m ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    if (!file) {
        cout << "\033[31mNo registered users found. Please register first.\033[0m\n\n";
        return;
    }

    while (file >> fileUser >> filePass >> age >> weight >> height >> gender >> bmi >> bmr) {
        if (fileUser == username && filePass == password) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
    	
    	system("cls");
        cout << "\033[32m\nLogin successful! Welcome, " << username << "!\033[0m\n";
        int option;
        do {
            cout << "\n=== \033[36mMAIN MENU\033[0m ===\n";
            cout << "1. User Profile\n";
            cout << "2. Set Diet Goal\n";
            cout << "3. Add Food\n";
            cout << "4. Food Log\n";
            cout << "5. Daily Report\n";
            cout << "6. Logout\n";
            cout << "Enter choice: ";
            cin >> option;

            switch (option) {
                case 1:
                    displayUserProfile(username);
                    break;
                case 2:
                    setDietGoal(username);
                    break;
                case 3:
                    addFoodToList(username);
                    break;
                case 4:
                    logFood(username);
                    break;
                case 5:
                    viewReport(username, bmr);
                    break;
                case 6:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "\033[31mInvalid choice.\033[0m\n";
            }
        } while (option != 6);

    } else {
        cout << "\033[31mInvalid username or password.\033[0m\n\n";
    }
}

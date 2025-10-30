#include "login.h"
#include "userprofile.h"
#include "foodlog.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void registerUser() {
    string username, password, gender;
    int age;
    double weight, height;
    double bmi, bmr;

    cout << "=== USER REGISTRATION ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    cout << "\n--- PROFILE INFORMATION ---\n";
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter weight (kg): ";
    cin >> weight;
    cout << "Enter height (cm): ";
    cin >> height;

    do {
        cout << "Enter gender (male/female): ";
        cin >> gender;
        for (auto &c : gender) c = tolower(c);
        if (gender != "male" && gender != "female") {
            cout << "Invalid input. Please type 'male' or 'female'.\n";
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

    cout << "\n=== REGISTRATION COMPLETE ===\n";
    cout << "Username: " << username << endl;
    cout << "BMI: " << fixed << setprecision(2) << bmi << " (" << bmiStatus << ")\n";
    cout << "BMR: " << fixed << setprecision(2) << bmr << " kcal/day\n";
    cout << "Registration successful!\n\n";
}

void loginUser() {
    string username, password;
    string fileUser, filePass, gender;
    int age;
    double weight, height, bmi, bmr;
    bool found = false;

    cout << "=== USER LOGIN ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    if (!file) {
        cout << "No registered users found. Please register first.\n\n";
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
        cout << "\nLogin successful! Welcome, " << username << "!\n";
        int option;
        do {
            cout << "\n=== MAIN MENU ===\n";
            cout << "1. User Profile\n";
            cout << "2. Food Log\n";
            cout << "3. Add Food\n";
            cout << "4. Daily Report\n";
            cout << "5. Logout\n";
            cout << "Enter choice: ";
            cin >> option;

            switch (option) {
                case 1:
                    displayUserProfile(username);
                    break;
                case 2:
                    logFood(username);
                    break;
                case 3:
                    addFoodToList(username);
                    break;
                case 4:
                    viewReport(username, bmr);
                    break;
                case 5:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (option != 5);

    } else {
        cout << "Invalid username or password.\n\n";
    }
}

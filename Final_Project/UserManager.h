#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "HealthManager.h" 
#include <iostream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
    string gender; // "Man" or "Woman"
    int age;
    float weight;
    float height;
};

class UserManager {
private:
    static const int MAX_USERS = 100;
    User users[MAX_USERS];
    int userCount;

public:
    UserManager() {
        userCount = 0;
    }

    void createAccount() {
        if (userCount >= MAX_USERS) {
            cout << "User limit reached.\n";
            return;
        }

        cout << "Enter username: ";
        cin >> users[userCount].username;
        cout << "Enter password: ";
        cin >> users[userCount].password;

        // Gender input
        int genderChoice;
        cout << "Select gender (1 - Man, 2 - Woman): ";
        cin >> genderChoice;
        if (genderChoice == 1)
            users[userCount].gender = "Man";
        else if (genderChoice == 2)
            users[userCount].gender = "Woman";
        else {
            cout << "Invalid choice, defaulting to 'Unspecified'.\n";
            users[userCount].gender = "Unspecified";
        }

        cout << "Enter age: ";
        cin >> users[userCount].age;
        cout << "Enter weight (kg): ";
        cin >> users[userCount].weight;
        cout << "Enter height (cm): ";
        cin >> users[userCount].height;

        userCount++;
        cout << "Account created successfully!\n";
    }

    void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful! Welcome, " << username << "!\n";
            cout << "\n--- Profile Info ---\n";
            cout << "Gender: " << users[i].gender << endl;
            cout << "Age: " << users[i].age << endl;
            cout << "Weight: " << users[i].weight << " kg\n";
            cout << "Height: " << users[i].height << " cm\n";

            // 🔹 Launch health menu
            HealthManager hm;
            hm.openHealthMenu(users[i].weight, users[i].height);
            return;
        }
    }
    cout << "Invalid username or password.\n";
}


    void updatePassword() {
        string username, oldPass, newPass;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter old password: ";
        cin >> oldPass;

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == oldPass) {
                cout << "Enter new password: ";
                cin >> newPass;
                users[i].password = newPass;
                cout << "Password updated successfully!\n";
                return;
            }
        }
        cout << "Invalid username or old password.\n";
    }

    void displayUsers() {
        if (userCount == 0) {
            cout << "No users registered yet.\n";
            return;
        }

        cout << "\n--- Registered Users ---\n";
        for (int i = 0; i < userCount; i++) {
            cout << i + 1 << ". " << users[i].username
                 << " | Gender: " << users[i].gender
                 << " | Age: " << users[i].age
                 << " | Weight: " << users[i].weight << "kg"
                 << " | Height: " << users[i].height << "cm" << endl;
        }
    }
};

#endif

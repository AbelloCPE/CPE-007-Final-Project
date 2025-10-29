#include "login.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void registerUser() {
    string username, password;

    cout << "=== User Registration ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ofstream file("users.txt", ios::app); // Append to file
    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful!\n\n";
}

void loginUser() {
    string username, password, fileUser, filePass;
    bool found = false;

    cout << "=== User Login ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    if (!file) {
        cout << "No registered users found. Please register first.\n\n";
        return;
    }

    while (file >> fileUser >> filePass) {
        if (fileUser == username && filePass == password) {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
        cout << "Login successful! Welcome, " << username << "!\n\n";
    else
        cout << "Invalid username or password.\n\n";
}




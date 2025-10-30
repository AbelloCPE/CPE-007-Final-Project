#include "dietoption.h"
#include <iostream>
#include <fstream>
using namespace std;

void setDietGoal(const string& username) {
    int choice;
    cout << "\n=== SET DIET GOAL ===\n";
    cout << "1. Gain Weight (Calorie Surplus)\n";
    cout << "2. Maintain Weight\n";
    cout << "3. Lose Weight (Calorie Deficit)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    string goal;
    switch (choice) {
        case 1: goal = "gain"; break;
        case 2: goal = "maintain"; break;
        case 3: goal = "lose"; break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    ofstream file(username + "_diet.txt");
    if (file.is_open()) {
        file << goal;
        file.close();
        cout << "Diet goal set to '" << goal << "' successfully!\n";
    } else {
        cout << "Error saving diet goal.\n";
    }
}

double getAdjustedBMR(const string& username, double bmr) {
    ifstream file(username + "_diet.txt");
    if (!file.is_open()) return bmr;

    string goal;
    getline(file, goal);
    file.close();

    if (goal == "gain") return bmr + 300;
    if (goal == "lose") return bmr - 300;
    return bmr;
}

#include "dietoption.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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

    // Save goal
    ofstream file(username + "_diet.txt");
    if (file.is_open()) {
        file << goal;
        file.close();
        cout << "Diet goal set to '" << goal << "' successfully!\n";
    } else {
        cout << "Error saving diet goal.\n";
        return;
    }

    // Retrieve original (baseline) BMR from users.txt
    ifstream users("users.txt");
    if (!users.is_open()) {
        cout << "Error: users.txt not found.\n";
        return;
    }

    string u, p, gender;
    int age;
    double weight, height, bmi, baseBMR = 0;
    while (users >> u >> p >> age >> weight >> height >> gender >> bmi >> baseBMR) {
        if (u == username) break;
    }
    users.close();

    // Calculate adjusted BMR
    double adjusted = getAdjustedBMR(username, baseBMR);

    // Update profile file
    string profileFile = username + "_profile.txt";
    ifstream in(profileFile);
    if (!in.is_open()) {
        cout << "Error: Cannot find profile file to update BMR.\n";
        return;
    }

    stringstream buffer;
    string line;
    bool updated = false;
    while (getline(in, line)) {
        if (line.find("BMR (Calories Needed):") != string::npos) {
            ostringstream newLine;
            newLine << "BMR (Calories Needed): " << fixed << setprecision(2)
                    << adjusted << " kcal/day";
            line = newLine.str();
            updated = true;
        }
        buffer << line << "\n";
    }
    in.close();

    ofstream out(profileFile);
    out << buffer.str();
    out.close();

    if (updated)
        cout << "Profile updated with adjusted BMR (" << adjusted << " kcal/day)!\n";
    else
        cout << "Warning: BMR line not found in profile file.\n";
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

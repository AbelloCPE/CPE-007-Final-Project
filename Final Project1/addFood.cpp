#include "addFood.h"
#include <iostream>
#include <fstream>
using namespace std;

void addFoodToList(const string& username) {
    string foodName;
    double calories, protein, carbs;

    cout << "\n=== ADD FOOD TO LIST ===\n";
    cout << "Enter food name: ";
    cin.ignore();
    getline(cin, foodName);
    cout << "Calories: ";
    cin >> calories;
    cout << "Protein (g): ";
    cin >> protein;
    cout << "Carbs (g): ";
    cin >> carbs;

    ofstream file(username + "_foodlist.txt", ios::app);
    if (file.is_open()) {
        file << foodName << "," << calories << "," << protein << "," << carbs << endl;
        file.close();
        cout << "Food added successfully!\n";
    } else {
        cout << "Error saving food list.\n";
    }
}

#include "foodlog.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
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

void logFood(const string& username) {
    ifstream foodList(username + "_foodlist.txt");
    if (!foodList) {
        cout << "No food list found. Please add some foods first.\n";
        return;
    }

    cout << "\n=== YOUR FOOD LIST ===\n";
    string foodName;
    double calories, protein, carbs;
    int index = 0;

    string names[100];
    double cals[100];

    while (getline(foodList, foodName, ',')) {
        foodList >> calories;
        foodList.ignore();
        foodList >> protein;
        foodList.ignore();
        foodList >> carbs;
        foodList.ignore();

        index++;
        names[index] = foodName;
        cals[index] = calories;
        cout << index << ". " << foodName << " - " << calories << " kcal\n";
    }
    foodList.close();

    if (index == 0) {
        cout << "Your food list is empty.\n";
        return;
    }

    int choice;
    cout << "\nEnter which food you ate (1-" << index << "): ";
    cin >> choice;

    if (choice < 1 || choice > index) {
        cout << "Invalid choice.\n";
        return;
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(ltm->tm_mday);

    ofstream logFile(username + "_foodlog.txt", ios::app);
    logFile << date << "," << names[choice] << "," << cals[choice] << endl;
    logFile.close();

    cout << "Logged " << names[choice] << " (" << cals[choice] << " kcal) successfully!\n";
}


void viewReport(const string& username, double bmr) {
    ifstream logFile(username + "_foodlog.txt");
    if (!logFile) {
        cout << "No food logs found.\n";
        return;
    }

    string date, food;
    double calories, protein, carbs;
    double totalCalories = 0;

    // Get today's date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string today = to_string(1900 + ltm->tm_year) + "-" +
                   to_string(1 + ltm->tm_mon) + "-" +
                   to_string(ltm->tm_mday);

    cout << "\n=== DAILY REPORT (" << today << ") ===\n";

    // Each line format: date,food,calories,protein,carbs
    while (getline(logFile, date, ',')) {
        getline(logFile, food, ',');
        logFile >> calories;
        logFile.ignore(); // skip comma
        logFile >> protein;
        logFile.ignore();
        logFile >> carbs;
        logFile.ignore();

        if (date == today) {
            cout << "- " << food << ": " << calories << " kcal\n";
            totalCalories += calories;
        }
    }

    cout << "\nTotal Calories Today: " << totalCalories << " kcal\n";
    cout << "BMR: " << bmr << " kcal/day\n";

    if (totalCalories >= bmr)
        cout << "You reached or exceeded your BMR today!\n";
    else
        cout << "You are below your BMR goal.\n";
}


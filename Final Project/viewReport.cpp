#ifndef FOOD_REPORT_H
#define FOOD_REPORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "dietoption.h"
using namespace std;

void viewReport(const string& username, double bmr) {
    ifstream file(username + "_foodlog.txt");
    if (!file) {
        cout << "No food logs found.\n";
        return;
    }

    double adjustedBMR = getAdjustedBMR(username, bmr);

    string line, date, food;
    double calories, protein, carbs;
    int quantity;
    double totalCalories = 0, totalProtein = 0, totalCarbs = 0;

    // Get today's date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string today = to_string(1900 + ltm->tm_year) + "-" +
                   to_string(1 + ltm->tm_mon) + "-" +
                   to_string(ltm->tm_mday);

    cout << "\n=== DAILY REPORT (" << today << ") ===\n";

    while (getline(file, line)) {
        // Split line by commas
        size_t p1 = line.find(",");
        size_t p2 = line.find(",", p1 + 1);
        size_t p3 = line.find(",", p2 + 1);
        size_t p4 = line.find(",", p3 + 1);
        size_t p5 = line.find(",", p4 + 1);

        if (p4 == string::npos) continue;

        date = line.substr(0, p1);
        food = line.substr(p1 + 1, p2 - p1 - 1);
        calories = stod(line.substr(p2 + 1, p3 - p2 - 1));
        protein = stod(line.substr(p3 + 1, p4 - p3 - 1));
        carbs = stod(line.substr(p4 + 1, p5 - p4 - 1));
        quantity = stoi(line.substr(p5 + 1));

        if (date == today) {
            cout << "- " << food << " " << quantity << "x"
                 << ": " << calories << " kcal, "
                 << protein << "g protein, "
                 << carbs << "g carbs\n";

            totalCalories += calories;
            totalProtein += protein;
            totalCarbs += carbs;
        }
    }
    file.close();

    cout << "\n=== TOTALS FOR TODAY ===\n";
    cout << "Calories: " << totalCalories << " kcal\n";
    cout << "Protein:  " << totalProtein << " g\n";
    cout << "Carbs:    " << totalCarbs << " g\n";
    cout << "BMR (Goal): " << adjustedBMR << " kcal/day\n\n";

    if (totalCalories == 0)
        cout << "No foods logged today.\n";
    else if (totalCalories < adjustedBMR)
        cout << "You are below your calorie goal.\n";
    else if (totalCalories >= adjustedBMR + 200)
        cout << "You exceeded your calorie goal!\n";
    else
        cout << "You reached your calorie goal.\n";
}

#endif

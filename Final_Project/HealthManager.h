#ifndef HEALTHMANAGER_H
#define HEALTHMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Food {
    string name;
    float calories;
    float protein;
    float carbs;
};

class HealthManager {
private:
    vector<Food> foodList;
    string dietType;

public:
    // Calculate BMI
    float calculateBMI(float weight, float height) {
        float heightInMeters = height / 100; // convert cm to meters
        return weight / (heightInMeters * heightInMeters);
    }

    // Display BMI status
    void showBMIStatus(float weight, float height) {
        float bmi = calculateBMI(weight, height);
        cout << fixed << setprecision(2);
        cout << "\nYour BMI: " << bmi << endl;

        if (bmi < 18.5)
            cout << "Status: Underweight\n";
        else if (bmi < 25)
            cout << "Status: Normal\n";
        else
            cout << "Status: Overweight\n";
    }

    // Select diet plan
    void selectDiet() {
        int choice;
        cout << "\nChoose a diet goal:\n";
        cout << "1. Bulk (Gain Weight)\n";
        cout << "2. Calorie Deficit (Lose Weight)\n";
        cout << "3. Maintain Weight\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: dietType = "Bulk"; break;
            case 2: dietType = "Calorie Deficit"; break;
            case 3: dietType = "Maintain"; break;
            default: dietType = "Unspecified"; break;
        }

        cout << "Selected Diet: " << dietType << "\n";
    }

    // Add food to list
    void addFood() {
        Food newFood;
        cout << "\nEnter food name: ";
        cin.ignore();
        getline(cin, newFood.name);
        cout << "Enter calories: ";
        cin >> newFood.calories;
        cout << "Enter protein (g): ";
        cin >> newFood.protein;
        cout << "Enter carbs (g): ";
        cin >> newFood.carbs;

        foodList.push_back(newFood);
        cout << "Food added successfully!\n";
    }

    // Display all added foods
    void showFoods() {
        if (foodList.empty()) {
            cout << "\nNo foods added yet.\n";
            return;
        }

        cout << "\n--- Added Foods ---\n";
        cout << left << setw(20) << "Food Name" << setw(10) << "Calories" 
             << setw(10) << "Protein(g)" << setw(10) << "Carbs(g)" << endl;
        cout << string(50, '-') << endl;

        for (const auto &food : foodList) {
            cout << left << setw(20) << food.name 
                 << setw(10) << food.calories 
                 << setw(10) << food.protein 
                 << setw(10) << food.carbs << endl;
        }
    }

    // Main menu after login
    void openHealthMenu(float weight, float height) {
        int choice;
        do {
            cout << "\n====== HEALTH MENU ======\n";
            showBMIStatus(weight, height);
            cout << "\n1. Select Diet Plan\n";
            cout << "2. Add Food\n";
            cout << "3. Show Added Foods\n";
            cout << "4. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    selectDiet();
                    break;
                case 2:
                    addFood();
                    break;
                case 3:
                    showFoods();
                    break;
                case 4:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

#endif

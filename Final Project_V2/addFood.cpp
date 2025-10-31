#include "addFood.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void addFoodToList(const string& username) {
    cout << "\n=== ADD FOOD TO LIST ===\n";
    cout << "1. Choose from predefined foods\n";
    cout << "2. Add custom food manually\n";
    cout << "3. Mix existing foods to create a new one\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    string foodName;
    double calories = 0, protein = 0, carbs = 0;

    if (choice == 1) {
        // Load predefined foods
        ifstream predef("predefined_foods.txt");
        if (!predef) {
            cout << "No predefined food file found.\n";
            return;
        }

        vector<string> foods;
        vector<double> cals, prots, carbsArr;
        string line;

        while (getline(predef, line)) {
            size_t p1 = line.find(",");
            size_t p2 = line.find(",", p1 + 1);
            size_t p3 = line.find(",", p2 + 1);
            if (p3 == string::npos) continue;

            string name = line.substr(0, p1);
            double cal = stod(line.substr(p1 + 1, p2 - p1 - 1));
            double prot = stod(line.substr(p2 + 1, p3 - p2 - 1));
            double carb = stod(line.substr(p3 + 1));

            foods.push_back(name);
            cals.push_back(cal);
            prots.push_back(prot);
            carbsArr.push_back(carb);
        }
        predef.close();

        if (foods.empty()) {
            cout << "Predefined list is empty.\n";
            return;
        }

        // Pagination variables
        int page = 0;
        const int perPage = 10;
        int totalPages = (foods.size() + perPage - 1) / perPage;
        string action;

        while (true) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "\n=== PREDEFINED FOOD LIST (Page " << page + 1 << " of " << totalPages << ") ===\n";

            int start = page * perPage;
            int end = min((int)foods.size(), start + perPage);
            for (int i = start; i < end; ++i) {
                cout << (i + 1) << ". " << foods[i]
                     << " - " << cals[i] << " kcal, "
                     << prots[i] << "g protein, "
                     << carbsArr[i] << "g carbs\n";
            }

            cout << "\nEnter number to select food, N for next, P for previous, or Q to quit: ";
            cin >> action;

            if (action == "N" || action == "n") {
                if (page < totalPages - 1) page++;
                else cout << "You're on the last page.\n";
            } 
            else if (action == "P" || action == "p") {
                if (page > 0) page--;
                else cout << "You're on the first page.\n";
            } 
            else if (action == "Q" || action == "q") {
                cout << "Cancelled.\n";
                return;
            } 
            else {
                // Check if user entered a valid number
                try {
                    int select = stoi(action);
                    if (select >= 1 && select <= (int)foods.size()) {
                        foodName = foods[select - 1];
                        calories = cals[select - 1];
                        protein = prots[select - 1];
                        carbs = carbsArr[select - 1];
                        break;
                    } else {
                        cout << "Invalid number.\n";
                    }
                } catch (...) {
                    cout << "Invalid input.\n";
                }
            }
        }
    }
    else if (choice == 2) {
        // Add custom food
        cin.ignore();
        cout << "Enter food name: ";
        getline(cin, foodName);
        cout << "Calories: ";
        cin >> calories;
        cout << "Protein (g): ";
        cin >> protein;
        cout << "Carbs (g): ";
        cin >> carbs;
    }
    else if (choice == 3) {
        // Mix existing foods
        ifstream file(username + "_foodlist.txt");
        if (!file) {
            cout << "No existing food list found. Add some foods first.\n";
            return;
        }

        vector<string> foods;
        vector<double> cals, prots, carbsArr;
        string line;
        int index = 0;

        cout << "\n=== YOUR FOOD LIST ===\n";
        while (getline(file, line)) {
            size_t p1 = line.find(",");
            size_t p2 = line.find(",", p1 + 1);
            size_t p3 = line.find(",", p2 + 1);
            if (p3 == string::npos) continue;

            string name = line.substr(0, p1);
            double cal = stod(line.substr(p1 + 1, p2 - p1 - 1));
            double prot = stod(line.substr(p2 + 1, p3 - p2 - 1));
            double carb = stod(line.substr(p3 + 1));

            foods.push_back(name);
            cals.push_back(cal);
            prots.push_back(prot);
            carbsArr.push_back(carb);

            cout << ++index << ". " << name << " - " << cal << " kcal, "
                 << prot << "g protein, " << carb << "g carbs\n";
        }
        file.close();

        if (index == 0) {
            cout << "Your food list is empty.\n";
            return;
        }

        vector<int> selected;
        cout << "\nEnter food numbers to mix (separated by space, 0 to stop): ";
        int choiceNum;
        while (true) {
            cin >> choiceNum;
            if (choiceNum == 0) break;
            if (choiceNum >= 1 && choiceNum <= index) {
                selected.push_back(choiceNum - 1);
            } else {
                cout << "Invalid number. Try again.\n";
            }
        }

        if (selected.empty()) {
            cout << "No foods selected.\n";
            return;
        }

        // Combine nutrition values
        for (int i : selected) {
            calories += cals[i];
            protein += prots[i];
            carbs += carbsArr[i];
        }

        cin.ignore();
        cout << "Enter a name for your new mixed food: ";
        getline(cin, foodName);

        cout << "New food '" << foodName << "' created! Total: "
             << calories << " kcal, " << protein << "g protein, "
             << carbs << "g carbs.\n";
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    // Save the new or mixed food
    ofstream file(username + "_foodlist.txt", ios::app);
    if (file.is_open()) {
        file << foodName << "," << calories << "," << protein << "," << carbs << endl;
        file.close();
        cout << "Food saved successfully!\n";
    } else {
        cout << "Error saving food list.\n";
    }
}


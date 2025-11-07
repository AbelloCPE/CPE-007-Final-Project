#include "addFood.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> // ? for setw(), left, right, etc.
#include <cstdlib>
using namespace std;


void addFoodToList(const string& username) {
	system("cls");
    cout << "\n=== \033[36mADD FOOD TO LIST\033[0m ===\n";
    cout << "1. Choose from predefined foods\n";
    cout << "2. Add custom food manually\n";
    cout << "3. Mix existing foods to create a new one\n";
    cout << "0. Go Back\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
	
	//INORDER TO NOT RUN INFINITELY WHEN YOU INPUT A WRONG LETTER/NUMBER
	if (cin.fail()){
		cin.clear();
        cin.ignore(10000, '\n');
        system("cls");
        cout << "Invalid input! Please enter a number between (1-3) or (0) to go back.\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        system("cls");
        return addFoodToList(username);
	}
	
	
    string foodName;
    double calories = 0, protein = 0, carbs = 0;
    
    if (choice == 0){
    	system("cls");
    	return;
	}

    if (choice == 1) {
        // Load predefined foods
        ifstream predef("predefined_foods.txt");
        if (!predef) {
            cout << "No predefined food file found.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
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
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return;
        }

        // Pagination variables
        int page = 0;
        const int perPage = 10;
        int totalPages = (foods.size() + perPage - 1) / perPage;
        string action;

        while (true) {
			system("cls");
			
            cout << "\n=== \033[36mPREDEFINED FOOD LIST (Page " << page + 1 << " of " << totalPages << ")\033[0m ===\n\n";

            // ?? Table header
            cout << left << setw(5) << "No."
                 << setw(25) << "Food Name"
                 << right << setw(12) << "Calories"
                 << setw(12) << "Protein(g)"
                 << setw(12) << "Carbs(g)" << "\n";
            cout << string(65, '-') << "\n";

            int start = page * perPage;
            int end = min((int)foods.size(), start + perPage);
            for (int i = start; i < end; ++i) {
                cout << left << setw(5) << (i + 1)
                     << setw(25) << foods[i]
                     << right << setw(12) << fixed << setprecision(1) << cals[i]
                     << setw(12) << fixed << setprecision(1) << prots[i]
                     << setw(12) << fixed << setprecision(1) << carbsArr[i]
                     << "\n";
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
                system("cls");
                return addFoodToList(username);
            } 
            else {
                try {
                    int select = stoi(action);
                    if (select >= 1 && select <= (int)foods.size()) {
                        foodName = foods[select - 1];
                        calories = cals[select - 1];
                        protein = prots[select - 1];
                        carbs = carbsArr[select - 1];
                        break;
                    } else {
                        cout << "\033[31mInvalid number.\033[0m\n";
                    }
                } catch (...) {
                    cout << "\033[31mInvalid input.\033[0m\n";
                }
            }
        }
    }
    else if (choice == 2) {
        // Add custom food
        char confirm;
        system("cls");
        cin.ignore();
        cout << "=== \033[36mCUSTOM FOOD ADD\033[0m ===\n";
        cout << "Do you want to continue adding a custom food? (Y/N): ";
        cin >> confirm;
        
        if (confirm == 'N' || confirm == 'n'){
        	system("cls");
        	return addFoodToList(username);
		}
        
        cin.ignore();
        cout << "Enter food name: ";
        getline(cin, foodName);
    
        
        cout << "Calories: ";
        while (!(cin >> calories)){
        	cin.clear();
        	cin.ignore(10000, '\n');
        	cout << "\033[31mInvalid, Enter a number for calories: \033[0m";
		}

        cout << "Protein (g): ";
        while (!(cin >> protein)){
        	cin.clear();
        	cin.ignore(10000, '\n');
        	cout << "\033[31mInvalid, Enter a number for protein: \033[0m";
		}
        
        cout << "Carbs (g): ";
        while (!(cin >> carbs)){
        	cin.clear();
        	cin.ignore(10000, '\n');
        	cout << "\033[31mInvalid, Enter a number for carbs: \033[0m";
		}
		
		cin.ignore();
	    system("cls");
	    cout << "\n Custom food added successfully!\n";
	    cout << left << setw(15) << "Food:"    << foodName << "\n";
	    cout << left << setw(15) << "Calories:" << fixed << setprecision(1) << calories << " kcal\n";
	    cout << left << setw(15) << "Protein:"  << fixed << setprecision(1) << protein  << " g\n";
	    cout << left << setw(15) << "Carbs:"    << fixed << setprecision(1) << carbs    << " g\n";
    }
    else if (choice == 3) {
        // Mix existing foods
        system("cls");
        ifstream file(username + "_foodlist.txt");
        if (!file) {
            cout << "No existing food list found. Add some foods first.\n";
            cout << "\nPress Enter to continue...";
        	cin.ignore();
        	cin.get();
        	system("cls");
            return;
        }

        vector<string> foods;
        vector<double> cals, prots, carbsArr;
        string line;
        int index = 0;

        cout << "\n=== \033[36mYOUR FOOD LIST\033[0m ===\n\n";
        cout << left << setw(5) << "No."
             << setw(25) << "Food Name"
             << right << setw(12) << "Calories"
             << setw(12) << "Protein(g)"
             << setw(12) << "Carbs(g)" << "\n";
        cout << string(65, '-') << "\n";

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

            cout << left << setw(5) << (++index)
                 << setw(25) << name
                 << right << setw(12) << fixed << setprecision(1) << cal
                 << setw(12) << fixed << setprecision(1) << prot
                 << setw(12) << fixed << setprecision(1) << carb
                 << "\n";
        }
        file.close();

        if (index == 0) {
            cout << "\033[31mYour food list is empty.\033[0m\n";
            cout << "\nPress Enter to continue...";
        	cin.ignore();
        	cin.get();
        	system("cls");
            return;
        }

        vector<int> selected;
        cout << "\nEnter food numbers to mix (separated by space, (0) to stop): ";
        
        int choiceNum;
        while (true) {
            cin >> choiceNum;
            
            if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid input! Please enter valid numbers only.\033[0m\n";
            continue;
        }
            
            if (choiceNum == 0) break;
            if (choiceNum >= 1 && choiceNum <= index)
                selected.push_back(choiceNum - 1);
            else
                cout << "\033[31mInvalid number. Try again.\033[0m\n";
        }

        if (selected.empty()) {
            cout << "\033[31mNo foods selected.\033[0m\n";
            cout << "\nPress Enter to continue...";
        	cin.ignore();
        	cin.get();
        	system("cls");
            return;
        }

        // Combine nutrition values
        for (int i : selected) {
            calories += cals[i];
            protein += prots[i];
            carbs += carbsArr[i];
        }

        cin.ignore();
        cout << "\nEnter a name for your new mixed food: ";
        getline(cin, foodName);
        
        system("cls");

        cout << "\nNew food '" << foodName << "' created! Total:\n";
        cout << left << setw(15) << "Calories:" << fixed << setprecision(1) << calories << " kcal\n";
        cout << left << setw(15) << "Protein:"  << fixed << setprecision(1) << protein  << " g\n";
        cout << left << setw(15) << "Carbs:"    << fixed << setprecision(1) << carbs    << " g\n";
    }
    else {
        cout << "\033[31mInvalid choice.\033[0m\n";
        return;
    }

    // Save the new or mixed food
    ofstream file(username + "_foodlist.txt", ios::app);
    if (file.is_open()) {
        file << foodName << "," << calories << "," << protein << "," << carbs << endl;
        file.close();
        cout << "\nFood saved successfully!\n";
    
    } else {
        cout << "\033[31mError saving food list.\033[0m\n";
    }
    
        cout << "\nPress Enter to return to menu...";
    	cin.get();
    	system("cls");
    
}


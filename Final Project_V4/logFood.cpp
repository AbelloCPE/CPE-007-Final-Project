#ifndef LOGFOOD_H
#define LOGFOOD_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void logFood(const string& username) {
	system(CLEAR);
	
    ifstream foodList(username + "_foodlist.txt");
    if (!foodList) {
        cout << "No food list found. Please add some foods first.\n";
        cout << "\nPress Enter to go back...";
        cin.ignore();
        cin.get();
        system(CLEAR);
        return;
    }

    cout << "\n=== YOUR FOOD LIST ===\n";
    string foodName;
    double calories, protein, carbs;
    int index = 0;

    string names[100];
    double cals[100], prots[100], carbsArr[100];

    // Read food list (name, calories, protein, carbs)
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
        prots[index] = protein;
        carbsArr[index] = carbs;

        cout << index << ". " << foodName
             << "\t-\t" << calories << " kcal | "
             << protein << "g protein | "
             << carbs << "g carbs\n";
    }
    foodList.close();

    if (index == 0) {
        cout << "Your food list is empty.\n";
        cout << "\nPress Enter to go back...";
        cin.ignore();
        cin.get();
        system(CLEAR);
        return;
    }
    
    int choice;
    if (index == 1) {

// ERROR HANDLING INCASE THEY ENTER SOMETIHING IN THE ALPHABET
    cout << "\nEnter which food you ate (1) or 0 to go back: ";
    while(!(cin >> choice)){
    	cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid input! Please enter a number: ";
	}
}
	else{
		cout << "\nEnter which food you ate (1-" << index << ", or 0 to go back): ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number (1-" << index << " or 0 to go back): ";
	}
}

	if (choice==0){
		system(CLEAR);
		return;
	}

// FOR RANGE
    if (choice < 1 ||choice > index) {
        cout << "Invalid choice.\n";
        cout << "\nPress Enter to go back...";
        cin.ignore();
        cin.get();
        system(CLEAR);
        return;
    }

    int quantity;
    cout << "How many servings did you eat? ";
    while (!(cin >> quantity)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter a valid number of servings: ";
    }

    if (quantity <= 0) {
        cout << "Invalid quantity.\n";
        cout << "\nPress Enter to go back...";
        cin.ignore();
        cin.get();
        system(CLEAR);
        return;
    }

    // Multiply by quantity
    double totalCals = cals[choice] * quantity;
    double totalProt = prots[choice] * quantity;
    double totalCarb = carbsArr[choice] * quantity;

    // Get current date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(ltm->tm_mday);

    // Save to log file
    ofstream logFile(username + "_foodlog.txt", ios::app);
    logFile << date << "," << names[choice] << "," << totalCals << ","
            << totalProt << "," << totalCarb << "," << quantity << endl;
    logFile.close();

    cout << "\nLogged " << names[choice] << " " << quantity << "x" << " successfully!\n";
    cout << "\nPress Enter to return to the menu...";
    cin.ignore();
    cin.get();
    system(CLEAR);
}

#endif

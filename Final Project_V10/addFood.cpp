#include "addFood.h"
#include <iostream> // cin, cout
#include <fstream> // ifstream, ofstream
#include <vector> // vector<string>, vector<double>, vector<int>
#include <string> // substr(), getline(), find(), npos , stod
#include <iomanip> // setw(), setprecision(), fixed, left, right
#include <cstdlib> // system("cls") 
using namespace std;

// Define the main feature function, tied to a specific user via username
void addFoodToList(const string& username) { 
    system("cls");                                            // clear the system

    // === SHOW EXISTING FOOD LIST FIRST ===
    ifstream showList(username + "_foodlist.txt");            // Open the user's food list file
    cout << "=== \033[36mYOUR FOOD LIST\033[0m ===\n";
    if (!showList.is_open()) {                                // if file can't be opened (DNE)
        cout << "(No foods added yet)\n";
    } else {
        string line;
        int index = 0;    
        cout << left << setw(5) << "No."
             << setw(25) << "Food Name"
             << right << setw(12) << "Calories"
             << setw(12) << "Protein(g)"
             << setw(12) << "Carbs(g)" << "\n";
        cout << string(65, '-') << "\n";

        while (getline(showList, line)) {               // Read the txt file line by line
            size_t p1 = line.find(",");                 // Read the 1st comma
            size_t p2 = line.find(",", p1 + 1);         // Read the 2nd comma 
            size_t p3 = line.find(",", p2 + 1);         // Read the 3rd comma
            if (p3 == string::npos) continue;  

            string name = line.substr(0, p1);                          // Extract food name
            double cal = stod(line.substr(p1 + 1, p2 - p1 - 1));       // Extract calories and convert string to double 
            double prot = stod(line.substr(p2 + 1, p3 - p2 - 1));      // Extract protein and convert string to double 
            double carb = stod(line.substr(p3 + 1));                   // Extract carbs and convert string to double 

            // print the food details
            cout << left << setw(5) << (++index)
                 << setw(25) << name
                 << right << setw(12) << fixed << setprecision(1) << cal
                 << setw(12) << fixed << setprecision(1) << prot
                 << setw(12) << fixed << setprecision(1) << carb
                 << "\n";
        }
        
        if (index == 0) {                        // if no lines were read, the list is empty
            cout << "(Your list is empty)\n";
        }
        showList.close();                        // close file
    }

    // === MENU SECTION ===
    cout << "\n=== \033[36mFOOD LIST MENU\033[0m ===\n";
    cout << "1. Choose from predefined foods\n";
    cout << "2. Add custom food manually\n";
    cout << "3. Mix existing foods to create a new one\n";
    cout << "4. Remove food from list\n";
    cout << "0. Go Back\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    // Prevent invalid input loop, if entering a non-numeric
    if (cin.fail()) {
        cin.clear();                                                        // clear the fail state
        cin.ignore(10000, '\n');                                            // discard invalid input
        system("cls");
        cout << "Invalid input! Please enter a number between (0-4).\n";    
        cout << "\nPress Enter to continue...";                            
        cin.ignore();                                                        // waiting for enter
        system("cls");
        return addFoodToList(username);                                      // return addFoodToList menu
    }

    string foodName;
    double calories = 0, protein = 0, carbs = 0;

    // go back to the main menu
    if (choice == 0) { 
        system("cls");
        return;
    }

    // === REMOVE FEATURE ===
    if (choice == 4) {
        system("cls");
        ifstream file(username + "_foodlist.txt");    
        if (!file.is_open()) {                            // open user file list
            cout << "No food list found.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return addFoodToList(username);                // back to menu
        }
        
        vector<string> foods;                            // store all foods lines
        string line;                                     // temp holder for reading lines
        while (getline(file, line)) {                    // read each line
            if (!line.empty()) foods.push_back(line);    // keep lines that are not empty
        }
        file.close();                                    // close file

        // if no items were saved, print the list is empty
        if (foods.empty()) {
            cout << "Your food list is empty.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return addFoodToList(username);            // back to menu
        }

        cout << "=== \033[36mREMOVE FOOD FROM LIST\033[0m ===\n";
        cout << left << setw(5) << "No."
             << setw(25) << "Food Name"
             << right << setw(12) << "Calories"
             << setw(12) << "Protein(g)"
             << setw(12) << "Carbs(g)" << "\n";
        cout << string(65, '-') << "\n";

        for (size_t i = 0; i < foods.size(); ++i) {        // loop through all the items
            size_t p1 = foods[i].find(",");
            size_t p2 = foods[i].find(",", p1 + 1);
            size_t p3 = foods[i].find(",", p2 + 1);
            if (p3 == string::npos) continue;              // skip if there is a malformed lines

            string name = foods[i].substr(0, p1);                           // analyze name 
            double cal = stod(foods[i].substr(p1 + 1, p2 - p1 - 1));        // analyze calories
            double prot = stod(foods[i].substr(p2 + 1, p3 - p2 - 1));       // analyze protien
            double carb = stod(foods[i].substr(p3 + 1));                    // analyze carbs

            cout << left << setw(5) << (i + 1)
                 << setw(25) << name
                 << right << setw(12) << fixed << setprecision(1) << cal
                 << setw(12) << fixed << setprecision(1) << prot
                 << setw(12) << fixed << setprecision(1) << carb
                 << "\n";
        }

        // prompt for removing a food from the index
        cout << "\nEnter number of food to remove (0 to cancel): ";
        int removeIndex;
        cin >> removeIndex;

        // validates input if it's non-numeric
        if (cin.fail() || removeIndex < 0 || removeIndex > (int)foods.size()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid input.\033[0m\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return addFoodToList(username);        // return to addFoodToList menu
        }
        // return to main menu of the program
        if (removeIndex == 0) {    
            system("cls");
            return addFoodToList(username);
        }

        foods.erase(foods.begin() + removeIndex - 1); // remove the selected food

        // open the file and remove the food inside of it
        ofstream out(username + "_foodlist.txt", ios::trunc);    
        for (const string& item : foods)
            out << item << "\n";
        out.close(); //close the file

        cout << "\n\033[32mFood successfully removed!\033[0m\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");                            
        return addFoodToList(username);            // return to addFoodToList menu
    }

    // === ADD PREDEFINED FOOD ===
    if (choice == 1) {
        // Load predefined foods
        ifstream predef("predefined_foods.txt");                // open the predefined food list file
        if (!predef) {                                          // if the file is missing
            cout << "No predefined food file found.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return;                                             // return to menu
        }

        vector<string> foods;                                    // Names of the food
        vector<double> cals, prots, carbsArr;                   // nutrition vector
        string line;                                            // temp line 

        while (getline(predef, line)) {                        // read each entry
            size_t p1 = line.find(",");
            size_t p2 = line.find(",", p1 + 1);
            size_t p3 = line.find(",", p2 + 1);
            if (p3 == string::npos) continue;                   //skip if malformed lines

            string name = line.substr(0, p1);                        
            double cal = stod(line.substr(p1 + 1, p2 - p1 - 1));
            double prot = stod(line.substr(p2 + 1, p3 - p2 - 1));
            double carb = stod(line.substr(p3 + 1));

            foods.push_back(name);                            // store the anaylze name,carb,prot,cals to the vectors
            cals.push_back(cal);
            prots.push_back(prot);
            carbsArr.push_back(carb);
        }
        predef.close();                                        // close predefined file

        if (foods.empty()) {                                   // if nothing is loaded, then print
            cout << "Predefined list is empty.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return;                                            //return to menu
        }

        // declaration for going into the next page
        int page = 0;
        const int perPage = 10;
        int totalPages = (foods.size() + perPage - 1) / perPage;
        string action;

        // looping for the page of the predefined foods
        while (true) {
            system("cls");

            cout << "\n=== \033[36mPREDEFINED FOOD LIST (Page " << page + 1 << " of " << totalPages << ")\033[0m ===\n\n";
            cout << left << setw(5) << "No."
                 << setw(25) << "Food Name"
                 << right << setw(12) << "Calories"
                 << setw(12) << "Protein(g)"
                 << setw(12) << "Carbs(g)" << "\n";
            cout << string(65, '-') << "\n";
            
            int start = page * perPage;                            // calculate the starting index
            int end = min((int)foods.size(), start + perPage);     // calculate the ending index
            for (int i = start; i < end; ++i) {                    // loop through the subset of foods corresponding to the page
                cout << left << setw(5) << (i + 1)
                     << setw(25) << foods[i]
                     << right << setw(12) << fixed << setprecision(1) << cals[i]
                     << setw(12) << fixed << setprecision(1) << prots[i]
                     << setw(12) << fixed << setprecision(1) << carbsArr[i]
                     << "\n";
            }

            cout << "\nEnter number to select food, N for next, P for previous, or Q to quit: ";
            cin >> action;
           
            if (action == "N" || action == "n") {     // next page
                if (page < totalPages - 1) page++;
            } else if (action == "P" || action == "p") {    // previous page
                if (page > 0) page--;
            } else if (action == "Q" || action == "q") {     // quit
                system("cls");
                return addFoodToList(username);             // return to addFoodToList menu
            } else {
                try {
                    int select = stoi(action);             // convert into integer
                    if (select >= 1 && select <= (int)foods.size()) {   // If the entered number corresponds to a valid food index
                        foodName = foods[select - 1];                     // Retrieve the selected food details from the stored vectors
                        calories = cals[select - 1];                       // and assign them to variables for later saving.
                        protein = prots[select - 1];
                        carbs = carbsArr[select - 1];
                        break;                                         // Exit the loop after a valid selection
                    } else {
                        cout << "\033[31mInvalid number.\033[0m\n";
                    }
                } catch (...) {                                           // the stoi() fails this catches the error and shows invalid input
                    cout << "\033[31mInvalid input.\033[0m\n";
                }
            }
        }
    }

    // === CUSTOM FOOD ===
    else if (choice == 2) {
        char confirm;
        system("cls");
        cin.ignore();
        cout << "=== \033[36mCUSTOM FOOD ADD\033[0m ===\n";
        cout << "Do you want to continue adding a custom food? (Y/N): ";
        cin >> confirm;

        if (confirm == 'N' || confirm == 'n') {
            system("cls");
            return addFoodToList(username);
        }

        cin.ignore();
        cout << "Enter food name: ";
        getline(cin, foodName);

        cout << "Calories: ";
        while (!(cin >> calories)) {                              // ask for calories and error validation
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid, Enter a number for calories: \033[0m";
        }

        cout << "Protein (g): ";
        while (!(cin >> protein)) {                                // ask for protein and error validation
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid, Enter a number for protein: \033[0m";
        }

        cout << "Carbs (g): ";                                    // ask for carbs and error validation
        while (!(cin >> carbs)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[31mInvalid, Enter a number for carbs: \033[0m";
        }

        cin.ignore();
        system("cls");
        cout << "\nCustom food added successfully!\n";                  // prints the details
        cout << left << setw(15) << "Food:" << foodName << "\n";
        cout << left << setw(15) << "Calories:" << fixed << setprecision(1) << calories << " kcal\n";
        cout << left << setw(15) << "Protein:" << fixed << setprecision(1) << protein << " g\n";
        cout << left << setw(15) << "Carbs:" << fixed << setprecision(1) << carbs << " g\n";
    }

    // === MIX FOODS ===
    else if (choice == 3) {
        system("cls");
        ifstream file(username + "_foodlist.txt");                        // open user's list
        if (!file) {
            cout << "No existing food list found. Add some foods first.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return;                                            // returm to menu
        }

        vector<string> foods;                                    //name
        vector<double> cals, prots, carbsArr;                    // nutrition data
        string line;                                             // temp for lines
        int index = 0;                                            // row counter

        cout << "\n=== \033[36mYOUR FOOD LIST\033[0m ===\n\n";
        cout << left << setw(5) << "No."
             << setw(25) << "Food Name"
             << right << setw(12) << "Calories"
             << setw(12) << "Protein(g)"
             << setw(12) << "Carbs(g)" << "\n";
        cout << string(65, '-') << "\n";

        while (getline(file, line)) {                                // read list
            size_t p1 = line.find(",");
            size_t p2 = line.find(",", p1 + 1);
            size_t p3 = line.find(",", p2 + 1);
            if (p3 == string::npos) continue;                        // skip malformed lines

            string name = line.substr(0, p1);                                //analyze cal,prot,carb
            double cal = stod(line.substr(p1 + 1, p2 - p1 - 1));
            double prot = stod(line.substr(p2 + 1, p3 - p2 - 1));
            double carb = stod(line.substr(p3 + 1));

            foods.push_back(name);                                       //store the data into the vectors
            cals.push_back(cal);
            prots.push_back(prot);
            carbsArr.push_back(carb);

            cout << left << setw(5) << (++index)                    // display the row of foods
                 << setw(25) << name
                 << right << setw(12) << fixed << setprecision(1) << cal
                 << setw(12) << fixed << setprecision(1) << prot
                 << setw(12) << fixed << setprecision(1) << carb
                 << "\n";
        }
        file.close();                                                     // close file

        if (index == 0) {                                                // if no entries
            cout << "\033[31mYour food list is empty.\033[0m\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return;                                                // return to menu
        }

        vector<int> selected;
        cout << "\nEnter food numbers to mix (separated by space), (0) to stop: ";

        int choiceNum;
        while (true) {
            cin >> choiceNum;
            if (cin.fail()) {                                  // validate if it's a numeric
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\033[31mInvalid input! Please enter valid numbers only.\033[0m\n";
                continue;
            }
            if (choiceNum == 0) break;                        // stop when 0 is entered
            if (choiceNum >= 1 && choiceNum <= index)        
                selected.push_back(choiceNum - 1);
            else
                cout << "\033[31mInvalid number. Try again.\033[0m\n";
        }

        if (selected.empty()) {                                // if none were chosen
            cout << "\033[31mNo foods selected.\033[0m\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            return;                                  // return to menu
        }

        for (int i : selected) {                    // sum nutrition of all selected
            calories += cals[i];
            protein += prots[i];
            carbs += carbsArr[i];
        }

        cin.ignore();
        cout << "\nEnter a name for your new mixed food: ";
        getline(cin, foodName);                                    

        system("cls");
        // display all the combined totals
        cout << "\nNew food '" << foodName << "' created! Total:\n";
        cout << left << setw(15) << "Calories:" << fixed << setprecision(1) << calories << " kcal\n";
        cout << left << setw(15) << "Protein:" << fixed << setprecision(1) << protein << " g\n";
        cout << left << setw(15) << "Carbs:" << fixed << setprecision(1) << carbs << " g\n";
    } else {
        cout << "\033[31mInvalid choice.\033[0m\n";
        return;
    }

    // === SAVE NEW FOOD ===
    ofstream file(username + "_foodlist.txt", ios::app);                                    // open user file
    if (file.is_open()) {                                                                   // if opened successfully
        file << foodName << "," << calories << "," << protein << "," << carbs << endl;      // write CSV line
        file.close();                                                                       // close line
        cout << "\nFood saved successfully!\n";
    } else {
        cout << "\033[31mError saving food list.\033[0m\n";                                // file open/write error
    }

    cout << "\nPress Enter to return to menu...";
    cin.get();
    system("cls");
}


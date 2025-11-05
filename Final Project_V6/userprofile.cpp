#include "userprofile.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib> // for system()
using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif


void createUserProfileFile(const string& username, const string& password, int age, double weight, double height,
                           const string& gender, double bmi, const string& bmiStatus, double bmr) {
    string filename = username + "_profile.txt";
    ofstream profileFile(filename);
    if (profileFile.is_open()) {
        profileFile << "=== USER PROFILE ===\n";
        profileFile << "Username: " << username << endl;
        profileFile << "Age: " << age << " years\n";
        profileFile << "Weight: " << weight << " kg\n";
        profileFile << "Height: " << height << " cm\n";
        profileFile << "Gender: " << gender << endl;
        profileFile << "BMI: " << fixed << setprecision(2) << bmi << " (" << bmiStatus << ")\n";
        profileFile << "BMR (Calories Needed): " << fixed << setprecision(2) << bmr << " kcal/day\n";
        profileFile.close();
        
    } else {
        cerr << "Error: Could not create profile file for " << username << ".\n";
    }
}

void displayUserProfile(const string& username) {
	system(CLEAR);
    string filename = username + "_profile.txt";
    ifstream profileFile(filename);
    if (profileFile.is_open()) {
        cout << "\n";
        string line;
        while (getline(profileFile, line)) {
            cout << line << endl;
        }
        profileFile.close();
    } else {
        cout << "Profile file not found for user '" << username << "'.\n";
    }
        cout << "\n\n";
		cout << "\033[1;37m" << "Press Enter to return to the main menu...";
   		cout << "\033[0m";
    	cin.ignore();
    	cin.get(); // Wait for Enter
    
    	system(CLEAR);
}



#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

string getCurrentDate(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    //format
    return to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-" + 
                    (day < 10 ? "0" : "") + to_string(day);
    return date;
}

//check goal
bool checkGoal(double totalCalories, double goalCalories, double totalProtein, 
    double goalProtein, double goalFats,double totalFats, double goalCarbohydrates, 
    double totalCarbohydrates) {
    return (totalCalories >= goalCalories) && (totalProtein >= goalProtein) &&
        (totalFats >= goalFats) && (totalCarbohydrates >= goalCarbohydrates);
}

int countGoalsMet(string filename){
    ifstream file(filename);
    string line;
    int count = 0;

    while (getline(file, line)) {
        if (line.find("?") != string::npos) {
            count++;
        }
    }
    
    file.close();
    return count; 
}

int getLastLoggedDate(string username){
    string filename = username + "_report.txt";
    ifstream file(filename);
    string line;
    string lastDate = "";

    while (getline(file, line)) {
        if (line.find("Date: ") != string::npos) {
            lastDate = line.substr(6);
        }
    }
    
    file.close();
    return lastDate;
}

void resetWeeklyReport(string username) {
    string filename = username + "_report.txt";
    ofstream file(filename, ios::trunc);
    file << "=========================================\n";
    file << "      ?? NEW WEEKLY REPORT STARTED\n";
    file << "=========================================\n\n";
    file.close();
    cout << "?? Weekly report reset for new week!\n";

void generateDailyReport(string username, int day,
                         double totalCalories, double goalCalories,
                         double totalProtein, double goalProtein,
                         double totalFats, double goalFats,
                         double totalCarbs, double goalCarbs) {
    bool goalMet = checkGoal(totalCalories, goalCalories,
                             totalProtein, goalProtein,
                             totalFats, goalFats,
                             totalCarbs, goalCarbs);

    string date = getCurrentDate();
    string filename = username + "_report.txt";

    ofstream file(filename, ios::app);
    if (!file) {
        cout << "? Error: Unable to open report file!\n";
        return;
    }

    file << "-----------------------------------------\n";
    file << "Date: " << date << " (Day " << day << " of 7)\n";
    file << (goalMet ? "? Goal Met\n" : "? Missed Goal\n");
    file << "Calories: " << totalCalories << " / " << goalCalories << " kcal\n";
    file << "Protein : " << totalProtein << " / " << goalProtein << " g\n";
    file << "Fats    : " << totalFats << " / " << goalFats << " g\n";
    file << "Carbs   : " << totalCarbs << " / " << goalCarbs << " g\n";
    file << "-----------------------------------------\n\n";

    file.close();

    cout << "? Day " << day << " report saved successfully (" 
         << (goalMet ? "Goal Met" : "Missed") << ").\n";
}

void showWeeklySummary(string username) {
    string filename = username + "_report.txt";
    int totalMet = countGoalsMet(filename);

    cout << "\n=========================================\n";
    cout << "           ?? WEEKLY SUMMARY CHECKLIST     \n";
    cout << "=========================================\n";

    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.find("Day ") != string::npos || 
            line.find("?") != string::npos || 
            line.find("?") != string::npos) {
            cout << line << endl;
        }
    }
    file.close();

    cout << "\n=========================================\n";
    cout << "Goals Met: " << totalMet << " / 7\n";

    if (totalMet == 7)
        cout << "?? Perfect week! You nailed every goal!\n";
    else if (totalMet >= 4)
        cout << "?? Nice! You met most of your goals.\n";
    else
        cout << "?? Try harder next week, you’ve got this!\n";

    cout << "=========================================\n";
}

void logOutAndGenerateReport(string username,
                             double totalCalories, double goalCalories,
                             double totalProtein, double goalProtein,
                             double totalFats, double goalFats,
                             double totalCarbs, double goalCarbs) {
    int currentDay = getCurrentDay(username);

    // Reset report when new week starts
    if (currentDay == 1) {
        resetWeeklyReport(username);
    }

    // Record today's progress
    generateDailyReport(username, currentDay,
                        totalCalories, goalCalories,
                        totalProtein, goalProtein,
                        totalFats, goalFats,
                        totalCarbs, goalCarbs);

    // Show weekly summary at the end of day 7
    if (currentDay == 7) {
        showWeeklySummary(username);
        resetWeeklyReport(username);
    }
}

#endif

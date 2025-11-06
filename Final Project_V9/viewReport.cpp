#include "viewReport.h"
#include "dietoption.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void viewReport(const string& username, double bmr) {

 	system("cls");
 	
    cout << "\n=== \033[36mDAILY REPORT\033[0m ===\n";

    ifstream logFile(username + "_foodlog.txt");
    if (!logFile.is_open()) {
        cout << "\033[31mNo food logs found for today.\033[0m\n";
        cout << "\nPress Enter to go back...";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }

    string line, date, food;
    double cal, prot, carb;
    int qty;

    // Match your log date format (no leading zeros)
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string today = to_string(1900 + ltm->tm_year) + "-" +
                   to_string(1 + ltm->tm_mon) + "-" +
                   to_string(ltm->tm_mday);

    double totalCal = 0, totalProt = 0, totalCarb = 0;
    bool hasLogs = false;

    while (getline(logFile, line)) {
        stringstream ss(line);
        getline(ss, date, ',');
        getline(ss, food, ',');
        ss >> cal;
        ss.ignore();
        ss >> prot;
        ss.ignore();
        ss >> carb;
        ss.ignore();
        ss >> qty;

        // Trim spaces manually
        string trimmedDate = "";
        for (char c : date) {
            if (!isspace(static_cast<unsigned char>(c)))
                trimmedDate += c;
        }
        date = trimmedDate;

        if (date == today) {
            hasLogs = true;
            cout << "- " << food << " " << qty << "x: "
                 << cal << " kcal, " << prot << "g protein, "
                 << carb << "g carbs\n";

            totalCal += cal;
            totalProt += prot;
            totalCarb += carb;
        }
    }
    logFile.close();

    if (!hasLogs) {
        cout << "\033[31m\nNo logs found for today (" << today << ").\033[0m\n";
        cout << "\nPress Enter to go back...";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }

    double adjustedBMR = getAdjustedBMR(username, bmr);

    cout << fixed << setprecision(2);
    cout << "\n=== \033[36mTOTALS FOR TODAY\033[0m ===\n";
    cout << "Date: " << today << endl;
    cout << "Calories: " << totalCal << " kcal\n";
    cout << "Protein:  " << totalProt << " g\n";
    cout << "Carbs:    " << totalCarb << " g\n";
    cout << "BMR (Goal): " << adjustedBMR << " kcal/day\n\n";

    // ==================== CLEAN ASCII PROGRESS BAR ====================
    double progress = (adjustedBMR > 0) ? (totalCal / adjustedBMR) : 0;
    if (progress > 1.5) progress = 1.5; // cap display at 150%

    int barWidth = 40;
    int filled = static_cast<int>(barWidth * (progress < 1.0 ? progress : 1.0));

    string color;
    if (totalCal < adjustedBMR * 0.8)
        color = "\033[33m"; // Yellow (below goal)
    else if (totalCal > adjustedBMR * 1.1)
        color = "\033[31m"; // Red (above goal)
    else
        color = "\033[32m"; // Green (goal met)

    cout << "   " << color << "[";
    for (int i = 0; i < barWidth; ++i)
        cout << (i < filled ? "=" : " ");
    cout << "] " << fixed << setprecision(1)
         << (progress * 100) << "% of goal\033[0m\n";

    // ==================== STATUS MESSAGE ====================
    cout << "\n";
    if (totalCal == 0)
        cout << "\033[31mNo foods logged today.\033[0m\n";
    else if (totalCal < adjustedBMR)
        cout << "You are below your calorie goal.\n";
    else if (totalCal >= adjustedBMR + 200)
        cout << "You exceeded your calorie goal.\n";
    else
        cout << "You reached your calorie goal.\n";

    cout << "\nPress Enter to go back...";
    cin.ignore();
    cin.get();
    system("cls");
}

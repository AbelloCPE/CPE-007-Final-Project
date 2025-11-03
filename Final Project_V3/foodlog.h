#ifndef FOODLOG_H
#define FOODLOG_H

#include <string>
using namespace std;

void addFoodToList(const string& username);
void logFood(const string& username);
void viewReport(const string& username, double bmr);

#endif

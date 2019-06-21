/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
DisplayableMonth.cpp: Defines functions for a DisplayableMonth object (i.e. displaying a day, adding a child to day, etc)
*/

#include "stdafx.h"
#include "DisplayableMonth.h"
#include "DisplayableDay.h"
#include "MonthDisplay.h"
#include <iostream>
#include <iomanip>

using namespace std;

DisplayableMonth::DisplayableMonth(std::tm d, std::shared_ptr<DisplayableComponent> p, string monthname, unsigned int numdays) : CalendarComponent(d, p), name(monthname), numberOfDays(numdays) {
	// initialize children vector, one spot for each day
	for (size_t i = 0; i < numberOfDays; ++i) {
		children.push_back(nullptr);
	}
}

//displays all months and their children 
void DisplayableMonth::displayAll() {
	cout << "\t\t" << name << ":" << endl;
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) { // forward request to all children
			children[i]->displayAll();
		}
	}
}

//updates display when month is the top level object being displayed 
void DisplayableMonth::displayObject() {

	cout << "Sunday     " << "Monday     " << "Tuesday    " << "Wednesday  " << "Thursday   " << "Friday     " << "Saturday   " << endl;

	int index = 0;

	string sun = "Sunday";
	string mon = "Monday";
	string tues = "Tuesday";
	string wends = "Wednesday";
	string thurs = "Thursday";
	string fri = "Friday";
	string sat = "Saturday";

	//update index depending on what day is the first day of the week 
	if (this->daysoftheweek[dateInfo.tm_wday] == sun)
	{
		index = DayOne;
	}
	else if (this->daysoftheweek[dateInfo.tm_wday] == mon)
	{
		index = DayTwo;
	}
	else if (this->daysoftheweek[dateInfo.tm_wday] == tues)
	{
		index = DayThree;
	}
	else if (this->daysoftheweek[dateInfo.tm_wday] == wends)
	{
		index = DayFour;
	}
	else if (this->daysoftheweek[dateInfo.tm_wday] == thurs)
	{
		index = DayFive;
	}
	else if (this->daysoftheweek[dateInfo.tm_wday] == fri)
	{
		index = DaySix;
	}
	else if (this->daysoftheweek[dateInfo.tm_wday] == sat)
	{
		index = DaySeven;
	}

	//add appropriate space between first day depending on start index
	for (int j = 0; j < index; ++j)
	{
		cout << "           ";
	}

	//display days on new line once index reaches 7 (i.e. the day is on a saturday)
	for (int i = 0; i < numberOfDays; ++i)
	{
		index++;
		children[i]->displayAll();
		if (index % 7 == 0)
		{
			cout << "\n";
		}
	}
	cout << endl;

}

//forward request to months children to display a day and its respsective events 
void DisplayableMonth::displayEvents() {
	cout << " " << name << endl;
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->displayEvents();
		}
	}
}

//forward request to children to store events in file 
void DisplayableMonth::writeToFile(std::string cal_name, std::string file_name)
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->writeToFile(cal_name, file_name);
		}
	}
}

//forward request to children to remove all events from calendar
void DisplayableMonth::removeEvents()
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->removeEvents();
		}
	}
}

//add component to a month 
shared_ptr<DisplayableComponent> DisplayableMonth::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableDay* d = dynamic_cast<DisplayableDay *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (d == nullptr) { // the cast failed
		return nullptr;
	}

	// otherwise, add the day to the correct location
	int dayOfMonth = d->dateInfo.tm_mday - 1;
	if (children[dayOfMonth] == nullptr) { // day does not already exist
		children[dayOfMonth] = comp;
		return comp;
	}
	else {  // day already exist, return existing day
		return children[dayOfMonth];
	}
}

vector<std::shared_ptr<DisplayableComponent>> DisplayableMonth::search(string query)
{
	cout << "Testing search function" << endl;
	vector<std::shared_ptr<DisplayableComponent>> test;
	return test;
}

void DisplayableMonth::markComplete(unsigned int x) {}
void DisplayableMonth::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) {}

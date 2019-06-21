/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
DisplayableYear.cpp: Defines functions for a DisplayableYear object (i.e.displaying a day, adding a child to day, etc)
*/

#include "stdafx.h"
#include "DisplayableYear.h"
#include <iostream>
#include "DisplayableMonth.h"
#include <fstream>

using namespace std;

DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l) {
	for (size_t i = 0; i < CalendarComponent::MONTHS; ++i) 
	{
		children.push_back(nullptr);
	}
}

//displays years and and forwards request to children
void DisplayableYear::displayAll() 
{
	cout << "\tYear " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
	for (size_t i = 0; i < children.size(); ++i) { 
		if (children[i] != nullptr) {
			children[i]->displayAll();
		}
	}
}

//update display when year is the top level object being displayed
void DisplayableYear::displayObject() 
{
	cout << endl;
	cout << "Year " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;

	//display each year and its index and forward request to children
	for (size_t i = 0; i < children.size(); ++i) { 
		cout << i;
		children[i]->displayEvents();
	}
	cout << endl;
}

//forward request to children to write all events to file 
void DisplayableYear::writeToFile(std::string cal_name, std::string file_name)
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
void DisplayableYear::removeEvents()
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->removeEvents();
		}
	}
}

//add component to year 
shared_ptr<DisplayableComponent> DisplayableYear::addComponent(shared_ptr<DisplayableComponent> comp) 
{
	// try to dynamically cast comp to a pointer to a DisplayableMonth
	DisplayableMonth * m = dynamic_cast<DisplayableMonth *>(comp.get());
	if (m == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	// otherwise, add the month to the correct location
	int monthOfYear = m->dateInfo.tm_mon;
	if (children[monthOfYear] == nullptr) { // month does not already exist
		children[monthOfYear] = comp;
		return comp;
	}
	else {  // month already exist, return existing month
		return children[monthOfYear];
	}
}

vector<std::shared_ptr<DisplayableComponent>> DisplayableYear::search(string query)
{
	vector<std::shared_ptr<DisplayableComponent>> test;
	return test;
}

void DisplayableYear::markComplete(unsigned int x) {}
void DisplayableYear::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) {}
void DisplayableYear::displayEvents() {}



/*
Camilla Moraes - camillamoraes@wustl.edu (Some of this written by Jon Shidal and provided as starter code) 
Lab 5
Calendar.cpp: defines functions declared in Calendar class responsible for displaying the calendar and 
handling any requests that must be forwarded to its children. 
*/

#include "stdafx.h"
#include "Calendar.h"
#include "DisplayableYear.h"
#include "Event.h"
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

// Calendar
Calendar::Calendar(string n, size_t y) : CalendarComponent(tm(), nullptr), name(n), yearsToHold(y) { // just initialize with a default tm for now.
	time_t now = time(0); // get the current time
	tm now_tm;
	localtime_s(&now_tm, &now); // create a struct tm(now_tm) from the current time
	currentDate = now_tm;    // set Calendar's date and time to now
	dateInfo = now_tm; // setup dateInfo to represent January 1st of the current year, start time of the calendar
	dateInfo.tm_sec = 0;
	dateInfo.tm_min = 0;
	dateInfo.tm_hour = 0;
	dateInfo.tm_mday = 1;
	dateInfo.tm_mon = 0;
	// calculate and set day of the week to that of January 1st of the current year. Very sloppy, I know...
	dateInfo.tm_wday = (now_tm.tm_wday + CalendarComponent::DAYSINAWEEK - (now_tm.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK;
	dateInfo.tm_yday = 0;
	dateInfo.tm_isdst = 0;
	// intialize calendar to hold __ years
	for (size_t i = 0; i < yearsToHold; ++i) {
		children.push_back(nullptr);
	}
}

//display calendar by forwarding request to its children
void Calendar::displayAll() {
	for (size_t i = 0; i < children.size(); ++i) { 
		if (children[i] != nullptr) {
			children[i]->displayAll();
		}
	}
}

//displays calendar years when the current display is the Calendar object
void Calendar::displayObject() 
{
	//number of years in current calendar
	int num_years = 3;


	int start_year = CalendarComponent::BASEYEAR;
	for (int i = 0; i < num_years; ++i)
	{
		cout << i << " " << dateInfo.tm_year + start_year << endl;
		start_year++;
	}
}

//
void Calendar::displayEvents() {
	cout << " " << name << endl;
}

//function to add children to calendar
shared_ptr<DisplayableComponent> Calendar::addComponent(std::shared_ptr<DisplayableComponent> comp) {
	DisplayableYear* y = dynamic_cast<DisplayableYear *>(comp.get());
	if (y == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	unsigned int calendarYear = CalendarComponent::BASEYEAR + dateInfo.tm_year;
	unsigned int yearAdding = CalendarComponent::BASEYEAR + y->dateInfo.tm_year;
	unsigned int index = yearAdding - calendarYear; // which child?
	if (index >= 0 && index < children.size() && children[index] == nullptr) {
		children[index] = comp;
		return comp;
	}
	else {
		return nullptr;
	}
}

//search for event based on its name and returns a vector of results
vector<std::shared_ptr<DisplayableComponent>> Calendar::search(string query)
{
	//create a vector to store search results
	vector<std::shared_ptr<DisplayableComponent>> events;

	//iterate through multimap storing events and check if multimap key matches query 
	for (multimap<string, std::shared_ptr<DisplayableComponent>>::iterator it = event_map.begin(); it != event_map.end(); ++it)
	{
		//if query matches key add event to vector
		if ((*it).first == query)
		{
			events.push_back((*it).second);
		}
		//if no results are found
		else
		{
			break;
		}
	}

	return events;

}

//forward request to calendar's children to store current calendar in a file 
void Calendar::writeToFile(std::string cal_name, std::string file_name)
{
	cout << "Calendar successfuly stored in file" << endl;

	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->writeToFile(cal_name, file_name);
		}
	}

}

//iterates through entire vector of children and removes all children
void Calendar::removeEvents()
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->removeEvents();
		}
	}

}

void Calendar::markComplete(unsigned int x) {}
void Calendar::editDisplay(std::shared_ptr<DisplayableComponent> d, string cal_name) {}

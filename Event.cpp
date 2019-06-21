/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
Event.cpp: Defines functions for an Event object (i.e.displaying a day, adding a child to day, etc)
*/

#include "stdafx.h"
#include "DisplayableDay.h"
#include "CalendarComponent.h"
#include "CalendarBuilder.h"
#include "Event.h"
#include "CalendarInfo.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

Event::Event(std::shared_ptr<DisplayableComponent> cal, string name, std::tm when, int recurrEvery, int recurrFor) : CalendarComponent(when, cal), name(name), recurrEvery(recurrEvery), recurrFor(recurrFor) { }

//displays an event when DisplayableDay is top level object being displayed
void Event::displayAll() {

	cout << "\t" << name << ": " << dateInfo.tm_mon + MonthIndex << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR
		<< " " << dateInfo.tm_hour << ":" << dateInfo.tm_min << endl;
}

//display an event when Event is the top level object being displayed 
void Event::displayObject() 
{
	//display event 
	cout << name << ": " << dateInfo.tm_mon + MonthIndex << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + 1900
	<< " " << dateInfo.tm_hour << ":" << dateInfo.tm_min << endl;

	cout << endl;

	cout << "What you like to edit or delete this event?" << endl;

	cout << endl;
}

//display event when DisplayableDay is the top level object being displayed
void Event::displayEvents()
{
	cout << name << ": " << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + 1900
		<< " " << dateInfo.tm_hour << ":" << dateInfo.tm_min << endl;
}

//write event information to file 
void Event::writeToFile(std::string cal_name, std::string file_name)
{
	ofstream file;

	//append mode to write to end of file (prevents from overwriting content)
	file.open(file_name, std::ios::app);

	file << name << " " << dateInfo.tm_mday << " " << dateInfo.tm_mon << " " << dateInfo.tm_year << " " << dateInfo.tm_hour << " "
		<< dateInfo.tm_min << " " << 0 << " " << 0 << endl;

	file.close();

}

vector<std::shared_ptr<DisplayableComponent>> Event::search(string query)
{
	vector<std::shared_ptr<DisplayableComponent>> test;
	return test;
}

void Event::markComplete(unsigned int x) {}
void Event::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) {}
void Event::removeEvents() {}



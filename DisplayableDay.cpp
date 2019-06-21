/*
Camilla Moraes - camillamoraes@wustl.edu 
Lab 5 
DisplayableDay.cpp: Defines functions for a DisplayableDay object (i.e. displaying a day, adding a child to day, etc)
*/

#include "stdafx.h"
#include "DisplayableDay.h"
#include "FullCalendarBuilder.h"
#include "Event.h"
#include "utilityfunctions.h"
#include "MergeDecorator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <fstream>

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p)
{ 
	//initialize each day with an empty vector that can be filled with events if necessary
	children.push_back(nullptr);
}

//display function called when month is top level object being displayed
void DisplayableDay::displayAll() 
{
	int max_width = 11;
	int last_single_digit = 9;
	int double_digit_width = 12;

	//set width between days that have no events
	if (num_events.find(this) == num_events.end())
	{
		//add a space when transitioning from single digit to double digit numbers
		if (dateInfo.tm_mday == last_single_digit)
		{
			cout << dateInfo.tm_mday << setw(double_digit_width);
		}
		else
		{
			cout << dateInfo.tm_mday << setw(max_width);
		}
	}
	else
	{
		cout << dateInfo.tm_mday;
		for (int i = 0; i < num_events.find(this)->second; ++i)
		{
			int max_events = 9;
			//add "*" to day to represent number of events day has (if day has >= 10 events, stop adding stars to maintain a good display)
			if (num_events.find(this)->second < max_events)
			{
				cout << "*";
			}
		}
		//update width between days depending on how many events day has 
		cout << setw(max_width - num_events.find(this)->second);
	}
}

//display function that is called when day is top level object being displayed
void DisplayableDay::displayObject() 
{
	cout << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday  << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) { // forward request to all children
			children[i]->displayEvents();
		}
	}
}

//forward request to children to write events to file 
void DisplayableDay::writeToFile(std::string cal_name, std::string file_name)
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->writeToFile(cal_name, file_name);
		}
	}
}

//remove all events from day 
void DisplayableDay::removeEvents()
{

	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			this->removeComponent(i);
		}
	}

}

//override remove component function ro remove event from days vector of children 
std::shared_ptr<DisplayableComponent> DisplayableDay::removeComponent(unsigned int index)
{
	//check if num_events has a key that is the current DisplayableDay object
	if (num_events.find(this) == num_events.end())
	{
		//do nothing
	}
	else
	{
		//remove number of events day has in num_events map (gets rid of *s in month display) 
		if (num_events.find(this)->second >= 1)
		{
			num_events.find(this)->second--;
		}
	}

	if (index < children.size()) { // leaf objects will have size of 0
		shared_ptr<DisplayableComponent> removed = children[index];
		children.erase(children.begin() + index);
		return removed; // pointer to the removed component if successful
	}

	return nullptr; // nullptr is remove fails
}

//display all events in a day
void DisplayableDay::displayEvents() 
{

	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) { // forward request to all children
			children[i]->displayAll();
		}
	}

}

//allocate a MergeDecorator object and forward request to event being decorated
void DisplayableDay::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name)
{

	for (unsigned int i = 0; i < children.size(); ++i)
	{
		if (children[i] == d)
		{
			//get pointer to given event to decorate
			std::shared_ptr<DisplayableComponent> comp = getChild(i);

			if (comp != nullptr)
			{
				//dynamically allocate new MergeDecorator object
				std::shared_ptr<DisplayableComponentDecorator> comp_dec = make_shared<MergeDecorator>(comp);

				//update vector
				children.at(i) = comp_dec;

				comp_dec->editDisplay(d, cal_name);
			}
	
		}
	}

}

//add component to day 
shared_ptr<DisplayableComponent> DisplayableDay::addComponent(shared_ptr<DisplayableComponent> comp) {
	
	// try to dynamically cast comp to a pointer to a Event, will fail if the DisplayableComponent is not an event
	Event* e = dynamic_cast<Event *>(comp.get()); // can only cast regular pointers, not shared_ptrs

	//increment days number of events 
	if (num_events.find(this) == num_events.end())
	{
		num_events.insert(pair<DisplayableDay*, int>(this, 1));
	}
	else
	{
		if (num_events.count(this) > 0)
		{
			num_events.find(this)->second++;
		}
	}

	// the cast failed
	if (e == nullptr) { 
		return nullptr;
	}

	int first_pos = 0;
	
	//if vector is empty (no children)
	if (children[first_pos] == nullptr)
	{
		//add event to first spot in vector
		children[first_pos] = comp;
		return comp; 
	}
	else
	{
		//add empty space to vector
		children.push_back(nullptr);

		//add event at end of vector
		children[children.size() - 1] = comp;

		//sort children from earliest to latest 
		std::sort(children.begin(), children.end(), event_compare);

		return comp; 
	}
}

vector<std::shared_ptr<DisplayableComponent>> DisplayableDay::search(std::string query)
{
	vector<std::shared_ptr<DisplayableComponent>> test;
	return test;
}

void DisplayableDay::markComplete(unsigned int x) {}
void DisplayableDay::editEvent(int index) {}

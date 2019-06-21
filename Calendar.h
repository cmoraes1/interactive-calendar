#pragma once

/*
Author: Jon Shidal
Lab 5
Calendar.h: declare the Calendar class, which inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent. Calendar.h has member variables with information about the calendar, such as
the number of years in holds, its name, and the current date.
*/

#include "CalendarComponent.h"
#include <string>
#include <vector>
#include <map>

// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;

class Calendar : public CalendarComponent {
	// friends
	friend FullCalendarBuilder;
	friend CalendarInterface;
protected:
	std::string name;
	size_t yearsToHold;
	std::tm currentDate; // current date and time
						 // dateInfo is the start date and time

						 // Calendar contains years, so override accordingly
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
public:
	// arguments: name of the calendar, length of the calendar in years
	Calendar(std::string n, size_t y);
	// inherited methods
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual void markComplete(unsigned int x) override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
	//map that associates month indices with the number of days in that month
	std::map<int, int> mon_days = { std::pair<int, int>(0, 31), std::pair<int, int>(1, 28), std::pair<int, int>(2, 31),
		std::pair<int, int>(3, 30), std::pair<int, int>(4, 31), std::pair<int, int>(5, 30), std::pair<int, int>(6, 31),
		std::pair<int, int>(7, 31), std::pair<int, int>(8, 30), std::pair<int, int>(9, 31), std::pair<int, int>(10, 30),
		std::pair<int, int>(11, 31) };
};
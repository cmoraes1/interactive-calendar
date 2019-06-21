#pragma once
/*
Author: Jon Shidal
Purpose:
This file contains the declaration for a calendar component. The main purpose of CalendarComponent is to add date/time information to
the DisplayableComponent class. All components in the Calendar will derive publicly from this class. The date/time infor is stored as a variable of type
struct tm. Please see the layout of the tm struct below. This class also declares some useful constants for the Calendar
*/
#include "DisplayableComponent.h"
#include<ctime>
#include<string>
#include <vector>

/*
here is the layout of the tm struct, it is declared in <ctime> header file
struct tm {
int tm_sec;   // seconds of minutes from 0 to 61
int tm_min;   // minutes of hour from 0 to 59
int tm_hour;  // hours of day from 0 to 24
int tm_mday;  // day of month from 1 to 31
int tm_mon;   // month of year from 0 to 11
int tm_year;  // year since 1900
int tm_wday;  // days since sunday
int tm_yday;  // days since January 1st
int tm_isdst; // hours of daylight savings time
}
*/

// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;

class CalendarComponent : public DisplayableComponent {
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	// inherited
	virtual void displayAll() = 0;
	virtual void displayObject() = 0;
	virtual void displayEvents() = 0;
	virtual void writeToFile(std::string cal_name, std::string file_name) = 0;
	virtual void removeEvents() = 0;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) = 0;
	virtual void markComplete(unsigned int x) = 0;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) = 0;
protected:
	// stores date/time associated with this component
	// see struct tm details above. This will always be set to the date/time at the beginning of the component. So for a month, it is set to the first day of the month
	// For a year, it is set to the first day of the year, etc...
	std::tm dateInfo;

	// constructor, protected is ok. Builder class is a friend
	CalendarComponent(std::tm, std::shared_ptr<DisplayableComponent>);

	// some static constants to use in place of hardcoded calendar values
	static const std::vector<std::string> daysoftheweek;
	static const std::vector<std::string> months;
	static const std::vector<int> days;
	static const unsigned int DAYSINAWEEK;
	static const unsigned int MONTHS;
	static const unsigned int BASEYEAR;
	static const unsigned int DAYSINAYEAR;
};

/*
Author: Jon Shidal
Purpose: declare the user interface for our calendar
*/
#pragma once
#include "CalendarBuilder.h"
#include "CalendarComponent.h"
//#include "Event.h"
#include<memory>
#include <vector>


class CalendarInterface {
	std::shared_ptr<Calendar> cal; // the calendar
	std::shared_ptr<CalendarBuilder> builder; // builder for managing construction of the calendar
	std::shared_ptr<DisplayableComponent> currentDisplay; // which component the user is currently viewing
public:
	// constructor
	// arguments: 1 - what type of builder? 2 - how many years to hold? 
	CalendarInterface(std::string builderType, std::string calendarName, size_t years);

	// calendar traversal functions
	void zoomIn(unsigned int index); // zoom in on a child of the current_display
	void zoomOut(); // zoom out to the parent of the current_display
	void run(); // display the current view to the user and prompt for input
	void todo(); //display to do list to user
};
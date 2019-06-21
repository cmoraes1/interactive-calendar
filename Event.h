#pragma once

/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
Event.h: declare the Event class, which inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent. An Event is a leaf class and can be a child of a DisplayableDay object.
*/

#include "CalendarComponent.h"
#include "DisplayableDay.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>

// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableDay;
class DisplayableComponent;

class Event : public CalendarComponent {
	friend class DisplayableDay;
	friend FullCalendarBuilder;
	friend CalendarInterface;
	friend DisplayableComponent;
protected:
	std::string name;
	tm when;
	int recurrEvery;
	int recurrFor;
public:
	//1st arg: parent, 2nd arg: event name, 3rd arg: event date/time: 4th arg: recurr every __ days, 5th arg: recurr for ___ days
	Event(std::shared_ptr<DisplayableComponent> comp, std::string name, tm when, int recurrEvery, int recurrFor);
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
	friend bool event_compare(std::shared_ptr<DisplayableComponent> one, std::shared_ptr<DisplayableComponent> two);
};




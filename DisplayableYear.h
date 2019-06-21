#pragma once
/*
Author: Jon Shidal
Purpose: declare the DisplayableYear class. This class may be a component of a calendar. It inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent
*/

#include "CalendarComponent.h"
#include <vector>
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class Calendar;

class DisplayableYear : public CalendarComponent {
	friend Calendar;
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	// arguments: date/time info, parent, leap year or no?
	DisplayableYear(std::tm, std::shared_ptr<DisplayableComponent>, bool);
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
protected:
	bool leap;
	// year contains months - override accordingly
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
};
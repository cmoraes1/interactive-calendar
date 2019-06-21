#pragma once
/*
Author: Jon Shidal
Purpose: declare the DisplayableMonth class. This class may be a component of a calendar. It inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent
*/

#include "CalendarComponent.h"
#include <vector>
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableYear;

class DisplayableMonth : public CalendarComponent {
	friend class DisplayableYear;
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	// arguments = date/time info, its parent, name of the month, days in the month
	DisplayableMonth(std::tm, std::shared_ptr<DisplayableComponent>, std::string monthname, unsigned int numdays);
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
protected:
	std::string name;
	unsigned int numberOfDays;
	// Month contains days, so it is a composite object. override addComponent accordingly
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
};
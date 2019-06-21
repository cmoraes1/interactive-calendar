#pragma once
/*
Author: Jon Shidal
Purpose: declare the DisplayableDay class. This class may be a component of a calendar. It inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent
*/

#include "CalendarComponent.h"
#include <vector>
#include <map>
#include <memory>
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableMonth;

class DisplayableDay : public CalendarComponent {
	friend class DisplayableMonth;
	friend FullCalendarBuilder;
	friend CalendarInterface;
public:
	//maps day to its event count 
	std::multimap < DisplayableDay*, int> num_events;
	// 1st argument = start date/timeof the day, 2nd argument = its parent
	DisplayableDay(std::tm, std::shared_ptr<DisplayableComponent>);
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void displayEvents() override;
	virtual void editEvent(int index);
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;

	//Days contains events, so it is a composite object. override addComponent accordingly
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
	virtual std::shared_ptr<DisplayableComponent> removeComponent(unsigned int) override;
};
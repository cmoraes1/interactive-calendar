#pragma once
/*
Author: Jon Shidal
Purpose: Declare FullCalendarBuilder, a concrete class that derives from CalendarBuilder,
which builds all components of the calendar at once.
*/

#include "CalendarBuilder.h"
#include "Event.h"
#include<vector>

// Concrete builder class
// builds a full calendar, all at once
class FullCalendarBuilder : public CalendarBuilder {
public:
	friend DisplayableDay;

	virtual std::shared_ptr<DisplayableComponent> buildEvent(std::shared_ptr<DisplayableComponent>, std::string name, std::tm when, int recurrEvery, int recurrFor) override;
	virtual std::shared_ptr<DisplayableComponent> getComponentByDate(std::shared_ptr<DisplayableComponent> cal, std::tm d, std::string granularity) override;
	virtual std::shared_ptr<Calendar> buildCalendar(std::string name, size_t years) override;
protected:
	virtual std::shared_ptr<DisplayableComponent> buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
};

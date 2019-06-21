/*
Author: Jon Shidal
Purpose: Define full calendar builder class, responsible for building and managing the structure of the calendar
*/

#include "stdafx.h"
#include "FullCalendarBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableDay.h"
#include "DisplayableMonth.h"
#include "DisplayableYear.h"
#include "utilityfunctions.h"
#include "MergeDecorator.h"
#include "CalendarInfo.h"
#include "Event.h"
#include <iostream>

using namespace std;

shared_ptr<Calendar> FullCalendarBuilder::buildCalendar(string name, size_t years) {
	currentCalendar = make_shared<Calendar>(name, years);
	// construct each year in a recursive way, add each year as a child of the calendar
	for (unsigned int i = 0; i < years; ++i) {
		tm y = currentCalendar->dateInfo;
		y.tm_year += i;
		y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR * i) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
		currentCalendar->addComponent(buildYear(y, currentCalendar));
	}
	return currentCalendar;
}

//builds an event and adds it as the child of a day 
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildEvent(shared_ptr<DisplayableComponent> cal, string name, tm when, int recurrEvery, int recurrFor) 
{

	//get day object and set events date info to be that of the day object 
	shared_ptr<DisplayableComponent> day = getComponentByDate(cal, when, "day");

	DisplayableDay * d = dynamic_cast<DisplayableDay *>(day.get());

	tm new_date = d->dateInfo;
	new_date.tm_hour = when.tm_hour;
	new_date.tm_min = when.tm_min;

	int year_index = 0;

	if (new_date.tm_year == BaseYear)
	{
		year_index = LowYearIndex;
	}
	else if (new_date.tm_year == MiddleYear)
	{
		year_index = MidYearIndex;
	}
	else if (new_date.tm_year == LargestYear)
	{
		year_index = HighYearIndex;
	}

	//created pointer to event 
	shared_ptr<DisplayableComponent> new_event = make_shared<Event>(day, name, new_date, recurrEvery, recurrFor);

	//add event to vector of events
	cal->event_map.insert(pair<std::string, std::shared_ptr<DisplayableComponent>>(name, new_event));

	//add component to day 
	cal->getChild(year_index)->getChild(new_date.tm_mon)->getChild(new_date.tm_mday - DayIndex)->addComponent(new_event);

	//build recurring events 
	if (recurrEvery > 0)
	{
		for (int i = 0; i < recurrFor; ++i)
		{
			//get new date depending on how often event should recurr
			new_date = addDays(new_date, recurrEvery);
			shared_ptr<DisplayableComponent> new_event = make_shared<Event>(day, name, new_date, recurrEvery, recurrFor);

			int year_index = 0;

			if (new_date.tm_year == BaseYear)
			{
				year_index = LowYearIndex;
			}
			else if (new_date.tm_year == MiddleYear)
			{
				year_index = MidYearIndex;
			}
			else if (new_date.tm_year == LargestYear)
			{
				year_index = HighYearIndex;
			}

			//check if event years is within the bounes of the calendar 
			if (new_date.tm_year < BaseYear || new_date.tm_year > LargestYear)
			{
				break;
			}

			//insert into event map
			cal->event_map.insert(pair<std::string, std::shared_ptr<DisplayableComponent>>(name, new_event));

			//add as child of day
			cal->getChild(year_index)->getChild(new_date.tm_mon)->getChild(new_date.tm_mday - DayIndex)->addComponent(new_event);
		}
	}

	return new_event;
}

//get calendar component by day based on granularity 
shared_ptr<DisplayableComponent> FullCalendarBuilder::getComponentByDate(shared_ptr<DisplayableComponent> cal, tm d, string granularity) {
	
	int index = 0;
	       
	//update index based on year 
	if (d.tm_year == BaseYear)
	{
		index = LowYearIndex;
	}
	else if (d.tm_year == MiddleYear)
	{
		index = MidYearIndex;
	}
	else if (d.tm_year == LargestYear)
	{
		index = HighYearIndex;
	}

	//get the DisplayableYear object
	if (granularity == "year")
	{
		return cal->getChild(index); 
	}
	//get the DisplayableMonth object
	else if (granularity == "month")
	{
		return cal->getChild(index)->getChild(d.tm_mon-MonthIndex);
	}
	//get the DisplayableDay object 
	else if (granularity == "day")
	{
		return cal->getChild(index)->getChild(d.tm_mon)->getChild(d.tm_mday-DayIndex);
	}

	return nullptr;
}

//builds a DisplayableDay
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) {

	shared_ptr<DisplayableComponent> day = make_shared<DisplayableDay>(d, p);

	return day;
}

//builds a DisplayableMonth
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> m = make_shared<DisplayableMonth>(d, p, CalendarComponent::months[index], CalendarComponent::days[index]);
	for (int i = 0; i < CalendarComponent::days[index]; ++i) { // for each day in the month
		m->addComponent(buildDay(d, m)); // construct day and add as a child of the month
		++(d.tm_mday); // increment day of the month
		d.tm_wday = (d.tm_wday + 1) % CalendarComponent::DAYSINAWEEK; // increment weekday, reset to 0 if needed
	}
	return m;
}

//builds a DisplayableYear
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> y = make_shared<DisplayableYear>(d, p, false);
	// construct each month and add it as a child of the year
	for (unsigned int i = 0; i < CalendarComponent::MONTHS; ++i) {
		d.tm_mon = i;
		y->addComponent(buildMonth(d, y));
		// set week day of first day of the next month
		d.tm_wday = (d.tm_wday + CalendarComponent::days[i]) % CalendarComponent::DAYSINAWEEK;
	}
	return y;
}
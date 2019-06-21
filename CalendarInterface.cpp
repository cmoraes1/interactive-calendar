/*
Camilla Moraes - camillamoraes@wustl.edu (Some written by Jon Shidal and provided as starter code) 
Lab 5
CalendarInterface.cpp: define functions declared in CalendarInterface class, which handle interaction with the
user and prompts them when either using the calendar or to do list. 
*/

#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "ToDoList.h"
#include "Task.h"
#include "Event.h"
#include "utilityfunctions.h"
#include "MergeDecorator.h"
#include "CalendarInfo.h"
#include "TimeInfo.h"
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

//CalendarInterface constructor
CalendarInterface::CalendarInterface(std::string builderType, std::string calendarName, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) {
	if (builderType == "full") {
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		currentDisplay = cal;
	}
}

//To do list 
void CalendarInterface::todo() 
{
	cout << endl;

	//get instance of to do list and set the current display to point to it 
	shared_ptr<DisplayableComponent> todolist = ToDoList::getInstance();
	currentDisplay = todolist;
	todolist->displayAll();

	while (1)
	{
		cout << "Add task: add\nMark task as complete: complete\nSwitch to calendar: cal" << endl;
		string input;
		cin >> input;

		//add task to to do list 
		if (input == "add")
		{
			tm task_date;

			cout << "Enter the name of the task" << endl;
			string name;
			cin >> name;

			cout << "Enter the month of the task (1 - 12)" << endl;
			unsigned int month;
			cin >> month;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}
			
			task_date.tm_mon = month-MonthIndex;

			//make sure month entered is valid 
			if (month > CalendarComponent::MONTHS || month < SmallestMonth)
			{
				cout << "The month you inputed is not within the range of a calendar (01 - 12). Please start over." << endl;
				break;
			}

			cout << "Enter the day of the task (1 - 31 depending on the month)" << endl;
			int day;
			cin >> day;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			task_date.tm_mday = day;

			//make sure day is a valid day in selected month 
			if (task_date.tm_mday < SmallestDay || task_date.tm_mday > cal->mon_days.find(task_date.tm_mon)->second)
			{
				cout << task_date.tm_mday << " is not a valid day in the selected month. Please start over." << endl;
				break;
			}

			cout << "Enter the year of the task" << endl;
			int year;
			cin >> year;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			task_date.tm_year = year - CalendarComponent::BASEYEAR;

			cout << "Enter the hour of the task (0 - 24)" << endl;
			int hour;
			cin >> hour;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			task_date.tm_hour = hour;

			//make sure hour entered is valid 
			if (hour > LargestHour || hour < SmallestHour)
			{
				cout << "The hour you inputed is not valid. Please start over" << endl;
				break;
			}

			cout << "Enter the minute of the task (0 - 60)" << endl;
			int minute;
			cin >> minute;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			task_date.tm_min = minute;

			//make sure minute entered is valid 
			if (minute > LargestMinute || minute < SmallestMinute)
			{
				cout << "The minute you entered is not valid. Please start over." << endl;
				break;
			}

			string state = "TODO";

			//create a task object and add it to the to do list
			shared_ptr<DisplayableComponent> new_task = make_shared<Task>(name, task_date, state);
			todolist->addComponent(new_task);
			cout << endl;
			todolist->displayAll();
		}
		//mark task as complete
		else if (input == "complete")
		{
			cout << "Enter number of the task of you would like to mark as complete (based on their order)" << endl;
			int index;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			cin >> index;

			//mark task as complete using CompleteDecorator 
			todolist->markComplete(index-TaskIndex);
			todolist->displayAll();
			cout << endl;
		}
		//switch to display calendar 
		else if (input == "cal")
		{
			//update display to display calendar
			currentDisplay = cal;
			run();
		}
	}
}

//run calendar 
void CalendarInterface::run() {
	// run until the user quits
	while (1) {
		int index = 0;

		cout << endl;

		// display the current display of the calendar
		currentDisplay->displayObject();

		cout << endl;

		// display options to the user and respond to user input accordingly
		cout << "add event: add\nsearch for event: search\njump to date: jump\nzoom out: out\nzoom in: in\nstore in file: store\nrestore calendar: restore\nMerge calendars: merge\nquit: q\nSwitch to to do list: todo" << endl;
		string in;
		cin >> in;

		//switch to do list 
		if (in == "todo")
		{
			todo();
		}
		//merge calendar from file 
		else if (in == "merge")
		{
			cout << "Enter the name of the file you would like to merge" << endl;
			string file_name;
			cin >> file_name;

			ifstream file;
			file.open(file_name);

			string file_cal_name;

			//get name of calendar in file 
			getline(file, file_cal_name);

			//add all events from file 
			tm date;

			string event_name;
			int day;
			int mon;
			int year;
			int min;
			int hour;
			int recurrEvery;
			int recurrFor;

			//extract values to build event from file 
			while (file >> event_name >> day >> mon >> year >> hour >> min >> recurrEvery >> recurrFor)
			{
				date.tm_mday = day;
				date.tm_mon = mon;
				date.tm_year = year;
				date.tm_min = min;
				date.tm_hour = hour;

				int year_index = 0;

				//update year_index depending on the year of the event 
				if (year == BaseYear)
				{
					year_index = LowYearIndex;
				}
				else if (year == MiddleYear)
				{
					year_index = MidYearIndex;
				}
				else if (year == LargestYear)
				{
					year_index = HighYearIndex;
				}

				//check if year is out of bounds of calendar 
				if (year < BaseYear || year > LargestYear)
				{
					break;
				}

				//build events with data extracted from file 
				shared_ptr<DisplayableComponent> new_event = builder->buildEvent(cal, event_name, date, recurrEvery, recurrFor);

				//call merge decorator on event to decorate it with the calendar name it came from 
				cal->getChild(year_index)->getChild(date.tm_mon)->getChild(date.tm_mday - DayIndex)->editDisplay(new_event, file_cal_name);
			}
		}
		//store current calendar in a file 
		else if (in == "store")
		{
			ofstream file;

			cout << "Enter the name of the file you would like to store the calendar to" << endl;
			string file_name;
			cin >> file_name;

			file.open(file_name);

			//add calendar name to file 
			file << cal->name << endl;;
			cal->writeToFile(cal->name, file_name);
			file.close();
		}
		//restore calendar from a file 
		else if (in == "restore")
		{
			cout << "Enter the name of the file you would like to open (i.e. file.txt)" << endl;
			string file_name;
			cin >> file_name;

			ifstream file;
			file.open(file_name);

			string file_cal_name;

			//set  calendar name to name in file
			getline(file, file_cal_name);
		
			cal->name = file_cal_name;

			//remove all current calendar events
			cal->removeEvents();

			//remove all events from map
			for (auto it = cal->event_map.begin(); it != cal->event_map.end();)
			{
				cal->event_map.erase(it++);
			}

			tm date;

			string event_name;
			int day;
			int mon;
			int year;
			int min;
			int hour;
			int recurrEvery;
			int recurrFor;

			//extract values with information about events from file 
			while (file >> event_name >> day >> mon >> year >> hour >> min >> recurrEvery >> recurrFor)
			{
				date.tm_mday = day;
				date.tm_mon = mon;
				date.tm_year = year;
				date.tm_min = min;
				date.tm_hour = hour;

				int year_index = 0;

				//update year_index depending on the year of the event 
				if (year == BaseYear)
				{
					year_index = LowYearIndex;
				}
				else if (year == MiddleYear)
				{
					year_index = MidYearIndex;
				}
				else if (year == LargestYear)
				{
					year_index = HighYearIndex;
				}

				//check if year is within bounds of calendar
				if (year < BaseYear || year > LargestYear)
				{
					break;
				}

				//if day's children vector is size 0, push back a nullptr to prevent program from crashing 
				if (cal->getChild(year_index)->getChild(date.tm_mon)->getChild(date.tm_mday - DayIndex)->children.size() == EmptyVector)
				{
					cal->getChild(year_index)->getChild(date.tm_mon)->getChild(date.tm_mday - DayIndex)->children.push_back(nullptr);
				}


				//build event with data extracted from file 
				builder->buildEvent(cal, event_name, date, recurrEvery, recurrFor);
			}
		}
		//add event to calendar 
		else if (in == "add")
		{
			tm when;

			//prompt user with questions to get information to build event 
			cout << "Enter the name of your event" << endl;
			string event_name;
			getline(cin >> ws, event_name);

			cout << "Enter the month of your event (1 - 12)" << endl;
			unsigned int month;
			cin >> month;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				run();
			}

			when.tm_mon = month - MonthIndex;

			//make sure month entered is valid 
			if (month > CalendarComponent::MONTHS || month < SmallestMonth)
			{
				cout << "The month you inputed is not within the range of a calendar (01 - 12). Please start over." << endl;
				run();
			}

			cout << "Enter the day of your event (1 - 31 depending on the month)" << endl;
			int day;
			cin >> day;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			when.tm_mday = day;

			//make sure day is a valid day in selected month 
			if (when.tm_mday < SmallestDay || when.tm_mday > cal->mon_days.find(when.tm_mon)->second)
			{
				cout << when.tm_mday << " is not a valid day in the selected month. Please start over." << endl;
				run();
			}

			cout << "Enter the year of your event (2019 - 2021)" << endl;
			int year;
			cin >> year;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			when.tm_year = year - CalendarComponent::BASEYEAR;

			int lowest_year = 2019;
			int greatest_year = 2021;

			//make sure year entered is within the range of the calendar (2019 - 2021) 
			if (year < lowest_year || year > greatest_year)
			{
				cout << "The year you entered is not within the bounds of the calendar. Please start over" << endl;
				run();
			}

			cout << "Enter the hour of your event (1 - 24)" << endl;
			int hour;
			cin >> hour;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			when.tm_hour = hour;

			//make sure hour entered is valid 
			if (hour > LargestHour || hour < SmallestHour)
			{
				cout << "The hour you inputed is not valid. Please start over" << endl;
				run();
			}

			cout << "Enter the minute of your event (1 - 60)" << endl;
			int minute;
			cin >> minute;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			when.tm_min = minute;

			//make sure minute entered is valid 
			if (minute > LargestMinute || minute < SmallestMinute)
			{
				cout << "The minute you entered is not valid. Please start over." << endl;
				run();
			}

			cout << "Event should recurr every ____ days (Enter 0 if your event is not recurring)" << endl;
			int re_every;
			cin >> re_every;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			cout << "Event should recurr ____ times (Enter 0 if your event is not recurring)" << endl;
			int re_for;
			cin >> re_for;

			//make sure input is numeric
			if (!cin)
			{
				cout << "Your input is not valid. You must enter a number. Please try again." << endl;
				break;
			}

			int year_index = 0;

			//update year_index depending on year entered by user 
			if (when.tm_year == BaseYear)
			{
				year_index = LowYearIndex;
			}
			else if (when.tm_year == MiddleYear)
			{
				year_index = MidYearIndex;
			}
			else if (when.tm_year == LargestYear)
			{
				year_index = HighYearIndex;
			}

			//make sure year entered is within the bounds of the calendar 
			if (when.tm_year < BaseYear || when.tm_year > LargestYear)
			{
				cout << "The year you entered is not within the range of the calendar. Please start over" << endl;
				run();
			}

			//if day's children vector is of size 0 push back a nullptr to prevent program crash
			if (cal->getChild(year_index)->getChild(when.tm_mon)->getChild(when.tm_mday - DayIndex)->children.size() == EmptyVector)
			{
				cal->getChild(year_index)->getChild(when.tm_mon)->getChild(when.tm_mday - DayIndex)->children.push_back(nullptr);
			}

			//build event with values entered by user 
			builder->buildEvent(cal, event_name, when, re_every, re_for);

		}
		//delete event from calendar 
		else if (in == "delete")
		{
			//make sure events parent exists 
			if (currentDisplay->getParent().lock() != nullptr)
			{
				//remove day's child at corresponding index to delete event from vector
				currentDisplay->getParent().lock()->removeComponent(index);

				//iterate through event map and remove event 
				for (auto it = cal->event_map.begin(); it != cal->event_map.end();)
				{
					if ((*it).second == currentDisplay)
					{
						cal->event_map.erase(it++);
					}
					else
					{
						++it;
					}
				}

				//zoom out to display the day object (event no longer exists so event object shoudn't be displayed anymore) 
				zoomOut();
			}
	

		}
		//edit event 
		else if (in == "edit")
		{
			//make sure events parent exists 
			if (currentDisplay->getParent().lock() != nullptr)
			{
				//get events parent and remove its child at corresponding index 
				currentDisplay->getParent().lock()->removeComponent(index);

				zoomOut();

				tm when;

				//prompt user to create event again 
				cout << "Enter the new name of your event" << endl;
				string event_name;
				getline(cin >> ws, event_name);

				cout << "Enter the new month of your event (1 - 12)" << endl;
				unsigned int month;
				cin >> month;

				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}

				when.tm_mon = month - MonthIndex;

				//make sure month entered is valid 
				if (month > CalendarComponent::MONTHS || month < SmallestMonth)
				{
					cout << "The month you inputed is not within the range of a calendar. Please start over." << endl;
					run();
				}

				cout << "Enter the new day of your event (1 - 31 depending on the month)" << endl;
				int day;
				cin >> day;

				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}

				when.tm_mday = day;

				//make sure day is a valid day in selected month 
				if (when.tm_mday < SmallestDay || when.tm_mday > cal->mon_days.find(when.tm_mon)->second)
				{
					cout << when.tm_mday << " is not a valid day in the selected month. Please start over." << endl;
					run();
				}

				cout << "Enter the new year of your event (2019 - 2021)" << endl;
				int year;
				cin >> year;

				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}

				when.tm_year = year - CalendarComponent::BASEYEAR;

				int lowest_year = 2019;
				int greatest_year = 2021;

				//make sure year entered is within the range of the calendar (2019 - 2021) 
				if (year < lowest_year || year > greatest_year)
				{
					cout << "The year you inputed is not within the range of the the calendar. Please start over." << endl;
					run();
				}

				cout << "Enter the new hour of your event (01 - 12)" << endl;
				int hour;
				cin >> hour;

				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}

				when.tm_hour = hour;

				//make sure hour entered is valid 
				if (hour > LargestHour || hour < SmallestHour)
				{
					cout << "The hour you inputed is not valid. Please start over" << endl;
					run();
				}

				cout << "Enter the minute of your event (1 - 60)" << endl;
				int minute;
				cin >> minute;

				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}

				when.tm_min = minute;

				//make sure minute entered is valid 
				if (minute > LargestMinute || minute < SmallestMinute)
				{
					cout << "The minute you entered is not valid. Please start over." << endl;
					run();
				}

				cout << "Event should recurr every ____ days (Enter 0 if your event is not recurring)" << endl;
				int re_every;
				cin >> re_every;

				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}

				cout << "Event should recurr ____ times (Enter 0 if your event is not recurring)" << endl;
				int re_for;
				cin >> re_for;
				
				//make sure input is numeric
				if (!cin)
				{
					cout << "Your input is not valid. You must enter a number. Please try again." << endl;
					break;
				}


				//build event with values entered by user 
				builder->buildEvent(cal, event_name, when, re_every, re_for);
			}

	
		}
		//search for event based on its name 
		else if (in == "search")
		{
			cout << "Enter the event name" << endl;
			string query;
			cin >> query;

			//vector with events with inputted name returned from search function 
			vector<std::shared_ptr<DisplayableComponent>> vect = cal->search(query);

			//if no events with entered name exist
			if (vect.size() == EmptyVector)
			{
				cout << "Sorry, no events named " << query << " were found in the calendar" << endl;
			}
			else
			{
				//display all events with given query (could be more than one)
				for (unsigned int i = 0; i < vect.size(); ++i)
				{
					vect.at(i)->displayAll();
				}

				unsigned int mult_results = 1;

				//prompt user to select event if there is more than 1 event with name queried
				if (vect.size() > mult_results)
				{
					int index_format = 1;
					cout << "Enter the number of the event you would like to see (i.e. 1, 2, 3, etc based on their ordering)" << endl;
					int index;
					cin >> index;

					//make sure input is numeric
					if (!cin)
					{
						cout << "Your input is not valid. You must enter a number. Please try again." << endl;
						currentDisplay = cal;
					}

					int event_index = index - index_format;

					//display event at selected index
					vect.at(event_index)->displayObject();

				}
			}
		}
		//jump to specific date in calendar and display at selected granularity
		else if(in == "jump")
		{
			//prompt user to enter day, month, year and granularity
			std::tm jump_date;

			cout << "Enter month" << endl;
			unsigned int month;
			cin >> month;
			jump_date.tm_mon = month-MonthIndex;

			//make sure month entered is valid 
			if (month > CalendarComponent::MONTHS || month < SmallestMonth)
			{
				cout << "The month you inputed is not within the range of a calendar. Please start over." << endl;
				run();
			}

			cout << "Enter day (1 - 31 depending on the month)" << endl;
			int day;
			cin >> day;
			int day_index = 1;
			jump_date.tm_mday = day;

			//make sure day is a valid day in selected month 
			if (jump_date.tm_mday < SmallestDay || jump_date.tm_mday > cal->mon_days.find(jump_date.tm_mon)->second)
			{
				cout << jump_date.tm_mday << " is not a valid day in the selected month. Please start over" << endl;
				run();
			}

			cout << "Enter a year (2019 - 2021)" << endl;
			int year;
			cin >> year;

			int lowest_year = 2019;
			int greatest_year = 2021;

			//make sure year entered is within the range of the calendar (2019 - 2021) 
			if (year < lowest_year || year > greatest_year)
			{
				cout << "The year you inputed is not within the range of the the calendar. Please start over." << endl;
				run();
			}

			int base_year = 1900;
			jump_date.tm_year = year - base_year;
			cout << "Select your granularity (year, month, or day)" << endl;
			string granularity;
			cin >> granularity;

			//call getComponentByDate function and update currentDisplay
			currentDisplay = builder->getComponentByDate(cal, jump_date, granularity);		
		}
		//zoom in one level
		else if (in == "in") 
		{
			if (currentDisplay->children.size() > 0) {
				cout << "index? (0-" << currentDisplay->children.size() - 1 << ") NOTE: This means that the index for a day is one less than the date (i.e. day 19's index is 18)" << endl;
				int index = 0;
				cin >> index;
				zoomIn(index);
			}
			else 
			{
				cout << "Nothing to zoom in on" << endl;
			}
		}
		//zoom out one level
		else if (in == "out") 
		{
			zoomOut();
		}
		//quit calendar
		else if (in == "q") 
		{
			break;
		}
	}
}

void CalendarInterface::zoomIn(unsigned int index) {
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr) {
		currentDisplay = temp;
	}
}

void CalendarInterface::zoomOut() {
    // if the current display has a parent, update current display to the parent
	if (currentDisplay->getParent().lock() != nullptr) {
		// create a shared_ptr from a weak_ptr, contributing to the objects reference count
		currentDisplay = currentDisplay->getParent().lock();
	}
}
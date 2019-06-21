/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
Task.cpp: Defines functions relating to a Task object (i.e. updating a tasks display and determining its current state)
*/

#include "stdafx.h"
#include "Task.h"
#include "CalendarInfo.h"
#include <iostream>

using namespace std;

Task::Task() {}

//task constructor
Task::Task(string name, tm date, string task_state)
	: task_name(name), task_date(date), state(task_state)
{}

//updates task display depending on the state of the task (todo or complete) 
void Task::displayAll()
{
	if (state == "COMPLETE")
	{
		cout << "\t" << task_name << " " << task_date.tm_mon+MonthIndex << "/" << task_date.tm_mday << "/" << task_date.tm_year + 1900 << " " << task_date.tm_hour << ":" << task_date.tm_min << " COMPLETE" << endl;;
	}
	else if (state == "TODO")
	{
		cout << "\t" << task_name << " " << task_date.tm_mon+MonthIndex << "/" << task_date.tm_mday << "/" << task_date.tm_year + 1900 << " " << task_date.tm_hour << ":" << task_date.tm_min << " TODO" << endl;;

	}
}

//updates task state to being complete
void Task::markComplete(unsigned int x)
{
	state = "COMPLETE";
}

std::vector<std::shared_ptr<DisplayableComponent>> Task::search(std::string query)
{
	vector<std::shared_ptr<DisplayableComponent>> vect;
	return vect;
}

void Task::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) {}
void Task::displayObject() {}
void Task::displayEvents() {}
void Task::writeToFile(std::string cal_name, std::string file_name) {}
void Task::removeEvents() {}
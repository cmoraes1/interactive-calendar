#pragma once

/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
Task.h: Declares the Task class, which inherits from DisplayableComponent. A task can be a child of a ToDoList
object. 
*/

#include "DisplayableComponent.h"
#include <string>
#include <memory>

class Task : public DisplayableComponent {
protected:
	std::string task_name;
	tm task_date;
	std::string task_state;
public:
	std::string state;
	Task();
	Task(std::string task, tm date, std::string state);
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
	friend bool task_compare(std::shared_ptr<DisplayableComponent> one, std::shared_ptr<DisplayableComponent> two);
};
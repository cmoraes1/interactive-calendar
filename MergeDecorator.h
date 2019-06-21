#pragma once

/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
MergeDecorator.h: Declares a concrete decorator which inherits from DisplayableComponentDecorator.
It is used to decorate an event with the name of the calendar it comes from when merging calendars from a file.
*/

#include "DisplayableComponent.h"
#include "DisplayableComponentDecorator.h"
#include <string>

//responsible for adding respective calendar name to event 
class MergeDecorator : public DisplayableComponentDecorator {
public:
	MergeDecorator(std::shared_ptr<DisplayableComponent> comp);
	std::string cal_origin;
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
};


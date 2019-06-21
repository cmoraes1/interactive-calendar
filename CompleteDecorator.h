#pragma once

/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
CompleteDecorator.h: Declares a concrete decorator which inherits from DisplayableComponentDecorator.
It is used to mark a task in a to do list as complete.
*/

#include "DisplayableComponentDecorator.h"
#include "DisplayableComponent.h"
#include <memory>

//responsible for marking a task as complete
class CompleteDecorator : public DisplayableComponentDecorator {
public:
	CompleteDecorator(std::shared_ptr<DisplayableComponent> comp);
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void markComplete(unsigned int x) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
};

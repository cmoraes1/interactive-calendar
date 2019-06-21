#pragma once

/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
ToDoList.h: declare the ToDoList class, which inherits from DisplayableComponent. The ToDoList is a composite
object and may have children which are Tasks. Implemented using the Singleton pattern to ensure only one ToDoList
object can exist at a time. 
*/

#include "DisplayableComponent.h"
#include <string>
#include <memory>

class ToDoList : public DisplayableComponent {
private:
	ToDoList(std::string name); //private constrctor
	//~ToDoList();
	//static ToDoList * list_instance;
	static std::shared_ptr<ToDoList> list_instance;
protected:
	std::string list_name;
public:
	static std::shared_ptr<ToDoList> getInstance();
	void markComplete(unsigned int x) override;
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
	virtual void displayAll() override;
	virtual void displayObject() override;
	virtual void displayEvents() override;
	virtual void writeToFile(std::string cal_name, std::string file_name) override;
	virtual void removeEvents() override;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) override;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) override;
};
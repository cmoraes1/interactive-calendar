/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
ToDoList.cpp: Declares functions defined in ToDoList class (i.e. adding tasks to todo list, updating its display and 
decorating it 
*/

#include "stdafx.h"
#include "ToDoList.h"
#include "DisplayableComponent.h"
#include "Task.h"
#include "DisplayableComponentDecorator.h"
#include "CompleteDecorator.h"
#include "MergeDecorator.h"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

using namespace std;

ToDoList::ToDoList(std::string name)
	: list_name(name)
{
	//initialize list with an empty vector that can be filled with tasks
	children.push_back(nullptr);
}

//set pointer to be 0 initially
shared_ptr<ToDoList> ToDoList::list_instance = 0;

//get instance of todo list to ensure only one object exists at a time
std::shared_ptr<ToDoList> ToDoList::getInstance()
{

	//if instance has already been created, return same instance (prevents client from being able to create > 1 list)
	if (list_instance == 0)
	{
		list_instance = shared_ptr<ToDoList>(new ToDoList("My Todo List:"));
	}

	return list_instance;

}

//add component to todo list 
std::shared_ptr<DisplayableComponent> ToDoList::addComponent(std::shared_ptr<DisplayableComponent> task)
{
	// try to dynamically cast comp to a pointer to a Task, will fail if the DisplayableComponent is not an task
	Task* new_task = dynamic_cast<Task *>(task.get()); // can only cast regular pointers, not shared_ptrs

	// the cast failed
	if (new_task == nullptr) {
		return nullptr;
	}

	int first_pos = 0;

	//if vector is empty (no children)
	if (children[first_pos] == nullptr)
	{
		//add task to first spot in vector
		children[first_pos] = task;
		return task;
	}
	else
	{
		//add empty space to vector
		children.push_back(nullptr);

		//add task at end of vector
		children[children.size() - 1] = task;

		//sort tasks from earliest to latest
		std::sort(children.begin(), children.end(), task_compare);

		return task;
	}
}

//display todo list and forward request to its children  
void ToDoList::displayAll()
{
	cout << list_name << endl;
  
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (children[i] != nullptr)
		{
			children[i]->displayAll();
		}
	}
}

//get child of todo list based on index passed in and allocate a Decorator object
void ToDoList::markComplete(unsigned int x)
{
	//get pointer to given task to decorate 
	std::shared_ptr<DisplayableComponent> comp = getChild(x);

	//mark that child as complete
	children.at(x)->markComplete(x);
}


std::vector<std::shared_ptr<DisplayableComponent>> ToDoList::search(std::string query)
{
	vector<std::shared_ptr<DisplayableComponent>> vect;
	return vect;
}

void ToDoList::displayObject() {}
void ToDoList::displayEvents() {}
void ToDoList::writeToFile(std::string cal_name, std::string file_name) {}
void ToDoList::removeEvents() {}
void ToDoList::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) { }



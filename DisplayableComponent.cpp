/*
Author: Jon Shidal
Purpose: Definition of DisplayableComponent class. Defines the implementation that is 
inherited by all concrete classes deriving from it.
*/

#include "stdafx.h"
#include "DisplayableComponent.h"
#include "Event.h"
#include "Task.h"
#include <iostream>

using namespace std;

DisplayableComponent::DisplayableComponent() {}

DisplayableComponent::DisplayableComponent(shared_ptr<DisplayableComponent> p) : parent(p) {}

// zero out all shared_ptr so resources are cleaned up
DisplayableComponent::~DisplayableComponent() {
	for (size_t i = 0; i < children.size(); ++i) {
		// parent is a weak_ptr, so no need to clear children's parent
		children[i] = nullptr;
	}
	children.clear();
}

//sorts events from earliest to latest 
bool event_compare(std::shared_ptr<DisplayableComponent> one, std::shared_ptr<DisplayableComponent> two)
{
	//dynamically cast DisplayableComponent pointer to be an Event
	Event* e_one = dynamic_cast<Event*>(one.get());
	Event* e_two = dynamic_cast<Event*>(two.get());

	//if hours are the same sort by minutes, otherwise sort by hour 
	return e_one->dateInfo.tm_hour < e_two->dateInfo.tm_hour || (e_one->dateInfo.tm_hour == e_two->dateInfo.tm_hour
		&& e_one->dateInfo.tm_min < e_two->dateInfo.tm_min);
}

//sorts tasks from earliest to latest
bool task_compare(std::shared_ptr<DisplayableComponent> one, std::shared_ptr<DisplayableComponent> two)
{
	//dynamically cast DisplayableComponent pointer to be a Task
	Task* t_one = dynamic_cast<Task*>(one.get());
	Task* t_two = dynamic_cast<Task*>(two.get());

	//sort by date, if dates are the same sort by time 
	return t_one->task_date.tm_year < t_two->task_date.tm_year
		|| (t_one->task_date.tm_year == t_two->task_date.tm_year
			&& t_one->task_date.tm_mon < t_two->task_date.tm_mon)
		|| (t_one->task_date.tm_year == t_two->task_date.tm_year
			&& t_one->task_date.tm_mon == t_two->task_date.tm_mon && t_one->task_date.tm_mday < t_two->task_date.tm_mday)
		|| (t_one->task_date.tm_year == t_two->task_date.tm_year
			&& t_one->task_date.tm_mon == t_two->task_date.tm_mon && t_one->task_date.tm_mday == t_two->task_date.tm_mday
			&& t_one->task_date.tm_hour < t_two->task_date.tm_hour)
		|| (t_one->task_date.tm_year == t_two->task_date.tm_year
			&& t_one->task_date.tm_mon == t_two->task_date.tm_mon && t_one->task_date.tm_mday == t_two->task_date.tm_mday
			&& t_one->task_date.tm_hour == t_two->task_date.tm_hour && t_one->task_date.tm_min < t_two->task_date.tm_min);
}

shared_ptr<DisplayableComponent> DisplayableComponent::addComponent(shared_ptr<DisplayableComponent> comp) {
	// do nothing as default, leaf nodes can't contain components. 
	// Any composite classes that can contain components will override this
	return nullptr;
}

// this method does not shrink the children vector, it simply nulls out the removed index in the vector
shared_ptr<DisplayableComponent> DisplayableComponent::removeComponent(unsigned int index) {
	// go ahead and define a default implementation here, this should be good enough for derived classes(leaf or composite).
	if (index < children.size()) { // leaf objects will have size of 0
		shared_ptr<DisplayableComponent> removed = children[index];
		children[index] = nullptr;
		return removed; // pointer to the removed component if successful
	}
	return nullptr; // nullptr is remove fails
}


weak_ptr<DisplayableComponent> DisplayableComponent::getParent() {
	return parent;
}

shared_ptr<DisplayableComponent> DisplayableComponent::getChild(unsigned int index) {
	// go ahead and define here, leaf classes with no children will return nullptr
	if (index < children.size()) {
		return children[index];
	}
	else {
		return nullptr; // nullptr if index is out of bounds
	}
}
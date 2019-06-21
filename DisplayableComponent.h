/*
Author: Jon Shidal
Purpose: Declaration of DisplayableComponent. DisplayableComponent is the common base class of all displayable objects.
It declares and defines the interface that all objects in the composite share.
*/
#pragma once
#include<memory>
#include<vector>
#include <map>
#include <string>

// forward declaration, needed for friend declaration
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableComponentDecorator;
class Event;

// abstract base class representing a composite object
class DisplayableComponent {
	friend FullCalendarBuilder;
	friend CalendarInterface;
	friend DisplayableComponentDecorator;
	friend Event;
public:
	DisplayableComponent();
	// defined by concrete classes deriving from DisplayableComponent
	virtual void displayAll() = 0;
	virtual void displayObject() = 0;
	virtual void displayEvents() = 0;
	virtual void writeToFile(std::string cal_name, std::string file_name) = 0;
	virtual void removeEvents() = 0;
	virtual std::vector<std::shared_ptr<DisplayableComponent>> search(std::string query) = 0;
	virtual void markComplete(unsigned int x) = 0;
	virtual void editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name) = 0;
protected:
	// member variables
	std::vector<std::shared_ptr<DisplayableComponent> > children;
	std::weak_ptr<DisplayableComponent> parent; // weak_ptr to avoid cycles, does not contribute to reference count

	// construction, destruction
	DisplayableComponent(std::shared_ptr<DisplayableComponent>);
	virtual ~DisplayableComponent();

	//multimap associating event name with event - data structure to store events
	std::multimap<std::string, std::shared_ptr<DisplayableComponent>> event_map; 

	// composite and traversal functions
	virtual std::weak_ptr<DisplayableComponent> getParent();
	virtual std::shared_ptr<DisplayableComponent> getChild(unsigned int);
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>);
	virtual std::shared_ptr<DisplayableComponent> removeComponent(unsigned int);

};

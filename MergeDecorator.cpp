/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
MergeDecorator.cpp: Decorates event object with calendar name.
*/

#include "stdafx.h"
#include "MergeDecorator.h"
#include "DisplayableComponentDecorator.h"
#include "DisplayableComponent.h"
#include "Calendar.h"
#include <iostream>
#include <vector>

using namespace std;

//initializes component to be decorated
MergeDecorator::MergeDecorator(std::shared_ptr<DisplayableComponent> comp)
	: DisplayableComponentDecorator(comp)
{}

//decorates object with calendar name when DisplayableMonth is the top level object being displayed
void MergeDecorator::displayAll()
{
	cout << "\t" << cal_origin << "::";
	component->displayAll();
}

//decorates object with calendar name when DisplayableDay is the top level object being displayed
void MergeDecorator::displayObject() 
{ 
	cout << cal_origin << "::";
	component->displayObject();
}

//decorates object with calendar name when an Event is the top level object being displayed
void MergeDecorator::displayEvents()
{
	cout << cal_origin << "::";
	component->displayEvents();
}

void MergeDecorator::editDisplay(std::shared_ptr<DisplayableComponent> d, std::string cal_name)
{
	//set member variable equal to name of calendar being merged in 
	cal_origin = cal_name;
}

std::vector<std::shared_ptr<DisplayableComponent>> MergeDecorator::search(std::string query)
{
	vector<shared_ptr<DisplayableComponent>> vect;
	return vect;
}

void MergeDecorator::writeToFile(std::string cal_name, std::string file_name) {}
void MergeDecorator::removeEvents() {}
void MergeDecorator::markComplete(unsigned int x) {}

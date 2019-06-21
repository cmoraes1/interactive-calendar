/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
DisplayableComponentDecorator.cpp: Decorator that initializes the component member variables and forwards requests to the object
being decorated.
*/

#include "stdafx.h"
#include "DisplayableComponentDecorator.h"
#include "DisplayableComponent.h"
#include <memory>

using namespace std;

//initializes component being decorator
DisplayableComponentDecorator::DisplayableComponentDecorator(std::shared_ptr<DisplayableComponent> comp)
	: component(comp)
{}

//override addComponent method by forwarding request to component being decorator
std::shared_ptr<DisplayableComponent> DisplayableComponentDecorator::addComponent(std::shared_ptr<DisplayableComponent> comp)
{
	return DisplayableComponentDecorator::component->addComponent(comp);
}

//override getChild method by forwarding request to component being decorator
std::shared_ptr<DisplayableComponent> DisplayableComponentDecorator::getChild(unsigned int i)
{
	return component->getChild(i);
}

//get parent of component
weak_ptr<DisplayableComponent> DisplayableComponentDecorator::getParent() {
	return component->getParent();
}
#pragma once

/*
Camilla Moraes - camillamoraes@wustl.edu
Lab 5
DisplayableComponentDecorator.h: Declares a decorator which inherits from DisplayableComponent. 
*/

#include "DisplayableComponent.h"
#include <memory>

class DisplayableComponentDecorator : public DisplayableComponent {
protected:
	std::shared_ptr<DisplayableComponent> component; //holds address of object being decorated
public:
	DisplayableComponentDecorator(std::shared_ptr<DisplayableComponent> d);
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
	virtual std::shared_ptr<DisplayableComponent> getChild(unsigned int) override;
	virtual std::weak_ptr<DisplayableComponent> getParent() override;
};

/*
Author: Jon Shidal
Purpose: create a CalendarInterface object and call run
*/

#include "stdafx.h"
#include "CalendarInterface.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char * argv[]) {

	cout << "Would you like to view the calendar or to do list? Enter cal for calendar and todo for todo list" << endl;
	string input;
	cin >> input;

	if (input == "cal")
	{
		CalendarInterface ci("full", "My Calendar", 3);
		ci.run();
	}
	else if(input == "todo")
	{
		CalendarInterface ci("full", "My Calendar", 3);
		ci.todo();
	}

	return 0;
}
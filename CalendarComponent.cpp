/*
Author: Jon Shidal
Purpose: Define Calendar component class.
*/

#include "stdafx.h"
#include "CalendarComponent.h"
#include<iostream>
#include<string>

using namespace std;

// from <ctime>
//struct tm {
//	int tm_sec;   // seconds of minutes from 0 to 61
//	int tm_min;   // minutes of hour from 0 to 59
//	int tm_hour;  // hours of day from 0 to 24
//	int tm_mday;  // day of month from 1 to 31
//	int tm_mon;   // month of year from 0 to 11
//	int tm_year;  // year since 1900
//	int tm_wday;  // days since sunday
//	int tm_yday;  // days since January 1st
//	int tm_isdst; // hours of daylight savings time
//}

// static class variables
const std::vector<string> CalendarComponent::daysoftheweek = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const std::vector<string> CalendarComponent::months = { "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November","December" };
const std::vector<int> CalendarComponent::days = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const unsigned int CalendarComponent::DAYSINAWEEK = 7;
const unsigned int CalendarComponent::MONTHS = 12;
const unsigned int CalendarComponent::BASEYEAR = 1900;
const unsigned int CalendarComponent::DAYSINAYEAR = 365;

// CalendarComponent
CalendarComponent::CalendarComponent(std::tm d, std::shared_ptr<DisplayableComponent> p) : DisplayableComponent(p), dateInfo(d) {}
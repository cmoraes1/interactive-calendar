#pragma once

#include<ctime>
/*
Author: Jon Shidal
Purpose: declare functions for dealing with tm structs, particularly for advancing the date/time represented by a particular number of days.
*/

tm addDays(tm current, int numDays);
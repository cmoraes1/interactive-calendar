Camilla Moraes - camillamoraes@wustl.edu
CSE 332
Lab 5

____________________________________________________________________________________________________________

Group members:

Camilla Moraes - completed on my own

Program Summary:

This program builds a calendar that holds three years, 2019, 2020, and 2021. The calendar can be displayed in a
a number of ways, depending on whether the user decides to zoom in on a year, month, day, or event. Users are 
able to add regular or recurring events to any day on the calendar, and can edit or delete these events. Users
can also store their current calendar in a file and restore calendars from files, which will overwrite the current
content of the calendar, or merge other calendars into their current calendar. Lastly, users also have the option
to create a todo list and switch back and forth between their todo list and the calendar.  

Test Cases: 

1. Adding an event in a year not stored in calendar (i.e. 2018 or 2021) - program prints
   statement indicating error and reprompts user. 
   
2. Adding an event that on an invalid day (i.e. 40) - program prints statement indicating error and 
   reprompts user. 
   
3. Adding an event in an invalid month (i.e. 15) - program prints statement indicating error and 
   reprompts user. 
   
4. Adding an event at an invalid time (i.e. hour greater than 24 and minute greater than 60) - 
   program prints statement indicating error and reprompts user.
   
5. Entering words (instead of numbers) for a task's year, month, date, hour, or minute - program
   prints statement indicating error and reprompts user. 
   
7. Adding task on an invalid day (i.e. 40) - program prints statement indicating my error and 
   reprompts user. 
   
8. Add task in an invalid month (i.e. 15) - program prints statement indicating error and 
   reprompts user.
   
9. Adding task that at invalid time (i.e. hour greater than 24 and minute greater than 60) - 
   program prints statement indicating  error and reprompts user.  

____________________________________________________________________________________________________________

1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 

What class/classes is responsible for the user interface of the Calendar?
CalendarInterface, which handles the users input and output, is responsible for the user interface of the Calendar.


What class/classes is responsible for managing the representation and construction of the Calendar?
FullCalendarBuilder, which is a subclass of CalendarBuilder, is responsible for managing the representation
and construction of the Calendar. 


Which class should handle collecting information from the user about an event?
The CalendarInterface class handles collecting information from the user about an event. In this class, the program
prompts the user to enter information about the event they would like to add to the calendar. 

Which class should handle constructing and adding the event to the Calendar?
The FullCalendarBuilder is responsible for constructing an event. After the event is constructed, it calls
the addComponent method on the DisplayableDay object for that event and adds it as a child of that day. 

____________________________________________________________________________________________________________

2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?

I created a multimap that maps a string to a shared_ptr<DisplayableComponent>. The string key is the event name,
and its value is the Event object. I chose to use a multimap instead of a regular map to account for events with
the same name. Multimaps can have duplicate keys, while maps cannot. Additionally, I chose to use a map instead of
another container, such as a vector, becasue lookup is much more efficient. Instead of having to iterate through
the entire container to search for an event, I am able to do it in constant time by asking the user to enter
the name of the event they are searching for, and checking if that name exists in the multimap and returning 
the Event object it maps to. 

Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?

The FullCalendarBuilder understands the structure of the Calendar. It is responsbile for building every object in
the calendar (Calendar, DisplayableYear, DisplayableMonth, DisplayableDay, Event). The Calendar object is responsible for jumping to a 
specific object in the Calendar by having access to each objects children. 

How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?

I saved the calendar name as the first line of the file. I wrote a function called writeToFile which is forwarded to each days event
and then wrote all the event information to the file. Therefore, each file contains a list of events and their details (date, time, how often it
recurs, recurs for) all separated by a space. I decided that there was no need to save all of the years, months and days
to the file because there are no changes to these objects. The only difference will be the events. 

____________________________________________________________________________________________________________

3. Part 2.3 Updating the display
How a particular component in the calendar should be displayed depends on what the current display of the calendar is.
How did you implement this functionality? 

I created two new functions, displayObject and displayEvents, which work with displayAll to handle the calendar's display.
DisplayObject is used to format the object when it is the top level object being displayed. Whenever the current display
of the calendar is updated, displayObject is called, and may forward more requests so its children depending on what the display is.
For objects that have children, I wrote code in the displayObject function iterates through the objects child vector and 
forwards requests to either call displayAll on its children, if I am trying to display all of its information as well as its 
childrens information, or displayEvents if I am trying to display all of the events associated with that object. 
The display function that is called and forwarded depends on the current display. 


Did you make any changes to the interfaces provided in the starter code? If so, how easy was it to 
refactor the code to match this change? 

I added functions to the DisplayableComponent and CalendarComponent classes that are overrided by 
classes that inherit from it. For example, I added displayObject and displayEvents to be pure virtual functions in 
DisplayableComponent and CalendarComponent because I wanted all objects that are shared pointers to DisplayableComponents
to override these functions and implement them. It was very easy to add these functions to the code. Other than this, I did
not make any changes to the interfaces provided in the starter code. 


How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.

I initially considered using the Visitor pattern to update the display of the calendar, but my implementation of creating new
display functions and calling each one depending on the calendar's current display was much easier. All I had to do 
was write functions to display the objects when they themselves were the current display, or write functions that would be 
forwarded to an objects children when I wanted to display the children in a certain way if the children themselves were not
the calendar's current display. This approach is very flexible because if I want to change an objects display all I have to 
do is figure out which function is being called on it and update it. Also, if I want to come up with a completely new way
to display an object, I am able to create a new display method and call it when appropriate. 

____________________________________________________________________________________________________________


Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?

The Decorator pattern is very beneficial in providing a flexible and extensible way to add behavior to an object.
The Decorator pattern adds this behavior, or "decorates" the object at run time, which provides more flexibility
than other alternatives which function at compile time. I created a class called DisplayableComponentDecorator which
was a subclass of DisplayableComponent and forwards all requests to the object that is decorated. Then, I created 
a MergeDecorator which inherits from the DisplayableComponentDecorator which defines the functions that actually decorate
the object. In this case, the Event objects that are merged in from other calendars are decorated with the name of the 
calendar that they originate from. Therefore, the functions in MergeDecorator "decorate" the events with their calendar
name and update the display. Lastly, in order to make these functions executed and actually decorate the event I 
wrote the editDisplay method in the DisplayableDay.cpp file to dynamically allocate a new MergeDecorator object
and then update the event in the day's child vector so that it was a MergeDecorator object. 


If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 

I used the decorator design pattern. 



3.2 ToDo List
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?

I implemented my TODO list to ensure that there is only a single todo list instance. I made my todo list constructor
private so that the client could not call the instructor and create another instance of the todo list. Additionally,
I created a private member variable called list_instance that is a shared pointer to a ToDoList. This member variable 
is initially set to 0. I created a function called getInstance which checks if the list_instance member variable has been set yet.
If it is equal to 0, then I dynamically allocate a ToDoList object using "new", and then construct a shared_ptr to
a ToDoList object using the pointer from the dynamically allocated object. Then, I set list_instance equal to this shared_ptr.
If list_instance has already been set, the getInstance method returns the list_instance, rather than creating a new one, 
ensuring that only one ToDoList object exists at a time. 

Regarding the actual implementation and functionality of my ToDoList, both the ToDoList and Task objects are subclasses
of DisplayableComponent. ToDoList has a vector of children initially set to null, but filled with Tasks each time a 
Task is created. A task is a leaf object and thus does not have any children. Therefore, I used the composite pattern
to build my ToDoList in order to make it flexible and extensible. With the composite pattern, I could easily make
a Task a composite object and give it children if I wanted to (i.e. if I wanted tasks to have subtasks). In order
to mark a task complete, I updated the task's state member variable when a user indicated they wanted to mark the task
complete and then updated the display. A task's state is initially set to "todo" when added to the todo list. This
made it very simple and easy to update the task display and indicate that they were complete. 

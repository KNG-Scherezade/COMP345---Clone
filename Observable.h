//! The observable header file contains the observer and subjet classes.
//! Both of these are abstract classes that force subclasses to connect to eachother and get the subject to notify a vector of observers something changes

//! Vanilla C++


#pragma once
#include<vector>

class Observer; 
class Subject;

//! forces subjects(AKA models) to have these methods if they work with __observer classes
class Subject
{
public:
	virtual void notify() = 0;
	virtual void attach(Observer* obs) = 0;
	
	std::vector<Observer*> listeners;
};

//! forces observers(views) to have the update method.
class Observer
{
public:
	Observer(Subject* subj);
	~Observer();

	virtual void update() = 0;
protected:
	Subject* getSubject();
private:
	Subject* subject;
};


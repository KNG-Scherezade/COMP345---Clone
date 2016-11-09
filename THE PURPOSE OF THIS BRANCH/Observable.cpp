#include "Observable.h"


//! abstract observer superclass that holds a subject and causes the subclass to attatch to a model/subject
Observer::Observer(Subject* subj)
{
	this->subject = subj;
	subj->attach(this);
}
Observer::~Observer()
{
}

//! gets subject
Subject* Observer::getSubject() {
	return subject;
}

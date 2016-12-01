#pragma once
#include "Observable.h"

class MonsterObserver :public Observer
{
public:
	MonsterObserver(Subject* subj);
	~MonsterObserver();

	void update();
	void printMonsterDetails();
	bool checkStatus();
};


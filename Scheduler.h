/*
 * Scheduler.h
 *
 *  Created on: Mar 13, 2013
 *      Author: ashish
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include<iostream>
#include<list>
#include "task.h"

using namespace std;

class Scheduler
{
private:
	void updateFirstFireAtTime(void);
protected:
	int startTime;
	list<TASK*> *TaskList;
public:
	Scheduler(){startTime=0;};
	~Scheduler(){};
	void setTaskSet(list<TASK*> *_TaskList)
	{
		if(!_TaskList){cout<<"\n\nError: TaskList NULL"<<endl;}
		TaskList = _TaskList;
	}
	void setStartTime(int _startTime){startTime = _startTime; updateFirstFireAtTime();}
};

class RMPriorityScheduler : public Scheduler
{
public:
	int startScheduler(void);
};

#endif /* SCHEDULER_H_ */

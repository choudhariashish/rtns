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
#include "Config.h"

using namespace std;

int checkDeadlineMiss(list<TASK*> *_TaskList, int _currTime);
int updateReadyTasks(list<TASK*> *_TaskList, int _currTime);
TASK* getRMHighestPriority(list<TASK*> *_TaskList);

class Scheduler
{
private:

protected:
	int startTime;
	list<TASK*> *TaskList;
	float calculateUtilization(void);
	float calculateDensity(void);
	int calculateHyperperiod(void);
	void printAllTasks(void);
	void printRespTimeOfAllTasks(void);
	void updateFirstFireAtTime(void)
	{
		list<TASK*>::iterator it;
		for( it=TaskList->begin(); it!= TaskList->end(); it++)
		{
			(*it)->setNextFireAt((*it)->getPhase());
			if((*it)->getNextFireAt() == startTime)
				(*it)->setStatus(active);
		}
	}
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

class RM_DM_Scheduler : public Scheduler
{
public:
	int start_RM_Scheduler(void);
};

class PriorityScheduler : public Scheduler
{
private:
	int highlightDeadlineMiss(int currTime);
	TASK* getHighestPriorityTask(void);
	void calculateExeFrom_P_D_d(void);
public:
	int start_Priority_Scheduler(void);
};

#endif /* SCHEDULER_H_ */

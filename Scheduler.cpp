/*
 * Scheduler.cpp
 *
 *  Created on: Mar 13, 2013
 *      Author: ashish
 */
#include "Scheduler.h"
#include<iostream>
#include<list>

using namespace std;

#define active	1
#define idle	0

void checkDeadlineMiss(list<TASK*> *_TaskList, int _currTime)
{
	list<TASK*>::iterator it;
	for( it=_TaskList->begin(); it!= _TaskList->end(); it++)
	{
		if((*it)->getDeadline() == _currTime && (*it)->getCurrExecution()<(*it)->getExecution())
		{
			(*it)->setStatus(idle);
			cout<<" Miss Tid: "<<(*it)->getTaskId()<<endl;
		}
	}
}

int updateReadyTasks(list<TASK*> *_TaskList, int _currTime)
{
	if(!_TaskList){cout<<"\nError: List* is NULL"<<endl;return -1;}
	list<TASK*>::iterator it;
	for( it=_TaskList->begin(); it!= _TaskList->end(); it++)
	{
		if((*it)->getNextFireAt() == _currTime)
		{
			(*it)->setStatus(active);
			(*it)->setDeadline(_currTime + (*it)->getPeriod());
			(*it)->setNextFireAt(_currTime + (*it)->getPeriod());
		}
	}
	return 0;
}

TASK* getRMHighestPriority(list<TASK*> *_TaskList)
{
	TASK* TaskHighPriority;
	int flag=0;
	list<TASK*>::iterator it;

	for( it=_TaskList->begin(); it!= _TaskList->end(); it++)
	{
		if((*it)->getStatus())
		{
			TaskHighPriority = (*it);
			flag = 1;
			break;
		}
	}
	for( it=_TaskList->begin(); it!= _TaskList->end(); it++)
	{
		if((*it)->getStatus())
			if((*it)->getPeriod() < TaskHighPriority->getPeriod())
			{
				TaskHighPriority = (*it);
			}
	}
	if(!flag)
	{
		TaskHighPriority = new TASK();
		TaskHighPriority->setTaskId(0);
	}
	return TaskHighPriority;
}

float check_RM_Utilization(list<TASK*> *TaskList)
{
	float utilization = 0.0;
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		utilization = utilization + ((float)(*it)->getExecution())/((float)(*it)->getPeriod());
	}
	return utilization;
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  else
    return gcd(b, a%b);
}

int lcm(int a, int b)
{
  return (a*b)/gcd(a,b);
}

int calculateHyperperiod(list<TASK*> *TaskList)
{
	int hyperperiod=1;
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		hyperperiod = lcm(hyperperiod, (*it)->getPeriod());
	}
	return hyperperiod;
}

void Scheduler::updateFirstFireAtTime(void)
{
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		(*it)->setNextFireAt((*it)->getPhase());
		if((*it)->getNextFireAt() == startTime)
			(*it)->setStatus(active);
	}
}

int RMPriorityScheduler::startScheduler(void)
{
	float utilization=check_RM_Utilization(TaskList);

	if(utilization == 0.0){cout<<"\n\nError: Utilization: "<<utilization<<"cannot continue..!"<<endl; return -1;}
	if(utilization>0.68 && TaskList->size()>=4){cout<<"\n\nError: Utilization: "<<utilization<<" not schedulable by RM"<<endl;return -1;}

	int startTime=0, endTime=calculateHyperperiod(TaskList);
	int currTime = startTime;

	if(!endTime){cout<<"\n\nError: Hyperperiod: "<<endTime<<endl;return -1;}
	cout<<"\n\nHyperperiod: "<<endTime<<endl;

	TASK *taskToSchedule = NULL;

	while(currTime<endTime)
	{
		updateReadyTasks(TaskList, currTime);
		taskToSchedule = getRMHighestPriority(TaskList);

		if(taskToSchedule->getTaskId() == 0)
			cout<<"Time: "<<currTime<<" Tid: Slack "<<endl;
		else
		{
			taskToSchedule->setCurrExecution(taskToSchedule->getCurrExecution()+1);

			cout<<"Time: "<<currTime<<" Tid: "<<taskToSchedule->getTaskId()<<" Exe: "<<taskToSchedule->getCurrExecution()<<endl;

			if(taskToSchedule->getCurrExecution()==taskToSchedule->getExecution())
			{
				taskToSchedule->setStatus(idle);
				taskToSchedule->resetCurrExecution();
				taskToSchedule = NULL;
			}
			checkDeadlineMiss(TaskList, currTime);
		}
		currTime++;
	}
	return 0;
}


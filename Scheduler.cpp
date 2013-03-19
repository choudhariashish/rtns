/*
 * Scheduler.cpp
 *
 *  Created on: Mar 13, 2013
 *      Author: ashish
 */
#include "Scheduler.h"
#include "Config.h"

#include<iostream>
#include<list>

using namespace std;


int checkDeadlineMiss(list<TASK*> *_TaskList, int _currTime)
{
	int flag=0;
	list<TASK*>::iterator it;
	for( it=_TaskList->begin(); it!= _TaskList->end(); it++)
	{
		if((*it)->getDeadline() == _currTime && (*it)->getCurrExecution()<(*it)->getExecution())
		{
			(*it)->setStatus(idle);
			(*it)->resetCurrExecution();
			if(debug){cout<<"\nTime : "<<_currTime<<" Deadline Miss Tid: "<<(*it)->getTaskId();}
			flag=1;
		}
	}
	return flag;
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
			(*it)->setDeadline(_currTime + (*it)->getDeadline());
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

float Scheduler::calculateUtilization(void)
{
	float utilization = 0.0;
	list<TASK*>::iterator it;
	int flag = 0;

	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		utilization = utilization + ((float)(*it)->getExecution())/((float)(*it)->getPeriod());
		if((*it)->getPeriod() != (*it)->getDeadline()) flag = 1;
	}
	if(flag) return 0.0;

	return utilization;
}

float Scheduler::calculateDensity(void)
{
	float density = 0.0;
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		density = density + ((float)(*it)->getExecution())/((float)(*it)->getStaticDeadline());
	}
	return density;
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

int Scheduler::calculateHyperperiod(void)
{
	int hyperperiod=1;
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		hyperperiod = lcm(hyperperiod, (*it)->getPeriod());
	}
	if(debug){cout<<"\nhyperperiod: "<<hyperperiod<<endl;}
	return hyperperiod;
}

void Scheduler::printAllTasks(void)
{
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		(*it)->printTaskParameters();
	}
}
void Scheduler::printRespTimeOfAllTasks(void)
{
	float QoS=0.0;
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		QoS = ((float)(*it)->getMaxRespTime()-(float)(*it)->getStaticDeadline()) / ((float)(*it)->getStaticDeadline());

//		cout<<"\n("<<(*it)->getMaxRespTime()<<"-"<<(float)(*it)->getStaticDeadline()<<")/"<<(float)(*it)->getStaticDeadline();

		cout<<"\nTid: "<<(*it)->getTaskId()<<" maxRespTime : "<<(*it)->getMaxRespTime();
		cout<<" QoS : "<<QoS;
		QoS = 0.0;
	}
}

/*
 * PriorityScheduler.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: ashish
 */
#include<iostream>
#include<list>

#include "Scheduler.h"
#include "Config.h"

using namespace std;

// highlight only if a job misses its deadline
int PriorityScheduler::highlightDeadlineMiss(int _currTime)
{
	int flag=0;
	list<TASK*>::iterator it;
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		if((*it)->getStatus()==active)
		{
			if((*it)->getDeadline() == _currTime && (*it)->getCurrExecution()<(*it)->getExecution())
			{
				if(debug){cout<<"\nTime : "<<_currTime<<" Deadline Miss Tid: "<<(*it)->getTaskId()<<" still continue(SoftRealTime)";}
				flag=1;
			}
		}
	}
	return flag;
}

// calculate exe from period,deadline,density
void PriorityScheduler::calculateExeFrom_P_D_d(void)
{
	float exe=0.0;
	int exe_temp=1;
	list<TASK*>::iterator it;
	if(debug)cout<<"\ncalculating Exe for tasks from Period,Deadline,density";
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		exe = ((float)(*it)->getDensity())*((float)(*it)->getStaticDeadline());
		exe_temp = exe;

		if(exe > (float)exe_temp)
			exe = exe+1.0;

		(*it)->setExecution(exe);

		if(debug){cout<<"\nTid: "<<(*it)->getTaskId()<<" exe : "<<(*it)->getExecution();}
		if(debug){cout<<" since, d*D+1.0 : "<<(*it)->getDensity()<<"*"<<(*it)->getStaticDeadline()<<"+1.0";}
	}
}

//find highest priority tas-strict priority defined by user
// lower value of priority higher is the weight
TASK* PriorityScheduler::getHighestPriorityTask(void)
{
	TASK* TaskHighPriority;
	int flag=0;
	list<TASK*>::iterator it;

	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		if((*it)->getStatus())
		{
			TaskHighPriority = (*it);
			flag = 1;
			break;
		}
	}
	for( it=TaskList->begin(); it!= TaskList->end(); it++)
	{
		if((*it)->getStatus())
			if((*it)->getPriority() < TaskHighPriority->getPriority())
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

int PriorityScheduler::start_Priority_Scheduler(void)
{
	int startTime = this->startTime;
	int currTime = startTime, endTime = this->calculateHyperperiod();

	calculateExeFrom_P_D_d();

	if(debug)printAllTasks();

	int deadlineMissFlag=0;

	TASK* HighPriorityTask;

	while(currTime < endTime)
	{
		updateReadyTasks(TaskList, currTime);

		HighPriorityTask = getHighestPriorityTask();

		if(HighPriorityTask->getTaskId() == 0)
		{
//			if(debug)cout<<"\nTime : "<<currTime<<" Tid : slack";
		}
		else
		{
			HighPriorityTask->setCurrExecution(HighPriorityTask->getCurrExecution()+1);

//			if(debug){cout<<"\nTime : "<<currTime<<" Tid : "<<HighPriorityTask->getTaskId()<<" Exe : "
//					<<HighPriorityTask->getCurrExecution();}

			if(HighPriorityTask->getCurrExecution() == HighPriorityTask->getExecution())
			{
//				if(debug){cout<<" responseTime : "<<(1+ currTime - (HighPriorityTask->getNextFireAt()-HighPriorityTask->getPeriod()));}
				HighPriorityTask->insertMinMaxRespTime((1+ currTime - (HighPriorityTask->getNextFireAt()-HighPriorityTask->getPeriod())));

				HighPriorityTask->resetCurrExecution();
				HighPriorityTask->setStatus(idle);
			}
		}

//		deadlineMissFlag = highlightDeadlineMiss(currTime);

		currTime++;
	}
//	if(debug){if(deadlineMissFlag){cout<<"\n\nDeadline missed";}else {cout<<"\nDeadline not missed";}}
	if(debug){cout<<"\ntotal density : "<<calculateDensity();}
	if(debug){printRespTimeOfAllTasks();}

	if(debug)cout<<endl;
	return 0;
}




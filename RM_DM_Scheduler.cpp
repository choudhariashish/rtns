/*
 * RM_DM_Scheduler.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: ashish
 */
#include<iostream>
#include<list>

#include "Scheduler.h"
#include "Config.h"

using namespace std;

int RM_DM_Scheduler::start_RM_Scheduler(void)
{
	float utilization=calculateUtilization();

	if(utilization == 0.0){cout<<"\n\nError: Utilization: "<<utilization<<"cannot continue..!"<<endl; return -1;}
	if(utilization>0.68 && TaskList->size()>=4){cout<<"\n\nError: Utilization: "<<utilization<<" not schedulable by RM"<<endl;return -1;}

	int startTime=0, endTime=calculateHyperperiod();
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

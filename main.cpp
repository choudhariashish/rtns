/*
 * main.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: ashish
 */
//system includes
#include<iostream>
#include<fstream>
#include<string>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<list>

//user includes
#include "task.h"
#include "Scheduler.h"

using namespace std;

int debug = 0;

int throwInputFileError(void)
{
	cout<<"\ninput file not in correct format\n\n";
	return -1;
}

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		cout<<"\nError: no input file specified\n"
				"\nUsage: ./RT_Neural_Net -i input.txt -d\n\n(-d to enable debug)\n"
				"\nfollow instructions in README.txt to write input.txt file\n";
		return -1;
	}
	char *file;
	for(int i=0; i<argc; i++)
	{
		if(argv[i][0] == '-')
		{
			if(argv[i][1] == 'd')
				debug = 1;
			else if(argv[i][1] == 'i')
				file = argv[i+1];
		}
	}
	cout<<"\nfile: "<<file<<endl;
	ifstream inptFile;
	inptFile.open(file);
	if(!inptFile.is_open())
	{
		cout<<"\nfailed to open input file\n";
		return -1;
	}
	string buffer;
	list<TASK*> *TaskList = new list<TASK*>;

	//parse input file and create objects for tasks
	while(!inptFile.eof())
	{
		inptFile>>buffer;
		if(buffer == "task")
		{
			inptFile>>buffer;
			if(buffer != "{"){ delete TaskList; return throwInputFileError();}
			TASK *task = new TASK();
			while(buffer != "}")
			{
				inptFile>>buffer;
				if(buffer == "taskid"){ inptFile>>buffer; task->setTaskId(atoi(buffer.c_str()));}else
				if(buffer == "phase"){inptFile>>buffer; task->setPhase(atoi(buffer.c_str()));}else
				if(buffer == "period"){inptFile>>buffer; task->setPeriod(atoi(buffer.c_str()));}else
				if(buffer == "execution"){inptFile>>buffer; task->setExecution(atoi(buffer.c_str()));}else
				if(buffer == "deadline"){inptFile>>buffer; task->setDeadline(atoi(buffer.c_str()));}else
				if(buffer == "priority"){inptFile>>buffer; task->setPriority((atof(buffer.c_str())));}else
				if(buffer == "qos"){inptFile>>buffer; task->setQos(atof(buffer.c_str()));}else
				if(buffer == "utilization"){inptFile>>buffer; task->setUtilization(atof(buffer.c_str()));}else
				if(buffer == "density"){inptFile>>buffer; task->setDensity(atof(buffer.c_str()));}else
				if(buffer == "}"){break;} else return throwInputFileError();
			}
			task->setStaticDeadline(task->getDeadline());
			TaskList->push_back(task);
		}
	}
	inptFile.close();
	if(debug){cout<<"\nNumber of tasks in system: "<<TaskList->size()<<endl;}

	PriorityScheduler P_Sched;

	Scheduler *Sched = &P_Sched;
	Sched->setTaskSet(TaskList);
	Sched->setStartTime(0);

	P_Sched.start_Priority_Scheduler();

	return 0;
}



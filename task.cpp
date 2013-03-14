/*
 * task.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: ashish
 */
#include"task.h"
#include<iostream>
using namespace std;

void TASK::printTaskParameters(void)
{
	cout<<"\ntaskid: "<<this->getTaskId();
	cout<<"\nphase: "<<this->getPhase();
	cout<<"\nperiod: "<<this->getPeriod();
	cout<<"\nexecution: "<<this->getExecution();
	cout<<"\ndeadline: "<<this->getDeadline();
	cout<<"\npriority: "<<this->getPriority();
	cout<<"\nqos: "<<this->getQos()<<endl;
}

TASK::TASK()
{
	taskid=0;
	phase=0;
	period=0;
	execution=0;
	deadline=0;
	priority=0;
	qos=0;
	currExecution=0;
	status = 0;
}

TASK::~TASK(){}

int TASK::getTaskId(void)
{
	return taskid;
}
int TASK::getPhase(void)
{
	return phase;
}
int TASK::getPeriod(void)
{
	return period;
}
int TASK::getExecution(void)
{
	return execution;
}
int TASK::getDeadline(void)
{
	return deadline;
}
float TASK::getPriority(void)
{
	return priority;
}
float TASK::getQos(void)
{
	return qos;
}
float TASK::getUtilization(void)
{
	return ((float)execution)/((float)period);
}
int TASK::getCurrExecution(void)
{
	return currExecution;
}
int TASK::getNextFireAt(void)
{
	return nextFireAt;
}
int TASK::getStatus(void)
{
	return status;
}

void TASK::setTaskId(int _taskid)
{
	taskid = _taskid;
}
void TASK::setPhase(int _phase)
{
	phase = _phase;
}
void TASK::setPeriod(int _period)
{
	period = _period;
}
void TASK::setExecution(int _execution)
{
	execution = _execution;
}
void TASK::setDeadline(int _deadline)
{
	deadline = _deadline;
}
void TASK::setPriority(float _priority)
{
	priority = _priority;
}
void TASK::setQos(float _qos)
{
	qos = _qos;
}
void TASK::setCurrExecution(int _currExecution)
{
	currExecution = _currExecution;
}
void TASK::resetCurrExecution(void)
{
	currExecution = 0;
}
void TASK::setNextFireAt(int _nextFireAt)
{
	nextFireAt = _nextFireAt;
}
void TASK::setStatus(int _status)
{
	status = _status;
}


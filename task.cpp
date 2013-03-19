/*
 * task.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: ashish
 */
#include"task.h"
#include<iostream>
#include<algorithm>

using namespace std;

void TASK::printTaskParameters(void)
{
	cout<<"\ntaskid: "<<this->getTaskId();
	cout<<"\nphase: "<<this->getPhase();
	cout<<"\nperiod: "<<this->getPeriod();
	cout<<"\nexecution: "<<this->getExecution();
	cout<<"\ndeadline: "<<this->getDeadline();
	cout<<"\npriority: "<<this->getPriority();
	cout<<"\nutilization: "<<this->getUtilization();
	cout<<"\ndensity: "<<this->getDensity();
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
	utilization=0.0;
	qos=0;
	currExecution=0;
	status = 0;
	density=0.0;
	minRespTime=0;
	maxRespTime=0;
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
int TASK::getStaticDeadline(void)
{
	return staticdeadline;
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
	return utilization;
}
float TASK::getDensity(void)
{
	return density;
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
int TASK::getMinRespTime(void)
{
	return minRespTime;
}
int TASK::getMaxRespTime(void)
{
	return maxRespTime;
}

/*------------------------------------*/

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
	minRespTime = period;
}
void TASK::setExecution(int _execution)
{
	execution = _execution;
	maxRespTime = execution;
}
void TASK::setDeadline(int _deadline)
{
	deadline = _deadline;
}
void TASK::setStaticDeadline(int _staticdeadline)
{
	staticdeadline = deadline;
}
void TASK::setPriority(float _priority)
{
	priority = _priority;
}
void TASK::setUtilization(float _utilization)
{
	utilization = _utilization;
}
void TASK::setDensity(float _density)
{
	density = _density;
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
void TASK::updateUtilization_OR_Density(void)
{
	if(this->getPeriod() > this->getDeadline())
	{
		this->setDensity((float)this->getExecution()/((float)this->getDeadline()));
		this->setUtilization(0.0);
	}
	else if(this->getPeriod() == this->getDeadline())
	{
		this->setUtilization((float)this->getExecution()/((float)this->getPeriod()));
		this->setDensity(0.0);
	}
}
void TASK::insertMinMaxRespTime(int _ResponseTime)
{
	maxRespTime = max(maxRespTime, _ResponseTime);
	minRespTime = min(minRespTime, _ResponseTime);
}


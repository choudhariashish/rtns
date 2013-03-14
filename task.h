/*
 * task.h
 *
 *  Created on: Mar 7, 2013
 *      Author: ashish
 */

#ifndef TASK_H_
#define TASK_H_

class TASK
{
private:
	int taskid;
	int phase;
	int period;
	int execution;
	int deadline;
	float priority;
	float qos;
	int currExecution;
	int nextFireAt;
	int status;
public:
	TASK();
	~TASK();
	int getTaskId(void);
	int getPhase(void);
	int getPeriod(void);
	int getExecution(void);
	int getDeadline(void);
	float getPriority(void);
	float getQos(void);
	float getUtilization(void);
	int getCurrExecution(void);
	int getNextFireAt(void);
	int getStatus(void);

	void setTaskId(int _taskid);
	void setPhase(int _phase);
	void setPeriod(int _period);
	void setExecution(int _execution);
	void setDeadline(int _deadline);
	void setPriority(float _priority);
	void setQos(float _qos);
	void setCurrExecution(int _currExecution);
	void resetCurrExecution(void);
	void setNextFireAt(int _nextFireAt);
	void setStatus(int _status);
	void printTaskParameters(void);
};


#endif /* TASK_H_ */

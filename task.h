/*
 * task.h
 *
 *  Created on: Mar 7, 2013
 *      Author: ashish
 */

#ifndef TASK_H_
#define TASK_H_

#include<vector>

using namespace std;

struct ResponseTime
{
	int time;
	int responseTime;
};

class TASK
{
private:
	int taskid;
	int phase;
	int period;
	int execution;
	int deadline;
	int staticdeadline;
	float priority;
	float qos;
	int currExecution;
	int nextFireAt;
	int status;
	float utilization;
	float density;
	vector<ResponseTime*> RespTime;
	int maxRespTime;
	int minRespTime;
public:
	TASK();
	~TASK();
	int getTaskId(void);
	int getPhase(void);
	int getPeriod(void);
	int getExecution(void);
	int getDeadline(void);
	int getStaticDeadline(void);
	float getPriority(void);
	float getQos(void);
	float getUtilization(void);
	float getDensity(void);
	int getCurrExecution(void);
	int getNextFireAt(void);
	int getStatus(void);

	void setTaskId(int _taskid);
	void setPhase(int _phase);
	void setPeriod(int _period);
	void setExecution(int _execution);
	void setDeadline(int _deadline);
	void setStaticDeadline(int _staticdeadline);
	void setPriority(float _priority);
	void setQos(float _qos);
	void setUtilization(float _utilization);
	void setDensity(float _density);
	void setCurrExecution(int _currExecution);
	void resetCurrExecution(void);
	void setNextFireAt(int _nextFireAt);
	void setStatus(int _status);
	void insertRespTime(ResponseTime* _RespTime)
	{
		RespTime.push_back(_RespTime);
	}
	void insertMinMaxRespTime(int _ResponseTime);
	int getMinRespTime(void);
	int getMaxRespTime(void);
	void updateUtilization_OR_Density(void);
	void printTaskParameters(void);
};


#endif /* TASK_H_ */

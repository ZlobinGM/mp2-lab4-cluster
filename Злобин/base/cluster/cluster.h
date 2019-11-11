#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "computer.h"
#include "queue.h"
#include <vector>
#include <iostream>

using namespace std;

const int EachQueueSize = 20;

class Cluster
{
	vector<Computer> cluster;						// кластер
	vector<TQueue<Task>> tasks;						// вектор очередей, для приоритета заданий
	vector<Task> tasks_in_progress;					// выполняющиеся на кластере

	int total_cores;

	int completed;
	int refused;
public:
	Cluster(vector<int> _cores_of_computers, int _priorities);

	void SetTasks(vector<Task> _tasks);
	void RunTact();
};

#endif

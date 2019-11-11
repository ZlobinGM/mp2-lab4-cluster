#include "cluster.h"

Cluster::Cluster(vector<int> _cores_of_computers, int _priorities) : completed(0), refused(0), total_cores(0)
{
	for each (int cores in _cores_of_computers)
	{
		total_cores += cores;
		cluster.push_back(Computer(cores));
	}
	for (int i = 0; i < _priorities; i++)
		tasks.push_back(TQueue(EachQueueSize));
}

void Cluster::SetTasks(vector<Task> _tasks)
{
}

void Cluster::RunTact()
{
}

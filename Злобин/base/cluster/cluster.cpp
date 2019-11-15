#include "cluster.h"

int Cluster::NoMoreActual()
{
	int refused_on_time = 0;
	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks[i].IsEmpty())
			continue;
		int length = tasks[i].Length();
		for (int j = 0; j < length; j++)
		{
			Task tmp = tasks[i].Pop();
			if (current_tact + tmp.GetTacts() <= total_tacts)
				tasks[i].Push(tmp);
			else refused_on_time++;
		}
	}
	return refused_on_time;
}

void Cluster::SetTasksInProgress()
{
	if (free_cores == 0)return;
	for (int i = 0; i < tasks.size(); i++)
	{
		if (!tasks[i].IsEmpty() && tasks[i].Begin().GetCores() > free_cores)
			return;
		else
			while (!tasks[i].IsEmpty() && tasks[i].Begin().GetCores() <= free_cores)
			{
				Task tmp = tasks[i].Pop();
				free_cores -= tmp.GetCores();
				for (int j = 0; j < comp_cluster.size(); j++)
				{
					if (tmp.GetCores() == 0) break;
					comp_cluster.at(j).LoudUpCores(tmp);
				}
				tasks_in_progress.push_back(tmp);
			}
	}
}

Cluster::Cluster(vector<int> _cores_of_computers, int _priorities, int _total_tacts) : completed(0), uncompleted(0), refused(0),
total_cores(0), total_tacts(_total_tacts), current_tact(0)
{
	for each (int cores in _cores_of_computers)
	{
		total_cores += cores;
		Computer comp(cores);
		comp_cluster.push_back(comp);
	}
	free_cores = total_cores;
	for (int i = 0; i < _priorities; i++) {
		TQueue<Task> queue_of_same_priority_tasks(EachQueueSize);
		tasks.push_back(queue_of_same_priority_tasks);
	}
}

int Cluster::SetTasks(vector<Task> _tasks)
{
	int refused_on_set = 0;
	refused_on_set += NoMoreActual();

	for each (Task _task in _tasks)
	{
		if (!tasks[_task.GetPriority()].IsFull() && _task.GetCores() <= total_cores
			&& _task.GetCreateTime() + _task.GetTacts() <= total_tacts)
		{
			tasks[_task.GetPriority()].Push(_task);
		}
		else refused_on_set++;
	}

	SetTasksInProgress();

	refused += refused_on_set;
	return refused_on_set;
}

int Cluster::RunTact()
{
	int completed_on_tact = 0;
	for (int i = tasks_in_progress.size() - 1; i >= 0; i--)
	{
		tasks_in_progress.at(i).ChangeTacts();
		if (tasks_in_progress.at(i).GetTacts() <= 0) {
			for (int j = 0; j < comp_cluster.size(); j++)
				free_cores += comp_cluster.at(j).FreeCoresOff(tasks_in_progress.at(i));
			tasks_in_progress.erase(tasks_in_progress.begin() + i);
			completed_on_tact++;
		}
	}
	current_tact++;
	completed += completed_on_tact;
	return completed_on_tact;
}

int Cluster::Stop()
{
	uncompleted = tasks_in_progress.size();
	comp_cluster.erase(comp_cluster.begin(), comp_cluster.end());
	tasks.erase(tasks.begin(), tasks.end());
	tasks_in_progress.erase(tasks_in_progress.begin(), tasks_in_progress.end());
	return uncompleted;
}

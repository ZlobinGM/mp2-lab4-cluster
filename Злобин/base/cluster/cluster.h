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
	vector<Computer> comp_cluster;						// кластер
	vector<TQueue<Task>> tasks;						// вектор очередей, для приоритета заданий
	vector<Task> tasks_in_progress;					// выполняющиеся на кластере

	int total_cores;								// всего ядер в кластере
	int free_cores;									// свободных ядер
	int total_tacts;								// сколько всего будет тактов
	int current_tact;

	int completed;									// завершенные задачи
	int uncompleted;								// незавершенные из-за прерывания
	int refused;									// отклоненные задачи

	int NoMoreActual();								// сколько задач, находясь в очереди, стали неактуальны по времени исполнения
	void SetTasksInProgress();						// назначить задание на исполнение
public:
	Cluster(vector<int> _cores_of_computers, int _priorities, int _total_tacts);

	int SetTasks(vector<Task> _tasks);				// назначить задание в очередь
	int RunTact();									// пройти 1 такт
	int Stop();										// остановка программы до естественного завершения

	int GetCompleted() { return completed; }
	int GetUncompleted() { return uncompleted; }
	int GetRefused() { return refused; }
};

#endif

#ifndef __TASK_H__
#define __TASK_H__

class Task
{
	static int count_of_tasks;
	int index;
	int create_time;			// когда задача появилась
	int priority;
	int cores;					// сколько ядер нужно на выполнение зада
	int tacts;					// сколько тактов будет выполняться
public:
	Task(int _create_time = 0, int _cores = 0, int _tacts = 0, int _priority = 0) : index(++count_of_tasks),
		create_time(_create_time), priority(_priority), cores(_cores), tacts(_tacts) {}
	Task(const Task& _task) : index(_task.index), create_time(_task.create_time), priority(_task.priority),
		cores(_task.cores), tacts(_task.tacts) {}

	int GetIndex() { return index; }
	int GetCreateTime() { return create_time; }
	int GetPriority() { return priority; }
	int GetCores() { return cores; }
	int GetTacts() { return tacts; }

	void ResetCreateTime(int _create_time) { create_time = _create_time; }
	void ChangeTacts() {									// уменьшить такты (нужно для контроля выполнения)
		tacts--; 
		if (tacts < 0) throw "task_already_completed";
	}
	void ChangeCores() {									// уменьшить число ядер (нужно для распределения задачи по ядрам кластера)
		cores--;
		if (cores < 0) throw "cores_for_task_already_found";
	}
	void ChangePriority() {									// уменьшить приоритет (нужно для избежания вечного застоя в очереди)
		if (priority == 0) return;
		priority--;
		if (priority < 0) throw "not_correct_priority";
	}
};

#endif
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
	Task(int _create_time,int _cores, int _tacts, int _priority) : index(++count_of_tasks), 
		create_time(_create_time), priority(_priority), cores(_cores), tacts(_tacts) {}

	int GetIndex() { return index; }
	int GetCreateTime() { return create_time; }
	int GetCores() { return cores; }
	int GetTacts() { return tacts; }

	void ResetCreateTime(int _create_time) { create_time = _create_time; }
	void ChangeTacts() { 
		tacts--; 
		if (tacts < 0) throw "task_already_completed";
	}
	void ChangeCores() {
		cores--;
		if (cores < 0) throw "cores_for_task_already_found";
	}
	void ChangePriority() {
		if (priority == 0) return;
		priority--;
	}
};

#endif
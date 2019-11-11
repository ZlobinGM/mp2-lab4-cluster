#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "task.h"

class Computer
{
	int cores;						// ������� ����
	int free_cores;					// ������� ���� ��������
	int* tasks_in_progress;			// ����� ������ �����������
public:
	Computer(int _cores = 1) :cores(_cores), free_cores(_cores) {
		tasks_in_progress = new int[_cores];
		for (int i = 0; i < _cores; i++) tasks_in_progress[i] = 0;
	}
	~Computer() { delete[] tasks_in_progress; }

	int GetCores() { return cores; }
	int GetFreeCores() { return free_cores; }
	void LoudUpCores(const Task& _task) {					// ��������� ������ �� ����������
		for (int i = 0; i < cores; i++)
		{
			if (!(_task.GetCores() && free_cores)) return;
			if (tasks_in_progress[i] == 0) {
				tasks_in_progress[i] = _task.GetIndex();
				_task.ChangeCores();
				free_cores--;
			}
		}
	}
	void FreeCoresOff(const Task& _task) {					// ���������� ����, ����������� ���������� ������ 
		for (int i = 0; i < cores; i++)
		{
			if (tasks_in_progress[i] == _task.GetIndex()) {
				tasks_in_progress[i] = 0;
				free_cores++;
			}
		}
	}
};

#endif
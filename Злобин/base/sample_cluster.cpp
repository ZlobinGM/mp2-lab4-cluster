#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include "cluster/cluster.h"

using namespace std;

int Task::count_of_tasks = 0;

int main()
{
	setlocale(LC_ALL, "Russian");

	int size_cluster, max_size = 30;
	cout << "Введите размер кластера x. 0 < x < " << max_size << " : ";
	do	{
		cin >> size_cluster;
	} while (size_cluster < 1 || size_cluster > max_size);

	int _tmp, core_with_max_size = 0;
	vector<int> cores;
	for (int i = 0; i < size_cluster; i++)
	{
		cout << "Введите число ядер " << i + 1 << "-го компьютера кластера x"
			<< i + 1 << ". 0 < x" << i + 1 << " < " << max_size << " : ";
		do {
			cin >> _tmp;
		} while (_tmp < 1 || _tmp > max_size);
		cores.push_back(_tmp);
		core_with_max_size = _tmp > core_with_max_size ? _tmp : core_with_max_size;
	}

	int priority, max_priority = 10;
	cout << "Введите число различных по приоритету видов задач x. 0 < x < " << max_priority << " : ";
	do {
		cin >> priority;
	} while (priority < 1 || priority > max_priority);

	int tacts, max_tacts = 1000;
	cout << "Введите число тактов x. 0 < x < " << max_tacts << " : ";
	do {
		cin >> tacts;
	} while (tacts < 1 || tacts > max_tacts);

	cout << "Нажмите любую клавишу чтобы прервать работу кластера и получить статистику." << endl;
	Cluster cluster(cores, priority, tacts);
	srand(time(NULL));
	for (int i = 0; i < tacts; i++)
	{
		if (_kbhit())
		{
			_getch();
			cluster.Stop();
			break;
		}
		vector<Task> new_tasks;
		int count = rand() % 10;
		for (int i = 0; i < count; i++)
		{
			int _cores = rand() % (core_with_max_size * size_cluster) + 1;
			int _tacts = rand() % (tacts) + 1;
			int _priority = rand() % priority;
			Task another_task(i, _cores, _tacts, _priority);
			new_tasks.push_back(another_task);
		}
		cout << "На " << i + 1 << "-ом такте: ";
		cout << "отклонено " << cluster.SetTasks(new_tasks) << " и ";
		cout << "выполнено " << cluster.RunTact() << " задач." <<endl;
		Sleep(50);
	}

	cout << endl << "Статистика: " << cluster.GetCompleted() << " выполненных, " << cluster.GetRefused() << " отклоненных, "
		<< cluster.GetUncompleted() << " незавершенных" << " задач." << endl;

	return 0;
}

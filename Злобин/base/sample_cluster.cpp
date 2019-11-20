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
	cout << "Введите размер кластера x. 0 < x < " << max_size + 1 << " : ";
	do	{
		cin >> size_cluster;
	} while (size_cluster < 1 || size_cluster > max_size);

	int _tmp, core_with_max_size = 0, total_cores_in_cluster = 0;
	vector<int> cores;
	for (int i = 0; i < size_cluster; i++)
	{
		cout << "Введите число ядер " << i + 1 << "-го компьютера кластера x"
			<< i + 1 << ". 0 < x" << i + 1 << " < " << max_size + 1 << " : ";
		do {
			cin >> _tmp;
		} while (_tmp < 1 || _tmp > max_size);
		cores.push_back(_tmp);
		total_cores_in_cluster += _tmp;
		core_with_max_size = _tmp > core_with_max_size ? _tmp : core_with_max_size;
	}

	int priority, max_priority = 10;
	cout << "Введите число различных по приоритету видов задач x. 0 < x < " << max_priority + 1 << " : ";
	do {
		cin >> priority;
	} while (priority < 1 || priority > max_priority);

	int tacts, min_tacts = 100, max_tacts = 1000;
	cout << "Введите число тактов x. " << min_tacts - 1 << " < x < " << max_tacts + 1 << " : ";
	do {
		cin >> tacts;
	} while (tacts < min_tacts || tacts > max_tacts);

	double large_cores_probability = 0, large_tacts_probability = 0, together = 0;
	cout << "Введите вероятность появления ресурсозатратной задачи x. " << 0 << " <= x <= " << 1 << " : ";
	do {
		cin >> large_cores_probability;
	} while (large_cores_probability < 0 || large_cores_probability > 1);
	cout << "Введите вероятность появления продожительной задачи x. " << 0 << " <= x <= " << 1 << " : ";
	do {
		cin >> large_tacts_probability;
	} while (large_tacts_probability < 0 || large_tacts_probability > 1);
	together = large_cores_probability * large_tacts_probability;

	cout << "Нажмите любую клавишу чтобы прервать работу кластера и получить статистику." << endl;
	int total_load_cores = 0;
	Cluster cluster(cores, priority, tacts);
	srand(time(NULL));
	for (int i = 0; i < tacts; i++)
	{
		if (_kbhit())
		{
			_getch();
			cluster.Stop();
			tacts = i + 1;
			break;
		}
		cout << "На " << i + 1 << "-ом такте: ";
		vector<Task> new_tasks;
		int count = rand() % 10;
		cout << "полученно " << count << ", ";
		for (int i = 0; i < count; i++)
		{
			double probability = double(rand()) / RAND_MAX;
			int _cores, _tacts;
			_cores = (probability > 1 - large_cores_probability || probability < together) ?
				rand() % (max_size - 1) + max_size / 2 : rand() % (core_with_max_size) + 1;
			_tacts = (probability < large_tacts_probability || probability > 1 - together) ?
				rand() % (max_tacts - min_tacts) + min_tacts : rand() % (min_tacts / 10) + 1;
			int _priority = rand() % priority;
			Task another_task(i, _cores, _tacts, _priority);
			new_tasks.push_back(another_task);
		}
		cout << "отклонено " << cluster.SetTasks(new_tasks) << " и ";
		cout << "выполнено " << cluster.RunTact() << " задач." <<endl;
		total_load_cores += total_cores_in_cluster - cluster.GetFreeCores();
		Sleep(50);
	}

	cout << endl << "Статистика: " << cluster.GetCompleted() << " выполненных, " << cluster.GetRefused() << " отклоненных, "
		<< cluster.GetUncompleted() << " незавершенных" << " задач." << endl;

	double median_load_in_percents = 100.0 * total_load_cores / total_cores_in_cluster / tacts;
	cout << "Средняя загрузка кластера: " << median_load_in_percents << "% ." << endl;

	return 0;
}

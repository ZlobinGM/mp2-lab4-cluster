#include <iostream>
#include <string>
#include <conio.h>
#include "cluster/cluster.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int size_cluster, max_size = 30;
	cout << "Введите размер кластера x. 0 < x < " << max_size << endl;
	do	{
		cin >> size_cluster;
	} while (size_cluster < 1 || size_cluster > max_size);

	int tmp;
	vector<int> cores;
	for (int i = 0; i < size_cluster; i++)
	{
		cout << "Введите число ядер " << i + 1 << "-го компьютера кластера x"
			<< i + 1 << ". 0 < x" << i + 1 << " < " << max_size;
		do {
			cin >> size_cluster;
		} while (tmp < 1 || tmp > max_size);
		cores.push_back(tmp);
	}

	int priority, max_priority = 10;
	cout << "Введите число различных по приоритету видов задач x. 0 < x < " << max_priority << endl;
	do {
		cin >> priority;
	} while (priority < 1 || priority > max_priority);

	int tacts, max_tacts = 1000;
	cout << "Введите число тактов x. 0 < x < " << max_tacts << endl;
	do {
		cin >> tacts;
	} while (tacts < 1 || tacts > max_tacts);

	cout << "Нажмите любую клавишу чтобы прервать работу кластера и получить статистику" << endl;
	Cluster cluster(cores, priority, tacts);
	for (int i = 0; i < tacts; i++)
	{
		if (_kbhit())
		{
			_getch();
		}
	}

	return 0;
}

#include "cluster/cluster.cpp"
#include <gtest.h>

int Task::count_of_tasks = 0;

TEST(Cluster, can_cluster)
{
	vector<int> cores_of_each_computer = { 1,2,4,8 };
	ASSERT_NO_THROW(Cluster(cores_of_each_computer, 10, 100));
}

TEST(Cluster, can_refuse_tasks_by_cores)
{
	vector<int> cores_of_each_computer = { 1,2,4,8 };
	Cluster cl(cores_of_each_computer, 10, 100);
	vector<Task> tasks;
	for (int i = 0; i < 10; i++)
	{
		tasks.push_back(Task(10, 55, 2, 2));
	}
	for (int i = 0; i < 5; i++)
	{
		tasks.push_back(Task(10, 2, 2, 2));
	}

	EXPECT_EQ(10, cl.SetTasks(tasks));
}

TEST(Cluster, can_refuse_tasks_by_tacts)
{
	vector<int> cores_of_each_computer = { 1,2,4,8 };
	Cluster cl(cores_of_each_computer, 10, 100);
	vector<Task> tasks;
	for (int i = 0; i < 10; i++)
	{
		tasks.push_back(Task(10, 2, 2, 2));
	}
	for (int i = 0; i < 5; i++)
	{
		tasks.push_back(Task(10, 2, 555, 2));
	}

	EXPECT_EQ(5, cl.SetTasks(tasks));
}

TEST(Cluster, can_complete_tasks)
{
	vector<int> cores_of_each_computer = { 1,2,4,8 };
	Cluster cl(cores_of_each_computer, 10, 100);
	vector<Task> tasks;
	for (int i = 0; i < 3; i++)
	{
		tasks.push_back(Task(3, 3, 1, 1));
	}
	cl.SetTasks(tasks);

	EXPECT_EQ(3, cl.RunTact());
}

TEST(Cluster, can_uncomplete_tasks)
{
	vector<int> cores_of_each_computer = { 1,2,4,8 };
	Cluster cl(cores_of_each_computer, 10, 100);
	vector<Task> tasks;
	for (int i = 0; i < 3; i++)
	{
		tasks.push_back(Task(3, 3, 9, 1));
	}
	cl.SetTasks(tasks);
	cl.RunTact();

	EXPECT_EQ(3, cl.Stop());
}
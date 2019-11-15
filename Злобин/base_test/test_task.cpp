#include "cluster/task.h"
#include <gtest.h>

TEST(Task, can_create_task)
{
	ASSERT_NO_THROW(Task());
}

TEST(Task, can_get_create_time)
{
	Task task(10, 22, 46, 80);
	EXPECT_EQ(10, task.GetCreateTime());
}

TEST(Task, can_get_riority)
{
	Task task(10, 22, 46, 80);
	EXPECT_EQ(80, task.GetPriority());
}

TEST(Task, can_get_cores)
{
	Task task(10, 22, 46, 80);
	EXPECT_EQ(22, task.GetCores());
}

TEST(Task, can_get_tacts)
{
	Task task(10, 22, 46, 80);
	EXPECT_EQ(46, task.GetTacts());
}

TEST(Task, can_reset_create_time)
{
	Task task(10, 22, 46, 80);
	task.ResetCreateTime(99);
	EXPECT_EQ(99, task.GetCreateTime());
}

TEST(Task, can_change_tacts)
{
	Task task(10, 22, 46, 80);
	task.ChangeTacts();
	EXPECT_EQ(45, task.GetTacts());
}

TEST(Task, throws_when_change_tacts_bellow_zero)
{
	Task task(10, 22, 0, 80);
	ASSERT_ANY_THROW(task.ChangeTacts(););
}

TEST(Task, can_change_cores)
{
	Task task(10, 22, 46, 80);
	task.ChangeCores();
	EXPECT_EQ(21, task.GetCores());
}

TEST(Task, throws_when_change_cores_bellow_zero)
{
	Task task(10, 0, 46, 80);
	ASSERT_ANY_THROW(task.ChangeCores(););
}

TEST(Task, can_change_priority)
{
	Task task(10, 22, 46, 80);
	task.ChangePriority();
	EXPECT_EQ(79, task.GetPriority());
}

TEST(Task, throws_when_change_priority_bellow_zero)
{
	Task task(10, 22, 46, -11);
	ASSERT_ANY_THROW(task.ChangePriority(););
}
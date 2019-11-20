#include "cluster/computer.h"
#include <gtest.h>

TEST(Computer, can_create_computer)
{
	ASSERT_NO_THROW(Computer());
}

TEST(Computer, can_get_cores)
{
	Computer comp(10);
	EXPECT_EQ(10, comp.GetCores());
}

TEST(Computer, can_get_free_cores)
{
	Computer comp(10);
	EXPECT_EQ(10, comp.GetFreeCores());
}

TEST(Computer, can_load_up_cores)
{
	Computer comp(10);
	Task task(10, 7, 3, 3);
	comp.LoudUpCores(task);

	EXPECT_EQ(3, comp.GetFreeCores());
}

TEST(Computer, can_free_off_cores)
{
	Computer comp(10);
	Task task1(10, 3, 3, 3), task2(10, 4, 4, 4);
	comp.LoudUpCores(task1);
	comp.LoudUpCores(task2);
	comp.FreeCoresOff(task2);

	EXPECT_EQ(7, comp.GetFreeCores());
}
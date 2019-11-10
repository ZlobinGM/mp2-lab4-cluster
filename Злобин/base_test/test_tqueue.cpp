#include "queue.h"
#include <gtest.h>

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> qu(5));
}

TEST(TQueue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(TQueue<int> qu(MaxStackSize + 1));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> qu(-5));
}

TEST(TQueue, can_push_to_queue)
{
	TQueue<int> qu(3);
	ASSERT_NO_THROW(qu.Push(3));
}

TEST(TQueue, throw_when_push_to_full_queue)
{
	TQueue<int> qu(3);
	qu.Push(1);
	qu.Push(2);
	qu.Push(3);

	ASSERT_ANY_THROW(qu.Push(4));
}

TEST(TQueue, can_pop_from_queue)
{
	TQueue<int> qu(3);
	qu.Push(1);

	ASSERT_NO_THROW(qu.Pop());
}

TEST(TQueue, throw_when_pop_from_empty_queue)
{
	TQueue<int> qu(3);

	ASSERT_ANY_THROW(qu.Pop());
}

TEST(TQueue, can_get_begin_of_queue)
{
	TQueue<int> qu(3);
	qu.Push(1);
	qu.Push(2);

	EXPECT_EQ(1, qu.Begin());
}

TEST(TQueue, throw_when_get_begin_from_empty_queue)
{
	TQueue<int> qu(3);

	ASSERT_ANY_THROW(qu.Begin());
}

TEST(TQueue, can_get_end_of_queue)
{
	TQueue<int> qu(3);
	qu.Push(1);
	qu.Push(2);

	EXPECT_EQ(1, qu.End());
}

TEST(TQueue, throw_when_get_end_from_empty_queue)
{
	TQueue<int> qu(3);

	ASSERT_ANY_THROW(qu.End());
}

TEST(TQueue, can_get_empty)
{
	TQueue<int> qu(2);

	EXPECT_EQ(true, qu.IsEmpty());
}

TEST(TQueue, can_get_not_empty)
{
	TQueue<int> qu(2);
	qu.Push(1);

	EXPECT_EQ(false, qu.IsEmpty());
}

TEST(TQueue, can_get_full)
{
	TQueue<int> qu(2);
	qu.Push(1);
	qu.Push(2);

	EXPECT_EQ(true, qu.IsFull());
}

TEST(TQueue, can_get_not_full)
{
	TQueue<int> qu(2);

	EXPECT_EQ(false, qu.IsFull());
}
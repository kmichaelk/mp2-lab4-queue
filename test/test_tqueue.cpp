#include <gtest.h>
#include "queue.h"

TEST(TQueue, can_create_queue)
{
    EXPECT_NO_THROW(TQueue<int> queue(8));
}

TEST(TQueue, fresh_queue_is_empty)
{
    TQueue<int> queue(1);
    EXPECT_EQ(true, queue.empty());
}

TEST(TQueue, cant_poll_from_empty_queue)
{
    TQueue<int> queue(1);
    EXPECT_ANY_THROW(queue.poll());
}

TEST(TQueue, can_push_element)
{
    TQueue<int> queue(8);
    ASSERT_NO_THROW(queue.push(1));
    EXPECT_EQ(1, queue.size());
}

TEST(TQueue, bottom_retrieves_first_element)
{
    TQueue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    EXPECT_EQ(1, queue.bottom());
}

TEST(TQueue, can_shift_element)
{
    TQueue<int> queue(8);
    queue.push(1);
    ASSERT_NO_THROW(queue.shift());
    EXPECT_EQ(0, queue.size());
}

TEST(TQueue, memory_allocation_is_reliable)
{
    TQueue<int> queue(5);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);

    queue.shift();
    queue.shift();

    EXPECT_NO_THROW(queue.push(6));
    EXPECT_NO_THROW(queue.push(7));

    EXPECT_EQ(3, queue.poll());
    EXPECT_EQ(4, queue.poll());
    EXPECT_EQ(5, queue.poll());
    EXPECT_EQ(6, queue.poll());
    EXPECT_EQ(7, queue.poll());
}
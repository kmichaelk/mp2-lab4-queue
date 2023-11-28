#include "cluster.h"

#include "random.h"

TCluster::TCluster(size_t capacity, double intensity, double performance)
    : tasks(capacity)
    , random(0.0, 1.0)
    , intensity(intensity)
    , performance(performance)
    , current(IdleTask)
{}


void TCluster::add_task(const TCluster::Task& task)
{
    stat.total_tasks++;

    if (tasks.full())
    {
        stat.rejected_tasks++;
        return;
    }

    tasks.push(task);
}

const TCluster::Task &TCluster::get_current_task() const noexcept
{
    return current;
}

void TCluster::generate_tasks()
{
    if (random.next() <= intensity)
    {
        add_task(++lastId);
    }
}

void TCluster::perform_cycle()
{
    stat.cycles++;

    if (current == IdleTask)
    {
        if (tasks.empty())
        {
            stat.idle_cycles++;
            return;
        }

        current = tasks.poll();
    }

    if (random.next() > performance)
    {
        return;
    }

    stat.completed_tasks++;
    current = IdleTask;
}

size_t TCluster::get_capacity() const noexcept
{
    return tasks.max_size();
}

bool TCluster::is_idle() const noexcept
{
    return current == IdleTask;
}

const TCluster::PerfStat& TCluster::stats() const noexcept
{
    return stat;
}


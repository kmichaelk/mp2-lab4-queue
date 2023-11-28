#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "queue.h"
#include "random.h"

class TCluster {
public:
    typedef int Task;

    struct PerfStat {
        int total_tasks = 0;
        int completed_tasks = 0;
        int rejected_tasks = 0;
        int cycles = 0;
        int idle_cycles = 0;
    };
private:
    static const Task IdleTask = -1;

    PerfStat stat;

    const double intensity;
    const double performance;

    TQueue<Task> tasks;
    TRandom<double> random;

    Task current;
    Task lastId = 0;
public:
    TCluster(size_t capacity, double intensity, double performance);

    void add_task(const Task& task);
    const Task& get_current_task() const noexcept;

    void generate_tasks();
    void perform_cycle();

    size_t get_capacity() const noexcept;
    bool is_idle() const noexcept;

    const PerfStat& stats() const noexcept;
};

#endif //__CLUSTER_H__

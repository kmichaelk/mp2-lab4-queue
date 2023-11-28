#include <iostream>
#include <cmath>

#include "cluster.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    /* -------------------------------------------- */
    int capacity;
    cout << "Мощность кластера (максимальное количество заданий): ";
    cin >> capacity;

    double intensity;
    cout << "Интенсивность потока заданий: ";
    cin >> intensity;

    double performance;
    cout << "Производительность кластера: ";
    cin >> performance;

    int T;
    cout << "Количество тактов: ";
    cin >> T;

    cout << endl;
    /* -------------------------------------------- */

    TCluster cluster(capacity, intensity, performance);

    for (int i = 0; i < T; i++)
    {
        cluster.generate_tasks();
        cluster.perform_cycle();
    }

    const auto& stat = cluster.stats();
    //
    const double rejection_percentage = static_cast<double>(stat.rejected_tasks) / stat.total_tasks;
    const int average_cycles = static_cast<int>(round(static_cast<double>(stat.cycles - stat.idle_cycles) / stat.completed_tasks));
    const double idle_percentage = static_cast<double>(stat.idle_cycles) / stat.cycles;
    //

    cout << "Количество поступивших в систему заданий: " << stat.total_tasks << endl;
    cout << "Количество отказов в обслуживании из-за переполнения очереди: " << (100 * rejection_percentage) << "%" << endl;
    cout << "Среднее количество тактов выполнения задания: " << average_cycles << endl;
    cout << "Количество тактов простоя процессора из-за отсутствия заданий: " << (100 * idle_percentage) << "%" << endl;

    return EXIT_SUCCESS;
}
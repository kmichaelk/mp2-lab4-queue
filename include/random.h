#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>

template<typename T>
class TRandom {
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_real_distribution<T> dist;
public:
    TRandom(T begin, T end);

    [[nodiscard]]
    T next();
};

template<typename T>
TRandom<T>::TRandom(T begin, T end)
    : mt(rd())
    , dist(begin, end)
{}

template<typename T>
T TRandom<T>::next()
{
    return dist(mt);
}

#endif // __RANDOM_H__

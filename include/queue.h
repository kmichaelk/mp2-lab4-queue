#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "stack.h"
#include "linkedlist.h"

template<typename T, template<typename> class TContainer>
class TBaseQueue : public TStack<T, TContainer>
{
    using TStack<T, TContainer>::list;
private:
    const size_t capacity;
public:
    explicit TBaseQueue(size_t capacity);

    bool full() const noexcept;

    T& bottom() noexcept;

    void push(const T& element);
    void push(T&& element);

    void shift();
    [[nodiscard]]
    T poll();
    T& peek();

    size_t max_size() const noexcept;
};

template<typename T>
using TQueue = TBaseQueue<T, TLinkedList>;

//

template<typename T, template<typename> class TContainer>
TBaseQueue<T, TContainer>::TBaseQueue(size_t capacity)
        : TStack<T, TContainer>(capacity)
        , capacity(capacity)
{}

template<typename T, template<typename> class TContainer>
bool TBaseQueue<T, TContainer>::full() const noexcept
{
    return list.size() == capacity;
}

template<typename T, template<typename> class TContainer>
T& TBaseQueue<T, TContainer>::bottom() noexcept
{
    this->require_not_empty();
    return list.front();
}

template<typename T, template<typename> class TContainer>
void TBaseQueue<T, TContainer>::push(const T &element)
{
    if (full())
    {
        throw std::overflow_error("Queue is full");
    }
    list.push_back(element);
}

template<typename T, template<typename> class TContainer>
void TBaseQueue<T, TContainer>::push(T&& element)
{
    push(element);
}

template<typename T, template<typename> class TContainer>
void TBaseQueue<T, TContainer>::shift()
{
    this->require_not_empty();
    list.remove(0);
}

template<typename T, template<typename> class TContainer>
T TBaseQueue<T, TContainer>::poll()
{
    this->require_not_empty();
    T element = list[0];
    list.remove(0);
    return element;
}

template<typename T, template<typename> class TContainer>
T& TBaseQueue<T, TContainer>::peek()
{
    this->require_not_empty();
    return list[0];
}

template<typename T, template<typename> class TContainer>
size_t TBaseQueue<T, TContainer>::max_size() const noexcept
{
    return capacity;
}

#endif // __QUEUE_H__

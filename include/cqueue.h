#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include "queue.h"
#include "arraylist.h"

template<typename T>
class TCircularQueue : public TStack<T, TArrayList>
{
    using TStack<T, TArrayList>::list;
private:
    const size_t capacity;
    size_t length;
    size_t idxBegin, idxEnd;

    size_t translate_index(size_t idx) noexcept;
    void update_constraints() noexcept;

    void require_not_empty() const;
public:
    explicit TCircularQueue(size_t capacity);

    bool full() const noexcept;
    bool empty() const noexcept;

    T& top();
    T& bottom();

    void push(const T& element);
    void push(T&& element);


    void pop();
    [[nodiscard]]
    T pop_element();

    void shift();
    [[nodiscard]]
    T poll();
    T& peek();

    size_t size() const noexcept;
    size_t max_size() const noexcept;
};

//

template<typename T>
TCircularQueue<T>::TCircularQueue(size_t capacity)
        : TStack<T, TArrayList>(capacity)
        , capacity(capacity)
        , length(0)
        , idxBegin(0)
        , idxEnd(0)
{
    list.reserve(capacity);
}

template<typename T>
size_t TCircularQueue<T>::translate_index(size_t idx) noexcept
{
    idx += idxBegin;
    if (idx > length) {
        idx -= length;
    }
    return idx;
}

template<typename T>
void TCircularQueue<T>::update_constraints() noexcept
{
    idxBegin %= capacity;
    idxEnd %= capacity;
}

template<typename T>
bool TCircularQueue<T>::full() const noexcept
{
    return length == capacity;
}

template<typename T>
bool TCircularQueue<T>::empty() const noexcept
{
    return length == 0;
}

template<typename T>
T& TCircularQueue<T>::top()
{
    this->require_not_empty();
    return list[idxEnd];
}

template<typename T>
T& TCircularQueue<T>::bottom()
{
    this->require_not_empty();
    return list[idxBegin];
}

template<typename T>
void TCircularQueue<T>::push(const T& element)
{
    if (full())
    {
        throw std::overflow_error("Queue is full");
    }

    list[idxEnd] = element;
    idxEnd++;
    length++;

    update_constraints();
}

template<typename T>
void TCircularQueue<T>::push(T&& element)
{
    push(element);
}

template<typename T>
void TCircularQueue<T>::shift()
{
    this->require_not_empty();

    idxBegin++;
    length--;

    update_constraints();
}

template<typename T>
T TCircularQueue<T>::poll()
{
    this->require_not_empty();

    T element = list[idxBegin];

    idxBegin++;
    length--;
    update_constraints();

    return element;
}

template<typename T>
T& TCircularQueue<T>::peek()
{
    this->require_not_empty();
    return list[idxBegin];
}

template<typename T>
void TCircularQueue<T>::pop()
{
    this->require_not_empty();

    idxEnd--;
    length--;
    update_constraints();
}

template<typename T>
T TCircularQueue<T>::pop_element()
{
    this->require_not_empty();

    T element = list[idxEnd];

    idxEnd--;
    length--;
    update_constraints();

    return element;
}

template<typename T>
size_t TCircularQueue<T>::size() const noexcept
{
    return length;
}

template<typename T>
size_t TCircularQueue<T>::max_size() const noexcept
{
    return capacity;
}

template<typename T>
void TCircularQueue<T>::require_not_empty() const
{
    if (empty())
        throw std::logic_error("Queue is empty");
}

#endif // __CIRCULAR_QUEUE_H__

#ifndef __STACK_H__
#define __STACK_H__

#include "arraylist.h"
#include <stdexcept>

template<typename T, template<typename> class TContainer>
class TStack
{
protected:
    TContainer<T> list;

    void require_not_empty() const;
public:
    typedef T value_type;

    explicit TStack(size_t initial_capacity = 8);

    void push(const T& element);
    void push(T&& element);

    T& top();

    void pop();
    [[nodiscard]]
    T pop_element();

    bool empty() const noexcept(noexcept(list.empty()));
    size_t size() const noexcept(noexcept(list.size()));
};

//

template<typename T, template<typename> class TContainer>
TStack<T, TContainer>::TStack(size_t initial_capacity)
        : list(initial_capacity)
{}

template<typename T, template<typename> class TContainer>
void TStack<T, TContainer>::push(const T &element)
{
    list.push_back(element);
}

template<typename T, template<typename> class TContainer>
void TStack<T, TContainer>::push(T &&element)
{
    push(element);
}

template<typename T, template<typename> class TContainer>
T &TStack<T, TContainer>::top()
{
    require_not_empty();
    return list.back();
}

template<typename T, template<typename> class TContainer>
void TStack<T, TContainer>::pop()
{
    require_not_empty();
    list.remove(list.size() - 1);
}

template<typename T, template<typename> class TContainer>
T TStack<T, TContainer>::pop_element()
{
    require_not_empty();

    T element = list[list.size() - 1];
    list.remove(list.size() - 1);
    return element;
}

template<typename T, template<typename> class TContainer>
bool TStack<T, TContainer>::empty() const noexcept(noexcept(list.empty()))
{
    return list.empty();
}

template<typename T, template<typename> class TContainer>
size_t TStack<T, TContainer>::size() const noexcept(noexcept(list.size()))
{
    return list.size();
}

template<typename T, template<typename> class TContainer>
void TStack<T, TContainer>::require_not_empty() const
{
    if (empty())
        throw std::logic_error("Stack is empty");
}

#endif // __STACK_H__

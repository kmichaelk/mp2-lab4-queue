#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdexcept>
#include <cassert>

template<class T>
class TLinkedList {
private:
    size_t length;
    struct Node {
        T value;
        Node *next = nullptr;
    } *first, *last;

    Node* get_node(size_t idx) const;
    void destroy_nodes();
public:
    typedef T value_type;

    explicit TLinkedList(size_t = 0);
    TLinkedList(const TLinkedList& src);
    TLinkedList(TLinkedList&& src) noexcept;

    ~TLinkedList();

    [[nodiscard]]
    size_t size() const noexcept;
    [[nodiscard]]
    bool empty() const noexcept;

    void push_back(const T& element);
    void push_back(T&& element);

    void push_front(const T& element);
    void push_front(T&& element);

    void insert(size_t pos, const T& element);
    void insert(size_t pos, T&& element);

    void remove(size_t idx);

    T& front();
    T& back();

    T& at(size_t idx);
    const T& at(size_t idx) const;

    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

    bool operator==(const TLinkedList& other) const noexcept;
    bool operator!=(const TLinkedList& other) const noexcept;

    TLinkedList& operator=(const TLinkedList& other);
    TLinkedList& operator=(TLinkedList&& other) noexcept;

    void clear();

    friend void swap(TLinkedList& lhs, TLinkedList& rhs) noexcept
    {
        std::swap(lhs.length, rhs.length);
        std::swap(lhs.first, rhs.first);
        std::swap(lhs.last, rhs.last);
    }
};

template<class T>
typename TLinkedList<T>::Node* TLinkedList<T>::get_node(size_t idx) const
{
    Node* node = first;
    for (size_t i = 0; i < idx; i++)
        node = node->next;
    return node;
}

template<class T>
void TLinkedList<T>::destroy_nodes()
{
    Node *current = first, *garbage;
    while (current) {
        garbage = current;
        current = garbage->next;
        delete garbage;
    }
}

template<class T>
TLinkedList<T>::TLinkedList(size_t)
        : length(0)
        , first(nullptr)
        , last(nullptr)
{}

template<class T>
TLinkedList<T>::TLinkedList(const TLinkedList<T>& src)
        : length(src.length)
{
    if (!src.first) {
        first = last = nullptr;
        return;
    }

    Node *current, *c_src = src.first;
    first = current = new Node { src.first };
    while (c_src->next)
    {
        current->next = new Node { c_src->value };
        current = current->next;
        c_src = c_src->next;
    }
    last = current;
}

template<class T>
TLinkedList<T>::TLinkedList(TLinkedList &&src) noexcept
        : first(nullptr)
        , last(nullptr)
{
    swap(*this, src);
}

template<class T>
TLinkedList<T>::~TLinkedList()
{
    destroy_nodes();
}

template<class T>
size_t TLinkedList<T>::size() const noexcept
{
    return length;
}

template<class T>
bool TLinkedList<T>::empty() const noexcept
{
    return length == 0;
}

template<class T>
void TLinkedList<T>::push_back(const T& element)
{
    Node* node = new Node{ element };

    if (first == nullptr)
    {
        first = last = node;
    }
    else
    {
        last->next = node;
        last = node;
    }

    length++;
}

template<class T>
void TLinkedList<T>::push_back(T &&element)
{
    push_back(element);
}

template<class T>
void TLinkedList<T>::push_front(const T& element)
{
    first = new Node { element, first };
    length++;
}

template<class T>
void TLinkedList<T>::push_front(T &&element)
{
    push_front(element);
}

template<class T>
void TLinkedList<T>::insert(size_t pos, const T& element)
{
    assert(pos < length && "Index is out of range");

    Node *node = get_node(pos);
    node->next = new Node { element, node->next };
    length++;
}

template<class T>
void TLinkedList<T>::insert(size_t pos, T &&element)
{
    insert(pos, element);
}

template<class T>
void TLinkedList<T>::remove(size_t idx)
{
    assert(idx < length && "Index is out of range");

    TLinkedList::Node* node;
    if (idx == 0)
    {
        node = first;
        first = node->next;
    }
    else
    {
        TLinkedList::Node* prev = get_node(idx - 1);
        node = prev->next;
        prev->next = node->next;
    }
    delete node;

    length--;
}

template<class T>
T& TLinkedList<T>::front()
{
    assert(length && "List is empty");
    return first->value;
}

template<class T>
T& TLinkedList<T>::back()
{
    assert(length && "List is empty");
    return last->value;
}

template<class T>
T& TLinkedList<T>::at(const size_t idx)
{
    return const_cast<T&>(std::as_const(at(idx)));
}

template<class T>
const T& TLinkedList<T>::at(const size_t idx) const
{
    assert(idx < length && "Index is out of range");
    return (*this)[idx];
}

template<class T>
T& TLinkedList<T>::operator[](const size_t idx)
        {
    return const_cast<T&>(std::as_const(*this)[idx]);
}

template<class T>
const T& TLinkedList<T>::operator[](const size_t idx) const
{
    return get_node(idx)->value;
}

template<class T>
bool TLinkedList<T>::operator==(const TLinkedList<T>& other) const noexcept
{
    if (this == &other)
        return true;

    if (length != other.length)
        return false;

    Node *left = first, *right = other.first;
    for (size_t i = 0; i < length; i++)
    {
        if (left->value != right->value)
        {
            return false;
        }
        left = left->next;
        right = right->next;
    }

    return true;
}

template<class T>
bool TLinkedList<T>::operator!=(const TLinkedList<T>& other) const noexcept
{
    return !(*this == other);
}

template<class T>
TLinkedList<T>& TLinkedList<T>::operator=(const TLinkedList<T>& other)
{
    if (this == &other)
        return *this;

    TLinkedList<T> tmp(other);
    swap(*this, tmp);
    return *this;
}

template<class T>
TLinkedList<T>& TLinkedList<T>::operator=(TLinkedList &&other) noexcept
{
    swap(*this, other);
    return *this;
}

template<class T>
void TLinkedList<T>::clear()
{
    destroy_nodes();
    first = last = nullptr;
    length = 0;
}

#endif // __LINKEDLIST_H__

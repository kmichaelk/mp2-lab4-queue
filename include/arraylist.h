#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include <stdexcept>
#include <cassert>

template<class T>
class TArrayList {
private:
    T *pMem;
    size_t capacity;
    size_t length;

    void expand_if_needed();
public:
    typedef T value_type;

    explicit TArrayList(size_t initial_capacity = 8);

    TArrayList(const TArrayList& src);
    TArrayList(TArrayList&& src) noexcept;

    ~TArrayList();

    T* begin() const;
    T* end() const;

    [[nodiscard]]
    size_t size() const noexcept;
    [[nodiscard]]
    bool empty() const noexcept;

    void push_back(const T& element);
    void push_back(T&& element);

    void insert(size_t pos, const T& element);
    void insert(size_t pos, T&& element);

    void remove(size_t idx);

    T& front();
    T& back();

    T& at(size_t idx);
    const T& at(size_t idx) const;

    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

    bool operator==(const TArrayList& other) const noexcept;
    bool operator!=(const TArrayList& other) const noexcept;

    TArrayList& operator=(const TArrayList& other);
    TArrayList& operator=(TArrayList&& other) noexcept;

    void clear();
    void shrink_to_fit();

    void reserve(size_t len) noexcept;

    friend void swap(TArrayList& lhs, TArrayList& rhs) noexcept
    {
        std::swap(lhs.pMem, rhs.pMem);
        std::swap(lhs.capacity, rhs.capacity);
        std::swap(lhs.length, rhs.length);
    }
};

//

template<class T>
TArrayList<T>::TArrayList(size_t initial_capacity)
        : capacity(initial_capacity > 0
                   ? initial_capacity
                   : throw std::invalid_argument("Initial list capacity should be greater than 0"))
        , length(0)
        , pMem(new T[initial_capacity])
{}

template<class T>
TArrayList<T>::TArrayList(const TArrayList &src)
        : capacity(src.capacity)
        , length(src.length)
        , pMem(new T[src.capacity])
{
    std::copy(src.pMem, src.pMem + length, pMem);
}

template<class T>
TArrayList<T>::TArrayList(TArrayList &&src) noexcept
        : pMem(nullptr)
{
    swap(*this, src);
}

template<class T>
TArrayList<T>::~TArrayList()
{
    delete[] pMem;
}

template<class T>
void TArrayList<T>::expand_if_needed()
{
    if (length < capacity) return;

    //
    const size_t new_capacity = capacity * 2;
    //

    capacity = new_capacity;
    TArrayList<T> tmp(*this);
    swap(*this, tmp);
}

template<class T>
T *TArrayList<T>::begin() const
{
    return pMem;
}

template<class T>
T *TArrayList<T>::end() const
{
    return pMem + length;
}

template<class T>
size_t TArrayList<T>::size() const noexcept
{
    return length;
}

template<class T>
bool TArrayList<T>::empty() const noexcept
{
    return length == 0;
}

template<class T>
void TArrayList<T>::push_back(const T &element)
{
    expand_if_needed();
    pMem[length++] = element;
}

template<class T>
void TArrayList<T>::push_back(T &&element)
{
    push_back(element);
}

template<class T>
void TArrayList<T>::insert(size_t pos, const T &element)
{
    assert(pos < length && "Index is out of range");

    expand_if_needed();
    std::copy(pMem + pos, pMem + length, pMem + pos + 1);
    pMem[pos] = element;
    length++;
}

template<class T>
void TArrayList<T>::insert(size_t pos, T &&element)
{
    insert(pos, element);
}

template<class T>
void TArrayList<T>::remove(size_t idx)
{
    assert(idx < length && "Index is out of range");

    std::copy(pMem + idx + 1, pMem + length, pMem + idx);
    length--;
}

template<class T>
T &TArrayList<T>::front()
{
    return pMem[0];
}

template<class T>
T &TArrayList<T>::back()
{
    return pMem[length - 1];
}

template<class T>
T &TArrayList<T>::at(const size_t idx)
{
    return const_cast<T&>(std::as_const(at(idx)));
}

template<class T>
const T &TArrayList<T>::at(const size_t idx) const
{
    assert(idx < length && "Index is out of range");
    return (*this)[idx];
}

template<class T>
T &TArrayList<T>::operator[](const size_t idx)
{
    return const_cast<T&>(std::as_const(*this)[idx]);
}

template<class T>
const T &TArrayList<T>::operator[](const size_t idx) const
{
    return pMem[idx];
}

template<class T>
bool TArrayList<T>::operator==(const TArrayList &other) const noexcept
{
    if (this == &other)
        return true;

    if (length != other.length)
        return false;

    for (size_t i = 0; i < length; i++)
        if (pMem[i] != other.pMem[i])
            return false;

    return true;
}

template<class T>
bool TArrayList<T>::operator!=(const TArrayList &other) const noexcept
{
    return !(*this == other);
}

template<class T>
TArrayList<T>& TArrayList<T>::operator=(const TArrayList &other)
{
    if (this == &other)
        return *this;

    TArrayList<T> tmp(other);
    swap(*this, tmp);
    return *this;
}

template<class T>
TArrayList<T>& TArrayList<T>::operator=(TArrayList &&other) noexcept
{
    swap(*this, other);
    return *this;
}

template<class T>
void TArrayList<T>::clear()
{
    length = 0;
}

template<class T>
void TArrayList<T>::shrink_to_fit()
{
    capacity = length;
    TArrayList<T> tmp(*this);
    swap(*this, tmp);
}

template<class T>
void TArrayList<T>::reserve(size_t len) noexcept
{
    if (len < capacity) {
        capacity = len;
        TArrayList<T> tmp(*this);
        swap(*this, tmp);
    }
    length = len;
}

#endif // __ARRAYLIST_H__

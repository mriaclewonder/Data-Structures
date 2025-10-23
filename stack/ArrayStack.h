#pragma once
#include <iostream>
#include <stdexcept>

template <class T>
class MyStack
{
public:
    explicit MyStack();
    explicit MyStack(std::size_t maxElements);
    MyStack(const MyStack &other);
    MyStack(MyStack &&other) noexcept;
    MyStack<T> &operator=(const MyStack<T> &other);
    MyStack<T> &operator=(MyStack<T> &&other) noexcept;
    virtual ~MyStack();

    void Push(T data);
    T Pop();
    T &Top();
    const T &Top() const;
    bool isEmpty() const;
    bool isFull() const;
    void Clear();
    std::size_t GetSize() const;

private:
    std::size_t top;
    T *array;
    std::size_t maxSize;
};

// 默认构造
template <class T>
inline MyStack<T>::MyStack() : top(0), maxSize(100), array(new T[maxSize])
{
}

// 有参构造
template <class T>
inline MyStack<T>::MyStack(std::size_t maxElements) : top(0), maxSize(maxElements), array(new T[maxElements])
{
}

// 析构函数
template <class T>
inline MyStack<T>::~MyStack()
{
    delete[] array;
}

// 拷贝构造
template <class T>
inline MyStack<T>::MyStack(const MyStack &other) : top(other.top), maxSize(other.maxSize), array(new T[maxSize])
{
    for (std::size_t i = 0; i < top; ++i)
    {
        array[i] = other.array[i];
    }
}

// 移动构造
template <class T>
inline MyStack<T>::MyStack(MyStack &&other) noexcept : top(other.top), maxSize(other.maxSize), array(other.array)
{
    other.array = nullptr;
    other.top = 0;
    other.maxSize = 0;
}

template <class T>
inline MyStack<T> &MyStack<T>::operator=(const MyStack<T> &other)
{
    if (this == &other)
        return *this;

    T *newarray = new T[other.maxSize];
    for (std::size_t i = 0; i < other.top; ++i)
        newarray[i] = other.array[i];

    delete[] array;
    array = newarray;
    top = other.top;
    maxSize = other.maxSize;

    return *this;
}

template <class T>
inline MyStack<T> &MyStack<T>::operator=(MyStack<T> &&other) noexcept
{
    if (this == &other)
        return *this;

    delete[] array;

    array = other.array;
    top = other.top;
    maxSize = other.maxSize;

    other.array = nullptr;
    other.top = 0;
    other.maxSize = 0;

    return *this;
}

// 入栈
template <class T>
inline void MyStack<T>::Push(T data)
{
    if (isFull())
        throw std::overflow_error("Stack is full. Cannot Push");

    array[top] = data;
    top++;
}

// 出栈
template <class T>
inline T MyStack<T>::Pop()
{
    if (isEmpty())
        throw std::underflow_error("Stack is empty. Cannot Pop.");
    top--;
    return array[top];
}

template <class T>
inline T &MyStack<T>::Top()
{
    if (isEmpty())
        throw std::runtime_error("Stack is Empty. Cannot Top");

    return array[top - 1];
}

template <class T>
const T &MyStack<T>::Top() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Stack is Empty. Cannot Top");
    }
    return array[top - 1];
}

template <class T>
inline bool MyStack<T>::isEmpty() const
{
    return top == 0;
}

template <class T>
inline bool MyStack<T>::isFull() const
{
    return top == maxSize;
}

template <class T>
inline void MyStack<T>::Clear()
{
    top = 0;
}

template <class T>
inline std::size_t MyStack<T>::GetSize() const
{
    return top;
}

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

    /// @brief 入栈
    /// @param data 要入栈的元素
    void Push(T data);

    /// @brief 出栈
    /// @return 出栈的元素
    T Pop();

    /// @brief 获取栈顶元素
    /// @return 栈顶元素的引用
    T &Top();

    /// @brief 获取栈顶元素（常量版本）
    /// @return 栈顶元素的常量引用
    const T &Top() const;

    /// @brief 判断栈是否为空
    /// @return 如果栈为空，返回true；否则返回false
    bool isEmpty() const;

    /// @brief 判断栈是否已满
    /// @return 如果栈已满，返回true；否则返回false
    bool isFull() const;

    /// @brief 清空栈
    void Clear();

    /// @brief 获取栈中元素的数量
    /// @return 栈中元素的数量
    std::size_t GetSize() const;

    /// @brief 获取栈的容量
    /// @return 栈的容量
    std::size_t GetCapacity() const;

private:
    /// @brief 扩容函数，当栈满时调用，自动将栈的容量翻倍
    void Resize();

private:
    std::size_t top;
    T *array;
    std::size_t maxSize;
};

template <class T>
inline MyStack<T>::MyStack() : top(0), maxSize(100), array(new T[maxSize])
{
}

template <class T>
inline MyStack<T>::MyStack(std::size_t maxElements) : top(0), maxSize(maxElements), array(new T[maxElements])
{
}

template <class T>
inline MyStack<T>::~MyStack()
{
    delete[] array;
}

template <class T>
inline MyStack<T>::MyStack(const MyStack &other) : top(other.top), maxSize(other.maxSize), array(new T[maxSize])
{
    for (std::size_t i = 0; i < top; ++i)
    {
        array[i] = other.array[i];
    }
}

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

template <class T>
inline void MyStack<T>::Push(T data)
{
    if (isFull())
        Resize(); // 栈满时自动扩容

    array[top] = data;
    top++;
}

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

template <class T>
inline void MyStack<T>::Resize()
{
    std::size_t newSize = maxSize * 2;
    T *newArray = new T[newSize];

    // 拷贝原有的数据
    for (std::size_t i = 0; i < top; ++i)
    {
        newArray[i] = std::move(array[i]);
    }

    delete[] array;
    array = newArray;
    maxSize = newSize;
    std::cout << "Stack resized to " << maxSize << " elements\n"; // 调试信息
}

template <class T>
inline std::size_t MyStack<T>::GetCapacity() const
{
    return maxSize;
}
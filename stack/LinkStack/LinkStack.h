#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

/// @brief 链式栈节点
/// @tparam T 节点存储的数据类型
template <class T>
struct Node
{
public:
    Node(T const &d, Node *n) : _data(d), _next(n) {}
    Node(T &&d, Node *n) : _data(std::move(d)), _next(n) {}

public:
    T _data;
    Node *_next;
};

/// @brief 链式栈
/// @tparam T 栈中存储的数据类型
template <class T>
class LinkStack
{
public:
    LinkStack() noexcept;

    LinkStack(LinkStack const &) = delete;
    LinkStack &operator=(LinkStack const &) = delete;

    LinkStack(LinkStack &&other) noexcept;
    LinkStack &operator=(LinkStack &&other) noexcept;
    ~LinkStack();

    /// @brief 左值入栈
    /// @param val 要入栈的左值
    void push(T const &val);

    /// @brief 右值入栈
    /// @param val 要入栈的右值
    void push(T &&val);

    /// @brief 出栈
    /// @return 出栈的元素
    T pop();

    /// @brief 获取栈顶元素
    /// @return 栈顶元素的引用
    T &top();

    /// @brief 获取栈顶元素（常量引用）
    /// @return 栈顶元素的常量引用
    T const &top() const;

    /// @brief 判断栈是否为空
    /// @return 如果栈为空返回true，否则返回false
    bool isEmpty() const;

    /// @brief 获取栈中元素的数量
    /// @return 栈中元素的数量
    int size() const;

private:
    /// @brief 清空栈
    void clear() noexcept;

private:
    Node<T> *_head;
    int _size;
};

template <class T>
LinkStack<T>::LinkStack() noexcept : _head(nullptr),
                                     _size(0) {}

template <class T>
LinkStack<T>::LinkStack(LinkStack &&other) noexcept
    : _head(other._head),
      _size(other._size)
{
    other._head = nullptr;
    other._size = 0;
}

template <class T>
LinkStack<T> &LinkStack<T>::operator=(LinkStack &&other) noexcept
{
    if (this != &other)
    {
        clear();
        _head = other._head;
        _size = other._size;
        other._head = nullptr;
        other._size = 0;
    }
    return *this;
}

template <class T>
LinkStack<T>::~LinkStack()
{
    clear();
}

template <class T>
void LinkStack<T>::push(T const &val)
{
    Node<T> *newNode = new Node<T>(val, _head);
    _head = newNode;
    ++_size;
}

template <class T>
void LinkStack<T>::push(T &&val)
{
    Node<T> *newNode = new Node<T>(std::move(val), _head);
    _head = newNode;
    ++_size;
}

template <class T>
T LinkStack<T>::pop()
{
    if (isEmpty())
    {
        throw std::underflow_error("LinkStack is empty");
    }

    Node<T> *temp = _head;
    _head = _head->_next;
    --_size;

    T result;
    try
    {
        result = std::move(temp->_data);
    }
    catch (...)
    {
        delete temp; // 确保在移动构造抛出时不会泄漏节点
        throw;
    }
    delete temp;
    return result;
}

template <class T>
T &LinkStack<T>::top()
{
    if (isEmpty())
    {
        throw std::underflow_error("LinkStack is empty");
    }
    return _head->_data;
}

template <class T>
T const &LinkStack<T>::top() const
{
    if (isEmpty())
    {
        throw std::underflow_error("LinkStack is empty");
    }
    return _head->_data;
}

template <class T>
bool LinkStack<T>::isEmpty() const
{
    return _head == nullptr;
}

template <class T>
int LinkStack<T>::size() const
{
    return _size;
}

template <class T>
void LinkStack<T>::clear() noexcept
{
    while (_head)
    {
        Node<T> *tmp = _head;
        _head = _head->_next;
        delete tmp;
    }
    _size = 0;
}

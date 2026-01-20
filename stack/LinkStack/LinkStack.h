#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

/**
 * 节点类
 */
template <class T>
struct Node {
public:
    Node(T const &d, Node *n) : _data(d), _next(n) {}

    Node(T &&d, Node *n) : _data(std::move(d)), _next(n) {}

public:
    // 数据域
    T _data;

    // 指针域
    Node *_next;
};

/**
 * 链式栈
 */
template <class T>
class LinkStack {
public:
    // 构造函数
    LinkStack() noexcept;

    // 禁用拷贝构造
    LinkStack(LinkStack const &) = delete;

    // 禁用拷贝赋值
    LinkStack &operator=(LinkStack const &) = delete;

    // 移动构造
    LinkStack(LinkStack &&other) noexcept;

    // 移动赋值
    LinkStack &operator=(LinkStack &&other) noexcept;

    // 析构函数
    ~LinkStack();

    // 左值入栈
    void push(T const &val);

    // 右值入栈
    void push(T &&val);

    // 出栈
    T pop();

    // 获取栈顶元素
    T &top();

    // 获取栈顶元素
    T const &top() const;

    // 栈是否为空
    bool isEmpty() const;

    // 栈的大小
    int size() const;

private:
    // 清除栈
    void clear() noexcept;

private:
    // 头指针
    Node<T> *_head;

    // 栈大小
    int _size;
};

template <class T>
LinkStack<T>::LinkStack() noexcept : _head(nullptr),
                                     _size(0) {}

template <class T>
LinkStack<T>::LinkStack(LinkStack &&other) noexcept
    : _head(other._head),
      _size(other._size) {
    other._head = nullptr;
    other._size = 0;
}

template <class T>
LinkStack<T> &LinkStack<T>::operator=(LinkStack &&other) noexcept {
    if (this != &other) {
        clear();
        _head = other._head;
        _size = other._size;
        other._head = nullptr;
        other._size = 0;
    }
    return *this;
}

template <class T>
LinkStack<T>::~LinkStack() {
    clear();
}

// 左值入栈
template <class T>
void LinkStack<T>::push(T const &val) {
    Node<T> *newNode = new Node<T>(val, _head);
    _head = newNode;
    ++_size;
}

// 右值入栈
template <class T>
void LinkStack<T>::push(T &&val) {
    Node<T> *newNode = new Node<T>(std::move(val), _head);
    _head = newNode;
    ++_size;
}

template <class T>
T LinkStack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("LinkStack is empty");
    }

    Node<T> *temp = _head;
    _head = _head->_next;
    --_size;

    T result;
    try {
        result = std::move(temp->_data);
    } catch (...) {
        delete temp; // 确保在移动构造抛出时不会泄漏节点
        throw;
    }
    delete temp;
    return result;
}

template <class T>
T &LinkStack<T>::top() {
    if (isEmpty()) {
        throw std::underflow_error("LinkStack is empty");
    }
    return _head->_data;
}

template <class T>
T const &LinkStack<T>::top() const {
    if (isEmpty()) {
        throw std::underflow_error("LinkStack is empty");
    }
    return _head->_data;
}

template <class T>
bool LinkStack<T>::isEmpty() const {
    return _head == nullptr;
}

template <class T>
int LinkStack<T>::size() const {
    return _size;
}

template <class T>
void LinkStack<T>::clear() noexcept {
    while (_head) {
        Node<T> *tmp = _head;
        _head = _head->_next;
        delete tmp;
    }
    _size = 0;
}

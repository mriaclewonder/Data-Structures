#include "LinkStack.h"

// 构造函数
template <typename T>
LinkStack<T>::LinkStack() : head_(nullptr),
                            size_(0) {}

// 析构函数
template <typename T>
LinkStack<T>::~LinkStack() {}

// 左值 入栈
template <typename T>
void LinkStack<T>::push(T const &value) {
    Node<T> *newNode = new Node(value, head_);
    head_ = newNode;
    ++size_;
}

// 右值 入栈
template <typename T>
void LinkStack<T>::push(T &&value) {
    Node<T> *newNode = new Node<T>(value, head_);
    newNode = head_;
    ++size_;
}

// 出栈
template <typename T>
T &LinkStack<T>::pop() const {
    if (isEmpty()) {
        throw "stack is empty";
    }
    return head_->data;
}

// 判空
template <typename T>
bool LinkStack<T>::isEmpty() const {
    return head_ == nullptr;
}

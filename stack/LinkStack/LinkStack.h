#pragma once

template <typename T>
struct Node {
    T data;
    Node *next;

    Node(T const &d, Node *n) : data(d), next(n) {}

    Node(T &&d, Node *n) : data(std::move(d)), next(n) {}
};

template <typename T>
class LinkStack {
private:
public:
    // 构造函数
    explicit LinkStack();
    ~LinkStack();

    void push(T const &value);
    void push(T &&value);
    T &pop() const;

    bool isEmpty() const;

    T &Top() const;

private:
    Node<T> *head_;
    int size_;
};

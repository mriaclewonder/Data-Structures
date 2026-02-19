#ifndef _SINGLELIST_H
#define _SINGLELIST_H

// 节点类型
struct Node
{
    Node(int val) : _data(val), _next(nullptr) {}

    int _data;
    Node *_next;
};

// 单链表
class SingleList
{
public:
    SingleList();
    ~SingleList();

    void insertAtHead(const int val);
    void insertAtTail(const int val);
    void insertAtPosition(const int index, const int val);

    bool remove(const int val);
    bool removeposition(const int pos);

    int size() const;
    bool isEmpty() const;
    void print();
    void clear();
    void reverse();

private:
    Node *_head;
    int _size;
};

#endif
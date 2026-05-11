#ifndef _SINGLELIST_H
#define _SINGLELIST_H

/// @brief 链表节点
struct Node
{
    Node(int val) : _data(val), _next(nullptr) {}

    int _data;
    Node *_next;
};

/// @brief 单链表
class SingleList
{
public:
    SingleList();
    ~SingleList();

    /// @brief 在链表头部插入一个节点
    /// @param val 节点的值
    void insertAtHead(const int val);

    /// @brief 在链表尾部插入一个节点
    /// @param val 节点的值
    void insertAtTail(const int val);

    /// @brief 在指定位置插入一个节点
    /// @param index 插入位置
    /// @param val 节点的值
    void insertAtPosition(const int index, const int val);

    /// @brief 删除第一个匹配的节点
    /// @param val 要删除的节点的值
    /// @return 如果删除成功，返回true；否则返回false
    bool remove(const int val);

    /// @brief 删除指定位置的节点
    /// @param pos 要删除的节点的位置
    /// @return 如果删除成功，返回true；否则返回false
    bool removeAtPosition(const int pos);

    /// @brief 获取链表中节点的数量
    /// @return 链表中节点的数量
    int size() const;

    /// @brief 判断链表是否为空
    /// @return 如果链表为空，返回true；否则返回false
    bool isEmpty() const;

    /// @brief 打印链表中的所有节点
    void print();

    /// @brief 清空链表
    void clear();

    /// @brief 反转链表
    void reverse();

private:
    Node *_head;
    int _size;
};

#endif
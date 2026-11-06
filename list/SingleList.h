#ifndef _SINGLELIST_H
#define _SINGLELIST_H

#include <iostream>

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
    SingleList() : _head(nullptr), _size(0)
    {
    }

    ~SingleList()
    {
        clear();
    }

    /// @brief 在链表头部插入一个节点
    /// @param val 节点的值
    void insertAtHead(const int val)
    {
        Node *temp = new Node(val);
        temp->_next = this->_head;
        this->_head = temp;
        ++this->_size;
    }

    /// @brief 在链表尾部插入一个节点
    /// @param val 节点的值
    void insertAtTail(const int val)
    {
        Node *temp = new Node(val);
        if (this->_head == nullptr)
        {
            this->_head = temp;
        }
        else
        {
            Node *cur = this->_head;
            while (cur->_next != nullptr)
            {
                cur = cur->_next;
            }
            cur->_next = temp;
        }

        this->_size++;
    }

    /// @brief 在指定位置插入一个节点
    /// @param index 插入位置
    /// @param val 节点的值
    void insertAtPosition(const int index, const int val)
    {
        if (index < 0 || index > this->_size)
        {
            std::cout << "index out of list range" << std::endl;
            return;
        }

        Node *temp = new Node(val);
        if (index == 0)
        {
            temp->_next = this->_head;
            this->_head = temp;
        }
        else
        {
            Node *cur = this->_head;
            for (int i = 0; i < index - 1; ++i)
            {
                cur = cur->_next;
            }
            temp->_next = cur->_next;
            cur->_next = temp;
        }

        ++this->_size;
    }

    /// @brief 删除第一个匹配的节点
    /// @param val 要删除的节点的值
    /// @return 如果删除成功，返回true；否则返回false
    bool remove(const int val)
    {
        if (this->_head == nullptr)
            return false;

        if (this->_head->_data == val)
        {
            Node *victim = this->_head;
            this->_head = victim->_next;
            delete victim;
            --this->_size;
            return true;
        }

        Node *cur = this->_head;
        while (cur->_next != nullptr)
        {
            if (cur->_next->_data == val)
            {
                Node *victim = cur->_next;
                cur->_next = victim->_next;
                delete victim;
                --this->_size;
                return true;
            }
            cur = cur->_next;
        }
        return false;
    }

    /// @brief 删除指定位置的节点
    /// @param pos 要删除的节点的位置
    /// @return 如果删除成功，返回true；否则返回false
    bool removeAtPosition(const int pos)
    {
        if (pos < 0 || pos >= this->_size)
        {
            std::cout << "index out if list range" << std::endl;
            return false;
        }

        Node *toDelete = nullptr;
        if (pos == 0)
        {
            toDelete = this->_head;
            this->_head = this->_head->_next;
        }
        else
        {
            Node *cur = this->_head;
            for (int i = 0; i < pos - 1; ++i)
            {
                cur = cur->_next;
            }

            toDelete = cur->_next;
            cur->_next = toDelete->_next;
        }

        delete toDelete;
        this->_size--;
        return true;
    }

    /// @brief 获取链表中节点的数量
    /// @return 链表中节点的数量
    int size() const
    {
        return this->_size;
    }

    /// @brief 判断链表是否为空
    /// @return 如果链表为空，返回true；否则返回false
    bool isEmpty() const
    {
        return this->_size == 0;
    }

    /// @brief 打印链表中的所有节点
    void print()
    {
        if (isEmpty())
        {
            std::cout << "list is empty" << std::endl;
            return;
        }

        Node *cur = this->_head;

        std::cout << "head->";
        while (cur != nullptr)
        {
            std::cout << cur->_data;
            if (cur->_next != nullptr)
            {
                std::cout << "->";
            }
            cur = cur->_next;
        }
        std::cout << "->nullptr" << std::endl;
    }

    /// @brief 清空链表
    void clear()
    {
        while (this->_head != nullptr)
        {
            Node *cur = this->_head;
            this->_head = cur->_next;
            delete cur;
            --this->_size;
        }

        this->_size = 0;
    }

    /// @brief 反转链表
    void reverse()
    {
        Node *prev = nullptr, *next = nullptr, *cur = this->_head;
        while (cur != nullptr)
        {
            next = cur->_next;
            cur->_next = prev;
            prev = cur;
            cur = next;
        }
        this->_head = prev;
    }

private:
    Node *_head;
    int _size;
};

#endif

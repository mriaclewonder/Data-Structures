#pragma once

#include <iostream>
#include <stdexcept>

/// @brief 节点类型
struct Node
{
    Node(int val) : _data(val), _next(nullptr) {}
    int _data;
    Node *_next;
};

/// @brief 单向循环链表
class CircularSingleList
{
public:
    CircularSingleList() : _head(nullptr), _size(0) {}
    ~CircularSingleList() { clear(); }

    CircularSingleList(const CircularSingleList &) = delete;
    CircularSingleList &operator=(const CircularSingleList &) = delete;

    /// @brief 头插法在链表头部插入一个节点
    /// @param val 要插入的值
    void insertAtHead(const int val)
    {
        Node *newNode = new Node(val);
        if (_head == nullptr)
        {
            _head = newNode;
            newNode->_next = newNode;
        }
        else
        {
            Node *cur = _head;
            while (cur->_next != _head)
            {
                cur = cur->_next;
            }
            newNode->_next = _head;
            cur->_next = newNode;
            _head = newNode;
        }
        ++_size;
    }

    /// @brief 尾插法在链表尾部插入一个节点
    /// @param val 要插入的值
    void insertAtTail(const int val)
    {
        Node *newNode = new Node(val);
        if (_head == nullptr)
        {
            _head = newNode;
            newNode->_next = newNode;
        }
        else
        {
            Node *cur = _head;
            while (cur->_next != _head)
            {
                cur = cur->_next;
            }
            cur->_next = newNode;
            newNode->_next = _head;
        }
        ++_size;
    }

    /// @brief 在指定位置插入一个节点
    /// @param index 要插入的位置，0表示在链表头部插入，size()表示在链表尾部插入
    /// @param val 要插入的值
    void insertAtPosition(const int index, const int val)
    {
        if (index < 0 || index > _size)
        {
            throw std::out_of_range("Index out of range");
            return;
        }

        if (index == 0)
        {
            insertAtHead(val);
        }
        else if (index == _size)
        {
            insertAtTail(val);
        }
        else
        {
            Node *newNode = new Node(val);
            Node *cur = _head;
            for (int i = 0; i < index - 1; ++i)
            {
                cur = cur->_next;
            }
            newNode->_next = cur->_next;
            cur->_next = newNode;
            ++_size;
        }
    }

    /// @brief 删除链表中第一个值为val的节点
    /// @param val 要删除的值
    /// @return 删除成功返回true，否则返回false
    bool removeFirstVal(const int val)
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("list is empty");
            return false;
        }

        if (_head->_next == _head)
        {
            if (_head->_data == val)
            {
                delete _head;
                _head = nullptr;
                --_size;
                return true;
            }
            return false;
        }

        if (_head->_data == val)
        {
            Node *tail = _head;
            while (tail->_next != _head)
            {
                tail = tail->_next;
            }
            Node *temp = _head;
            _head = _head->_next;
            tail->_next = _head;
            delete temp;
            --_size;
            return true;
        }

        Node *prev = _head;
        Node *curr = _head->_next;
        while (curr != _head)
        {
            if (curr->_data == val)
            {
                prev->_next = curr->_next;
                delete curr;
                --_size;
                return true;
            }
            prev = curr;
            curr = curr->_next;
        }
        return false;
    }

    /// @brief  删除链表头部节点
    /// @return 删除成功返回true，否则返回false
    bool removeAtHead()
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("list is empty");
            return false;
        }

        if (_head->_next == _head)
        {
            delete _head;
            _head = nullptr;
            --_size;
            return true;
        }

        Node *tail = _head;
        while (tail->_next != _head)
        {
            tail = tail->_next;
        }
        Node *temp = _head;
        _head = _head->_next;
        tail->_next = _head;
        delete temp;
        --_size;
        return true;
    }

    /// @brief  删除链表尾部节点
    /// @return 删除成功返回true，否则返回false
    bool removeAtTail()
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("list is empty");
            return false;
        }

        if (_head->_next == _head)
        {
            delete _head;
            _head = nullptr;
            --_size;
            return true;
        }

        Node *tail = _head;
        Node *prev = nullptr;
        while (tail->_next != _head)
        {
            prev = tail;
            tail = tail->_next;
        }
        prev->_next = _head;
        delete tail;
        --_size;
        return true;
    }

    /// @brief 删除链表中指定位置的节点
    /// @param pos 要删除的位置
    /// @return 删除成功返回true，否则返回false
    bool removePosition(const int pos)
    {
        if (pos < 0 || pos >= _size)
        {
            throw std::out_of_range("Position out of range");
            return false;
        }
        if (pos == 0)
        {
            return removeAtHead();
        }
        else if (pos == _size - 1)
        {
            return removeAtTail();
        }
        else
        {
            Node *prev = _head;
            for (int i = 0; i < pos - 1; ++i)
            {
                prev = prev->_next;
            }
            Node *cur = prev->_next;
            prev->_next = cur->_next;
            delete cur;
            --_size;
            return true;
        }
    }

    /// @brief 获取链表的大小
    /// @return 链表的大小
    int size() const { return _size; }

    /// @brief 判断链表是否为空
    /// @return 如果链表为空返回true，否则返回false
    bool isEmpty() const { return _size == 0; }

    /// @brief 清空链表
    void clear()
    {
        while (!isEmpty())
        {
            removeAtHead();
        }
    }

    /// @brief 反转链表
    void reverse()
    {
        if (_head == nullptr || _head->_next == _head)
        {
            return;
        }

        Node *prev = nullptr;
        Node *curr = _head;
        Node *next = nullptr;
        do
        {
            next = curr->_next;
            curr->_next = prev;
            prev = curr;
            curr = next;
        } while (curr != _head);

        _head->_next = prev;
        _head = prev;
    }

private:
    Node *_head;
    int _size;
};
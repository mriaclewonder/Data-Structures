#pragma once
#include <iostream>
#include <stdexcept>

/// @brief 节点
struct Node
{
    Node(int _val) : _val(_val), _prev(nullptr), _next(nullptr) {}
    int _val;
    Node *_prev;
    Node *_next;
};

/// @brief 双向链表
class DoubleList
{
public:
    DoubleList() : _head(nullptr), _tail(nullptr), _size(0) {}

    ~DoubleList() { clear(); }
    DoubleList(const DoubleList &) = delete;
    DoubleList &operator=(const DoubleList &) = delete;

    /// @brief 重载[]运算符，支持访问链表中的元素
    /// @param index
    /// @return 访问到的元素值
    int operator[](const int index) const
    {
        if (index < 0 || index >= _size)
        {
            throw std::out_of_range("index out of range");
        }

        Node *cur = nullptr;
        if (index <= _size / 2)
        {
            cur = _head;
            for (int i = 0; i < index; ++i)
                cur = cur->_next;
        }
        else
        {
            cur = _tail;
            for (int i = _size - 1; i > index; --i)
                cur = cur->_prev;
        }
        return cur->_val;
    }

    /// @brief 清空链表，释放所有节点的内存
    void clear()
    {
        Node *cur = _head;
        while (cur)
        {
            Node *next = cur->_next;
            delete cur;
            cur = next;
        }
        _head = _tail = nullptr;
        _size = 0;
    }

    /// @brief 在链表头部插入一个新节点，节点值为val
    /// @param val 要插入的节点值
    void push_front(const int val)
    {
        Node *newNode = new Node(val);
        if (_head == nullptr)
        {
            _head = _tail = newNode;
        }
        else
        {
            newNode->_next = _head;
            _head->_prev = newNode;
            _head = newNode;
        }
        ++_size;
    }

    /// @brief 在链表尾部插入一个新节点，节点值为val
    /// @param val 要插入的节点值
    void push_back(const int val)
    {
        Node *newNode = new Node(val);
        if (_tail == nullptr)
        {
            _tail = _head = newNode;
        }
        else
        {
            _tail->_next = newNode;
            newNode->_prev = _tail;
            _tail = newNode;
        }
        ++_size;
    }

    /// @brief 在指定位置插入一个新节点，节点值为val
    /// @param pos 插入位置，0表示在链表头部插入，size()表示在链表尾部插入
    /// @param val 插入节点的值
    void insert(const int pos, const int val)
    {
        if (pos < 0 || pos > _size)
        {
            throw std::out_of_range("insert position out of range");
        }

        if (pos == 0)
        {
            push_front(val);
            return;
        }

        if (pos == _size)
        {
            push_back(val);
            return;
        }

        Node *cur = nullptr;
        if (pos <= _size / 2)
        {
            cur = _head;
            for (int i = 0; i < pos; ++i)
                cur = cur->_next;
        }
        else
        {
            cur = _tail;
            for (int i = _size - 1; i > pos; --i)
                cur = cur->_prev;
        }

        Node *newNode = new Node(val);
        Node *prev = cur->_prev;

        prev->_next = newNode;
        newNode->_prev = prev;
        newNode->_next = cur;
        cur->_prev = newNode;

        ++_size;
    }

    /// @brief 从链表头部删除一个节点
    void pop_front()
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("list is empty");
        }
        Node *temp = _head;
        _head = _head->_next;
        if (_head)
        {
            _head->_prev = nullptr;
        }
        else
        {
            _tail = nullptr;
        }
        delete temp;
        --_size;
    }

    /// @brief 从链表尾部删除一个节点
    void pop_back()
    {
        if (_tail == nullptr)
        {
            throw std::out_of_range("list is empty");
        }

        Node *temp = _tail;
        _tail = temp->_prev;
        if (_tail)
        {
            _tail->_next = nullptr;
        }
        else
        {
            _head = nullptr;
        }
        delete temp;
        --_size;
    }

    /// @brief 删除指定位置的节点
    /// @param index 要删除节点的位置，0表示链表头部，size() - 1表示链表尾部
    void erase(const int index)
    {
        if (index < 0 || index >= _size)
        {
            throw std::out_of_range("index out of range");
        }
        if (index == 0)
        {
            pop_front();
            return;
        }
        if (index == _size - 1)
        {
            pop_back();
            return;
        }
        Node *cur = nullptr;
        if (index < _size / 2)
        {
            cur = _head;
            for (int i = 0; i < index; ++i)
            {
                cur = cur->_next;
            }
        }
        else if (index >= _size / 2)
        {
            cur = _tail;
            for (int i = _size - 1; i > index; --i)
            {
                cur = cur->_prev;
            }
        }

        Node *temp = cur;
        cur->_prev->_next = cur->_next;
        cur->_next->_prev = cur->_prev;
        delete temp;
        --_size;
    }

    /// @brief 获取链表头部节点的值
    /// @return 链表头部节点的值
    int front() const
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("list is empty");
        }
        return _head->_val;
    }

    /// @brief 获取链表尾部节点的值
    /// @return 链表尾部节点的值
    int back() const
    {
        if (_tail == nullptr)
        {
            throw std::out_of_range("list is empty");
        }
        return _tail->_val;
    }

    /// @brief 获取链表中节点的数量
    /// @return 链表中节点的数量
    int size() const
    {
        return _size;
    }

    /// @brief 判断链表是否为空
    /// @return 如果链表为空，返回true；否则返回false
    bool empty() const
    {
        return _size == 0;
    }

private:
    Node *_head;
    Node *_tail;
    int _size;
};
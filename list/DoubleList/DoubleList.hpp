#pragma once
#include <iostream>
#include <stdexcept>

struct Node
{
    Node(int _val) : _val(_val), _prev(nullptr), _next(nullptr) {}
    int _val;
    Node *_prev;
    Node *_next;
};

class DoubleList
{
public:
    DoubleList() : _head(nullptr), _tail(nullptr), _size(0) {}

    ~DoubleList() { clear(); }
    DoubleList(const DoubleList &) = delete;
    DoubleList &operator=(const DoubleList &) = delete;

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

    int front() const
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("list is empty");
        }
        return _head->_val;
    }

    int back() const
    {
        if (_tail == nullptr)
        {
            throw std::out_of_range("list is empty");
        }
        return _tail->_val;
    }

    int size() const
    {
        return _size;
    }

    bool empty() const
    {
        return _size == 0;
    }

private:
    Node *_head;
    Node *_tail;
    int _size;
};
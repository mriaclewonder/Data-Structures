#include "SingleList.h"
#include <iostream>
// 无参构造
SingleList::SingleList() : _head(nullptr), _size(0)
{
}

// 析构函数
SingleList::~SingleList()
{
    clear();
}

// 头插法
void SingleList::insertAtHead(const int val)
{
    Node *temp = new Node(val);
    temp->_next = this->_head;
    this->_head = temp;
    ++this->_size;
}

// 尾插法
void SingleList::insertAtTail(const int val)
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

// 指定位置插入
void SingleList::insertAtPosition(const int index, const int val)
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

// 移除当前链表中和val值相同的元素
bool SingleList::remove(const int val)
{
    if (isEmpty())
        return false;

    while (this->_head != nullptr && this->_head->_data == val)
    {
        Node *temp = this->_head;
        this->_head = this->_head->_next;
        delete temp;
        this->_size--;
    }

    if (this->_head == nullptr)
        return true;

    Node *cur = this->_head;
    while (cur->_next != nullptr)
    {
        if (cur->_next->_data == val)
        {
            Node *temp = cur->_next;
            cur->_next = temp->_next;
            delete temp;
            this->_size--;
        }
        else
        {
            cur = cur->_next;
        }
    }
    return true;
}

// 移除当前列表中指定位置的值
bool SingleList::removeAtPosition(const int pos)
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

// 获取当前链表大小
int SingleList::size() const
{
    return this->_size;
}

// 判断当前列表是否为空
bool SingleList::isEmpty() const
{
    return this->_size == 0;
}

// 打印整个链表
void SingleList::print()
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

// 清空链表
void SingleList::clear()
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

// 反转链表
void SingleList::reverse()
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
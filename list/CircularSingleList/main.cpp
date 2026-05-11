#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define private public
#include "CircularSingleList.hpp"
#undef private

namespace
{
std::vector<int> snapshot(const CircularSingleList &list)
{
    std::vector<int> values;
    Node *cur = list._head;
    for (int i = 0; i < list._size; ++i)
    {
        if (cur == nullptr)
        {
            throw std::runtime_error("Encountered nullptr before reaching size()");
        }
        values.push_back(cur->_data);
        cur = cur->_next;
    }
    return values;
}

void assertRingClosed(const CircularSingleList &list)
{
    if (list._size == 0)
    {
        if (list._head != nullptr)
        {
            throw std::runtime_error("Empty list should keep _head == nullptr");
        }
        return;
    }

    Node *cur = list._head;
    for (int i = 0; i < list._size; ++i)
    {
        if (cur == nullptr)
        {
            throw std::runtime_error("Encountered nullptr while checking the ring");
        }
        cur = cur->_next;
    }
    if (cur != list._head)
    {
        throw std::runtime_error("Ring is not closed back to _head after size() steps");
    }
}

std::string formatValues(const std::vector<int> &values)
{
    std::ostringstream oss;
    oss << "[";
    for (std::size_t i = 0; i < values.size(); ++i)
    {
        if (i > 0)
        {
            oss << ", ";
        }
        oss << values[i];
    }
    oss << "]";
    return oss.str();
}

void expectSequence(const CircularSingleList &list, const std::vector<int> &expected, const std::string &name)
{
    const std::vector<int> actual = snapshot(list);
    if (actual != expected)
    {
        throw std::runtime_error(name + " expected " + formatValues(expected) + ", got " + formatValues(actual));
    }
    assertRingClosed(list);
}

void expect(bool condition, const std::string &message)
{
    if (!condition)
    {
        throw std::runtime_error(message);
    }
}

template <typename Callable>
void expectThrows(const std::string &name, Callable callable)
{
    try
    {
        callable();
    }
    catch (const std::out_of_range &)
    {
        return;
    }
    throw std::runtime_error(name + " expected std::out_of_range");
}
} // namespace

int main()
{
    try
    {
        CircularSingleList list;
        expect(list.isEmpty(), "New list should be empty");
        expect(list.size() == 0, "New list size should be 0");

        list.insertAtHead(2);
        list.insertAtHead(1);
        list.insertAtTail(3);
        list.insertAtTail(4);
        expectSequence(list, {1, 2, 3, 4}, "Head/tail insertion");
        expect(list.size() == 4, "Size should be 4 after four insertions");

        list.insertAtPosition(2, 99);
        expectSequence(list, {1, 2, 99, 3, 4}, "Middle insertion");

        expect(list.removeFirstVal(99), "removeFirstVal should delete an existing middle value");
        expectSequence(list, {1, 2, 3, 4}, "removeFirstVal after deleting 99");

        list.insertAtTail(2);
        expectSequence(list, {1, 2, 3, 4, 2}, "Tail insertion with duplicate");
        expect(list.removeFirstVal(2), "removeFirstVal should remove the first duplicate only");
        expectSequence(list, {1, 3, 4, 2}, "removeFirstVal duplicate behavior");

        expect(list.removeAtHead(), "removeAtHead should succeed on non-empty list");
        expectSequence(list, {3, 4, 2}, "removeAtHead");

        expect(list.removeAtTail(), "removeAtTail should succeed on non-empty list");
        expectSequence(list, {3, 4}, "removeAtTail");

        list.insertAtTail(5);
        list.insertAtTail(6);
        expectSequence(list, {3, 4, 5, 6}, "Rebuild before removePosition");

        expect(list.removePosition(1), "removePosition should delete middle node");
        expectSequence(list, {3, 5, 6}, "removePosition middle");

        list.reverse();
        expectSequence(list, {6, 5, 3}, "reverse");

        list.clear();
        expect(list.isEmpty(), "List should be empty after clear");
        expect(list.size() == 0, "Size should be 0 after clear");
        assertRingClosed(list);

        expectThrows("removeAtHead on empty list", [&]() { list.removeAtHead(); });
        expectThrows("removeAtTail on empty list", [&]() { list.removeAtTail(); });
        expectThrows("removeFirstVal on empty list", [&]() { list.removeFirstVal(1); });
        expectThrows("removePosition on empty list", [&]() { list.removePosition(0); });
        expectThrows("insertAtPosition out of range", [&]() { list.insertAtPosition(1, 10); });

        std::cout << "All CircularSingleList tests passed." << std::endl;
        return 0;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Test failed: " << ex.what() << std::endl;
        return 1;
    }
}

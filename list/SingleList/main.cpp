#include "SingleList.h"
#include <iostream>

int main()
{
    SingleList list;

    std::cout << "=== 测试插入功能 ===\n";
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtHead(1);
    list.print(); // 预期: head->1->2->3->nullptr

    list.insertAtTail(4);
    list.insertAtTail(5);
    list.print(); // 预期: head->1->2->3->4->5->nullptr

    list.insertAtPosition(2, 99); // 在索引2处插入99
    list.print();                 // 预期: head->1->2->99->3->4->5->nullptr

    std::cout << "当前大小: " << list.size() << "\n\n"; // 预期: 6

    std::cout << "=== 测试按值删除 ===\n";
    list.remove(99); // 删除中间元素
    list.print();    // 预期: head->1->2->3->4->5->nullptr

    list.remove(1); // 删除头节点
    list.print();   // 预期: head->2->3->4->5->nullptr

    bool removed = list.remove(100);                                     // 删除不存在的值
    std::cout << "删除100结果: " << (removed ? "成功" : "失败") << "\n"; // 预期: 失败
    list.print();                                                        // 不变: head->2->3->4->5->nullptr

    list.remove(5); // 删除尾节点
    list.print();   // 预期: head->2->3->4->nullptr

    std::cout << "\n=== 测试按位置删除 ===\n";
    list.removeposition(0); // 删除头节点（索引0）
    list.print();           // 预期: head->3->4->nullptr

    list.removeposition(1); // 删除第二个节点（索引1，即值为4）
    list.print();           // 预期: head->3->nullptr

    list.removeposition(1); // 索引越界（当前size=1，索引1无效）
    // 预期输出: index out of range
    list.print(); // 不变: head->3->nullptr

    std::cout << "\n=== 测试反转 ===\n";
    list.insertAtTail(5);
    list.insertAtTail(7); // 当前: 3->5->7
    list.print();         // 预期: head->3->5->7->nullptr
    list.reverse();
    list.print(); // 预期: head->7->5->3->nullptr

    std::cout << "\n=== 测试清空与判空 ===\n";
    list.clear();
    std::cout << "清空后大小: " << list.size() << "\n";                  // 预期: 0
    std::cout << "是否为空: " << (list.isEmpty() ? "是" : "否") << "\n"; // 预期: 是
    list.print();                                                        // 预期: list is empty

    std::cout << "\n=== 测试边界插入 ===\n";
    list.insertAtPosition(0, 10); // 空链表插入索引0
    list.print();                 // 预期: head->10->nullptr
    list.insertAtPosition(1, 20); // 尾部插入
    list.print();                 // 预期: head->10->20->nullptr
    list.insertAtPosition(5, 30); // 越界插入，应提示错误
    // 预期输出: index out of list range

    return 0;
}
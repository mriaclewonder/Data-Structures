#include "LinkStack.h"
#include <iostream>
#include <stdexcept>
#include <string>

void testBasicOperations() {
    std::cout << "=== 测试基本操作 ===\n";

    LinkStack<int> stack;

    // 测试空栈
    std::cout << "栈是否为空: " << (stack.isEmpty() ? "是" : "否") << std::endl;
    std::cout << "栈大小: " << stack.size() << std::endl;

    // 测试入栈和出栈
    std::cout << "\n=== 测试入栈和出栈 ===\n";

    for (int i = 1; i <= 5; ++i) {
        std::cout << "入栈: " << i << std::endl;
        stack.push(i);
        std::cout << "栈顶元素: " << stack.top() << std::endl;
    }

    std::cout << "栈大小: " << stack.size() << std::endl;

    std::cout << "\n=== 出栈 ===\n";
    while (!stack.isEmpty()) {
        std::cout << "栈顶元素: " << stack.top() << std::endl;
        int val = stack.pop();
        std::cout << "出栈: " << val << std::endl;
        std::cout << "栈大小: " << stack.size() << std::endl;
    }
}

void testStringStack() {
    std::cout << "\n=== 测试字符串栈 ===\n";

    LinkStack<std::string> strStack;

    // 测试左值入栈
    std::string str1 = "Hello";
    std::string str2 = "World";

    strStack.push(str1);
    strStack.push(str2);

    std::cout << "入栈后栈大小: " << strStack.size() << std::endl;
    std::cout << "栈顶元素: " << strStack.top() << std::endl;

    // 测试右值入栈
    strStack.push("C++");
    strStack.push("Stack");

    std::cout << "右值入栈后栈大小: " << strStack.size() << std::endl;

    while (!strStack.isEmpty()) {
        std::cout << "出栈: " << strStack.pop() << std::endl;
    }
}

void testMoveOperations() {
    std::cout << "\n=== 测试移动操作 ===\n";

    LinkStack<int> stack1;
    for (int i = 1; i <= 3; ++i) {
        stack1.push(i);
    }

    std::cout << "stack1 初始大小: " << stack1.size() << std::endl;

    // 测试移动构造函数
    LinkStack<int> stack2(std::move(stack1));
    std::cout << "移动构造后:\n";
    std::cout << "stack1 大小: " << stack1.size() << std::endl;
    std::cout << "stack2 大小: " << stack2.size() << std::endl;

    // 测试移动赋值运算符
    LinkStack<int> stack3;
    stack3 = std::move(stack2);
    std::cout << "移动赋值后:\n";
    std::cout << "stack2 大小: " << stack2.size() << std::endl;
    std::cout << "stack3 大小: " << stack3.size() << std::endl;

    std::cout << "stack3 中的元素: ";
    while (!stack3.isEmpty()) {
        std::cout << stack3.pop() << " ";
    }
    std::cout << std::endl;
}

void testExceptionHandling() {
    std::cout << "\n=== 测试异常处理 ===\n";

    LinkStack<int> stack;

    try {
        // 尝试从空栈获取栈顶元素
        int top = stack.top();
        std::cout << "栈顶元素: " << top << std::endl;
    } catch (std::underflow_error const &e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }

    try {
        // 尝试从空栈出栈
        int val = stack.pop();
        std::cout << "出栈元素: " << val << std::endl;
    } catch (std::underflow_error const &e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "开始测试 LinkStack 类\n";

    try {
        testBasicOperations();
        testStringStack();
        testMoveOperations();
        testExceptionHandling();

        std::cout << "\n所有测试完成\n";
    } catch (std::exception const &e) {
        std::cerr << "测试过程中发生异常: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

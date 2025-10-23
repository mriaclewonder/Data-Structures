#include <iostream>
#include "ArrayStack.h"

int main()
{
    // 1. 创建栈
    MyStack<int> stack(5);

    // 2. 入栈操作
    std::cout << "Pushing elements: ";
    for (int i = 1; i <= 5; ++i)
    {
        stack.Push(i * 10);
        std::cout << i * 10 << " ";
    }
    std::cout << std::endl;

    // 3. 查看栈顶
    std::cout << "Top element: " << stack.Top() << std::endl;

    // 4. 获取栈大小
    std::cout << "Stack size: " << stack.GetSize() << std::endl;

    // 5. 出栈操作
    std::cout << "Popping elements: ";
    while (!stack.isEmpty())
    {
        std::cout << stack.Pop() << " ";
    }
    std::cout << std::endl;

    // 6. 检查栈空
    std::cout << "Stack is empty: " << (stack.isEmpty() ? "Yes" : "No") << std::endl;

    // 7. 异常处理示例
    try
    {
        stack.Pop(); // 这会抛出异常
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
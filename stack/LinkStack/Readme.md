** 为什么要禁用拷贝构造和拷贝赋值？**

```c++
// 默认拷贝构造（浅拷贝）会导致：
LinkStack<int> stack1;
stack1.push(1);
LinkStack<int> stack2 = stack1;  // 浅拷贝！

// 现在 stack1._head 和 stack2._head 指向同一个链表
// 析构时会导致双重释放（double free）错误
```

** 什么时候不能使用std::move? **
```c++
std::vector<int> func() {
    std::vector<int> result;
    // ... 
    return result;          // ✓ 让编译器优化
    // return std::move(result);  // ✗ 可能阻止 RVO
}

const std::string s = "hello";
auto s2 = std::move(s);  // 无效！仍然会拷贝


int x = 10;
int y = std::move(x);  // 无意义，仍然是拷贝


std::string s1 = "text";
std::string s2 = std::move(s1);

// 此时 s1 状态有效但未指定
// 不要依赖 s1 的内容（可能为空）
```
只在确定要放弃原对象所有权时使用 std::move，它只是将左值转换为右值引用，实际的移动操作由类的移动构造函数/赋值运算符完成。
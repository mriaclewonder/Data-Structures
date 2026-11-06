# Data-Structures

## 项目简介

这是一个使用 C++11 实现常见数据结构的练习项目，目前包含链表和栈的多种实现。

每个实现都配有一个独立的测试入口（`test_*.cpp`），既可以单独编译运行，也可以通过 CTest 批量执行。所有测试统一由根目录的 CMake 管理。

## 环境要求

- CMake 3.25 及以上
- 支持 C++11 的编译器，例如 MSVC、GCC、Clang
- 推荐使用 CLion、VS Code + CMake Tools 或 Visual Studio

## 构建与测试

在仓库根目录执行：

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Windows 上使用 MinGW 时可以显式指定生成器：

```bash
cmake -S . -B build -G "MinGW Makefiles"
```

可执行文件统一输出到构建目录下的 `bin/`（多配置生成器会再套一层 `Debug` / `Release`），不会写入源码树：

```text
build/
└── bin/
    ├── test_singlelist
    ├── test_doublelist
    └── ...
```

单独构建或运行某个测试：

```bash
cmake --build build --target test_doublelist
build/bin/test_doublelist.exe        # Windows
./build/bin/test_doublelist          # Linux / macOS
```

> 根目录的 `CMakeLists.txt` 提供了 `ds_add_test(<名字>)` 函数：在模块目录里放一个 `<名字>.cpp`，再在对应 `CMakeLists.txt` 里加一行 `ds_add_test(<名字>)`，就会自动生成可执行文件、加入头文件路径并注册到 CTest。因此不再需要为每个模块单独写 `CMakeLists.txt`。

## 目录结构

```text
.
├── CMakeLists.txt              # 统一构建入口、全局编译选项、ds_add_test()
├── list
│   ├── CMakeLists.txt
│   ├── SingleList.h            # 单链表
│   ├── DoubleList.hpp          # 双向链表
│   ├── CircularSingleList.hpp  # 单向循环链表
│   ├── test_singlelist.cpp
│   ├── test_doublelist.cpp
│   └── test_circle_singlelist.cpp
└── stack
    ├── CMakeLists.txt
    ├── ArrayStack.h            # 顺序栈（模板）
    ├── LinkStack.h             # 链式栈（模板）
    ├── QueueAsAStackImplementation.h  # 用队列实现栈（暂未接入构建）
    ├── test_arraystack.cpp
    └── test_linkstack.cpp
```

## 已实现的数据结构

### 链表（`list/`）

| 类 | 文件 | 已实现功能 |
| --- | --- | --- |
| `SingleList` | `SingleList.h` | 头插、尾插、按位置插入、按值删除、按位置删除、反转、清空、判空、获取长度、打印 |
| `DoubleList` | `DoubleList.hpp` | `push_front`、`push_back`、按位置插入、按位置删除、头删、尾删、`front` / `back` 访问、下标访问、清空、判空、获取长度 |
| `CircularSingleList` | `CircularSingleList.hpp` | 头插、尾插、按位置插入、删除头结点、删除尾结点、按值删除首个匹配、按位置删除、反转、清空、判空、获取长度 |

### 栈（`stack/`）

| 类 | 文件 | 已实现功能 |
| --- | --- | --- |
| `MyStack<T>` | `ArrayStack.h` | 模板实现、动态扩容、`Push`、`Pop`、`Top`、判空、判满、清空、获取大小、获取容量、拷贝构造 / 赋值、移动构造 / 赋值 |
| `LinkStack<T>` | `LinkStack.h` | 模板实现、左值入栈、右值入栈、`pop`、`top`、判空、获取大小、移动构造 / 赋值、空栈异常 |
| `MyStack` | `QueueAsAStackImplementation.h` | 基于 `std::queue` 实现栈（`push` / `pop` / `top` / `empty`），暂未接入构建 |

## 测试入口

| 测试 | 覆盖内容 |
| --- | --- |
| `list/test_singlelist.cpp` | 单链表的头插 / 尾插 / 按位置插入、按值 / 按位置删除、反转、清空与边界情况 |
| `list/test_circle_singlelist.cpp` | 循环结构闭环校验、插入删除顺序、反转、空链表异常 |
| `list/test_doublelist.cpp` | 功能用例 + 与 `std::vector` 的随机对拍压力测试；Windows 下会自派生子进程验证删除尾节点 |
| `stack/test_arraystack.cpp` | 顺序栈的自动扩容 |
| `stack/test_linkstack.cpp` | 链式栈基本操作、字符串栈、移动语义、异常处理 |

## 已知问题（待修复）

**运行时风险**

- `SingleList` 有析构函数但未禁用 / 实现拷贝，默认浅拷贝会导致重复释放。
- `CircularSingleList::clear()` 依赖 `removeAtHead()` 逐个删除，每次都要遍历到尾，整体复杂度为 O(n²)。
- `ArrayStack` 被移动后 `maxSize` 变为 0，再调用 `Push` 会越界写入。
- `stack/QueueAsAStackImplementation.h` 的 `pop()` 声明为 `const` 却修改队列，一旦被使用就会编译失败；该文件还缺少 include guard。

**其他**

- 各头文件都在全局命名空间定义了 `struct Node`，同时包含两个以上会报重定义错误。
- `QueueAsAStackImplementation.h` 没有测试入口，未参与构建。
- `SingleList::removeAtPosition()` 越界提示文案写成了 `index out if list range`（`if` 应为 `of`）。

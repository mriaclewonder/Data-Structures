# Data-Structures

## 项目简介

这是一个使用 C++ 实现常见数据结构的练习项目，当前已经包含链表和栈的多种实现。每个模块都带有独立的 `main.cpp`，既可以作为示例程序，也可以作为简单的功能验证入口。

## 环境搭建

### 开发环境

- `CMake 3.25` 及以上
- 支持 `C++11` 的编译器，例如 `MSVC`、`GCC`、`Clang`
- 推荐使用 `CLion`、`VS Code + CMake Tools` 或 `Visual Studio`

### 根目录快速构建

当前顶层 `CMakeLists.txt` 默认启用了 `list` 模块，而 `list/CMakeLists.txt` 当前默认启用了 `CircularSingleList`。

```bash
cmake -S . -B build
cmake --build build --config Debug
```

编译完成后，可执行文件会输出到 `bin/` 或构建目录对应的配置子目录中。

### 单独构建某个模块

仓库中的每个具体模块都带有独立的 `CMakeLists.txt`，可以按模块分别构建：

```bash
cmake -S list/SingleList -B build/SingleList
cmake --build build/SingleList --config Debug

cmake -S list/DoubleList -B build/DoubleList
cmake --build build/DoubleList --config Debug

cmake -S list/CircularSingleList -B build/CircularSingleList
cmake --build build/CircularSingleList --config Debug

cmake -S stack/ArrayStack -B build/ArrayStack
cmake --build build/ArrayStack --config Debug

cmake -S stack/LinkStack -B build/LinkStack
cmake --build build/LinkStack --config Debug
```

### 一次性启用更多模块

如果你希望在根目录统一构建更多实现，可以取消下面文件中的注释：

- 顶层 `CMakeLists.txt` 中的 `add_subdirectory(stack)`
- `list/CMakeLists.txt` 中的 `add_subdirectory(SingleList)`
- `list/CMakeLists.txt` 中的 `add_subdirectory(DoubleList)`

## 已实现的数据结构与功能

### 链表

| 模块 | 说明 | 已实现功能 |
| --- | --- | --- |
| `SingleList` | 单链表 | 头插、尾插、按位置插入、按值删除、按位置删除、反转、清空、判空、获取长度、打印 |
| `DoubleList` | 双向链表 | `push_front`、`push_back`、按位置插入、按位置删除、头删、尾删、`front/back` 访问、下标访问、清空、判空、获取长度 |
| `CircularSingleList` | 单向循环链表 | 头插、尾插、按位置插入、删除头结点、删除尾结点、按值删除首个匹配、按位置删除、反转、清空、判空、获取长度 |

### 栈

| 模块 | 说明 | 已实现功能 |
| --- | --- | --- |
| `ArrayStack` | 数组栈 | 模板实现、动态扩容、`Push`、`Pop`、`Top`、判空、判满、清空、获取大小、获取容量、拷贝构造、移动构造、拷贝赋值、移动赋值 |
| `LinkStack` | 链式栈 | 模板实现、左值入栈、右值入栈、`pop`、`top`、判空、获取大小、移动构造、移动赋值、异常处理 |

## 示例入口

- `list/SingleList/main.cpp`：演示单链表的插入、删除、反转和边界情况
- `list/DoubleList/main.cpp`：包含较完整的功能测试与随机压力测试
- `list/CircularSingleList/main.cpp`：验证循环结构闭环、插入删除与反转
- `stack/ArrayStack/main.cpp`：演示顺序栈自动扩容
- `stack/LinkStack/main.cpp`：演示链式栈基础操作、字符串栈、移动语义与异常处理

## 目录结构

```text
.
├── list
│   ├── SingleList
│   ├── DoubleList
│   └── CircularSingleList
├── stack
│   ├── ArrayStack
│   └── LinkStack
├── build
└── bin
```

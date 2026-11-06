# list 模块：每个 test_*.cpp 是一个独立的测试可执行文件
# 头文件（SingleList.h / DoubleList.hpp / CircularSingleList.hpp）与测试源码同目录，
# 由顶层 CMakeLists.txt 里的 ds_add_test() 自动加入头文件搜索路径。

ds_add_test(test_singlelist)         # 单链表
ds_add_test(test_circle_singlelist)  # 单向循环链表
ds_add_test(test_doublelist)         # 双向链表（含压力测试）

# stack 模块：每个 test_*.cpp 是一个独立的测试可执行文件
# 头文件（ArrayStack.h / LinkStack.h）与测试源码同目录，
# 由顶层 CMakeLists.txt 里的 ds_add_test() 自动加入头文件搜索路径。
# 注意：QueueAsAStackImplementation.h 目前没有对应的测试入口，因此不生成 target。

ds_add_test(test_arraystack)  # 数组栈
ds_add_test(test_linkstack)   # 链式栈

cmake_minimum_required(VERSION 3.25)

project(DataStruct LANGUAGES CXX)

# ---- 全局编译设置（对当前目录及所有子目录生效）----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 生成 compile_commands.json，供 clangd / VS Code 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 可执行文件统一输出到构建目录下的 bin/，不往源码树里写东西
# （多配置生成器会再套一层 Debug/Release）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

enable_testing()

# ds_add_test(<测试名>)
# 约定：调用它的目录下有 <测试名>.cpp，被测头文件也放在同一目录。
# 生成 <测试名> 可执行文件，同时注册到 CTest。
function(ds_add_test name)
    add_executable(${name} ${name}.cpp)
    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_subdirectory(list)
add_subdirectory(stack)

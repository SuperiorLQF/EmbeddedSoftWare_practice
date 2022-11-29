#指定最低版本
cmake_minimum_required(VERSION 3.0)
#指定工程名
project("lab3test1")
#指定编译选项(即gcc后面的选项)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -std=c99")

set(CMAKE_C_COMPILE "/usr/bin/gcc")
#set(CMAKE_CXX_COMPILE "g++")
#可以指定一下编译器,不然会使用默认的编译器
add_subdirectory(src)


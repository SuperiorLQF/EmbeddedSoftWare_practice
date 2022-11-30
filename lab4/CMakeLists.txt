cmake_minimum_required(VERSION 3.0)

project("rw_strategy")

add_executable(readfirst.o readfirst.c)

target_link_libraries(readfirst.o
                    pthread
)




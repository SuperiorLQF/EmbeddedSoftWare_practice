cmake_minimum_required(VERSION 3.0)

project("rw_strategy")

add_executable(readfirst.o readfirst.c)
add_executable(writefirst.o writefirst.c)
add_executable(rw_balance.o rw_balance.c)

target_link_libraries(readfirst.o
                    pthread
)

target_link_libraries(writefirst.o
                    pthread
)

target_link_libraries(rw_balance.o
                    pthread
)
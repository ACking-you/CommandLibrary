cmake_minimum_required(VERSION 3.22)
project(Library)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib models service view util)

file(GLOB SRC "models/*.cpp" "service/*.cpp" view/*.cpp util/*.cpp)

#排除部分含有入口函数的文件
file(GLOB R_SRC "models/TestBook.cpp" "models/TestUser.cpp")

LIST(REMOVE_ITEM SRC ${R_SRC})

message(${SRC})

add_executable(Library main.cpp ${SRC})

#model层的测试book
add_executable(test_book models/TestBook.cpp models/Book.cpp)
#model层测试user
add_executable(test_user models/TestUser.cpp models/User.cpp)
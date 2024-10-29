cmake_minimum_required(VERSION 3.10)
project(SimpleDBMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dbms 
    src/main.cpp
    src/dbms.cpp
    src/storage.cpp
    src/querry.cpp
)

target_include_directories(dbms PRIVATE src)

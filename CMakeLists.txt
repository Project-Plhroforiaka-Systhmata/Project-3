cmake_minimum_required(VERSION 3.17)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")


add_executable(Project-3 main.cpp JobScheduler.cpp Job.cpp Queue.cpp vertex.cpp list.cpp bucket.cpp hashTable.cpp negativeList.cpp vector.cpp BF.h BF.cpp functions.h functions.cpp)
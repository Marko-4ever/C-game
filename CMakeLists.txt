cmake_minimum_required(VERSION 4.2)
project(animacija CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(animacija animacija.cpp)

target_link_libraries(animacija bgi gdi32 comdlg32 uuid oleaut32 ole32)
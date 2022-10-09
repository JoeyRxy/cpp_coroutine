cmake_minimum_required(VERSION 3.21)
project(coro)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
        main.cpp
        io_utils.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

cmake_minimum_required(VERSION 3.7)

project(sdg)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

# Enables Warning
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(SOURCES 
    sdg.cpp)

# Including directory files
if(UNIX)
    include_directories(include/sdg)
    list(APPEND SOURCES 
        "source/linux/target.cpp"
        "source/linux/debugger.cpp")
else()
    # include_directories(windows)
endif()

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

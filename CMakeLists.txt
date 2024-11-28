cmake_minimum_required(VERSION 3.6)

if (${CMAKE_SOURCE_DIR} STREQUAL "${PROJECT_SOURCE_DIR/src}")
    message (FATAL_ERROR "CMake generation is not allowed within the source directory!")
endif()

project(lab2
    VERSION 1.0
    LANGUAGES CXX
)

set(default_build_type "Release")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(source_dir Lab2)

set(
    source_files
    ${source_dir}/CSAI_lab2.cpp
)

set(build_dir "..")
set(EXECUTABLE_OUTPUT_PATH ${build_dir})

set(
    support_files
    LICENSE
)

#file(COPY ${support_files} DESTINATION "${build_dir}")

add_executable(${PROJECT_NAME} ${source_files} ${support_files})

# include_directories(D:/programing/cpp/FTXUI/include)
include_directories(/home/lord/programing/FTXUI)
set(
    FTXUI_LIBRARIES
    #==============
    #Windows example
    #==============
    # D:/programing/cpp/FTXUI/build/libftxui-component.a
    # D:/programing/cpp/FTXUI/build/libftxui-screen.a
    # D:/programing/cpp/FTXUI/build/libftxui-dom.a
    #==============
    #Linux example
    #==============
    /usr/local/lib/libftxui-component.a
    /usr/local/lib/libftxui-screen.a
    /usr/local/lib/libftxui-dom.a
)

target_link_libraries(${PROJECT_NAME} ${FTXUI_LIBRARIES})
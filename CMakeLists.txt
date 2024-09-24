cmake_minimum_required(VERSION 3.5)

project(comsolBmpPrint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(comsolBmpPrint
    main.cpp
    bmpreader.h
    bmpreader.cpp)

# Подключаем библиотеку GDI32 для работы с windows.h
if(WIN32)
    target_link_libraries(comsolBmpPrint gdi32)
endif()

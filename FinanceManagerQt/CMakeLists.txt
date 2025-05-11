cmake_minimum_required(VERSION 3.16)

project(FinanceTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

set(SOURCES main.cpp mainwindow.cpp)

set(HEADERS mainwindow.h)

set(FORMS mainwindow.ui)

add_executable(FinanceTracker ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(FinanceTracker PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts)

target_include_directories(FinanceTracker PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS FinanceTracker RUNTIME DESTINATION bin)

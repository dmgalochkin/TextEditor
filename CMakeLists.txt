cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME TextEditor)
project(${PROJECT_NAME})

set(application TextEditorApplication)
set(library TextEditorLibrary)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Config" FORCE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TextEditorLibrary)

add_subdirectory(TextEditorApplication)
add_subdirectory(TextEditorLibrary)
add_subdirectory(gtest)
add_subdirectory(test)


cmake_minimum_required(VERSION 3.5)

project(utmatrix CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/gtest")

# Google Test (идёт в составе проекта-шаблона)
add_library(gtest "${CMAKE_SOURCE_DIR}/gtest/gtest-all.cc")

# Модульные тесты
add_executable(test_utmatrix
  "${CMAKE_SOURCE_DIR}/test/test_main.cpp"
  "${CMAKE_SOURCE_DIR}/test/test_tvector.cpp"
  "${CMAKE_SOURCE_DIR}/test/test_tmatrix.cpp"
)
target_link_libraries(test_utmatrix gtest)

if (UNIX)
  target_link_libraries(test_utmatrix pthread)
endif()

enable_testing()
add_test(NAME utmatrix_tests COMMAND test_utmatrix)

# Тестовое приложение (пример использования)
add_executable(sample_utmatrix
  "${CMAKE_SOURCE_DIR}/samples/sample_matrix.cpp"
)

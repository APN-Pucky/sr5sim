cmake_minimum_required (VERSION 2.8)
project(sr5)
enable_language(CXX)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
  
add_test(
  NAME sr5test
  COMMAND sr5test -o report.xml -r junit)
# https://stackoverflow.com/questions/14446495/cmake-project-structure-with-unit-tests
# https://schneide.blog/2017/12/11/integrating-catch2-with-cmake-and-jenkins/
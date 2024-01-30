cmake_minimum_required(VERSION 3.10)
project(hello)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(hello main.cpp)
add_library(hello_lib lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(test_version PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(hello PRIVATE hello_lib)

target_link_libraries(test_version
	${Boost_LIBRARIES}
	hello_lib
)

target_compile_options(hello PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)

enable_testing()
add_test(test_version test_version)

cmake_minimum_required(VERSION 3.2)

project(finger C CXX)

set(CXX_FLAGS
 -g
 # -DVALGRIND
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 -std=c++11
 -rdynamic
 )

include_directories(/home/lyh/muduo-build/release-install-cpp11/include)
link_directories(/home/lyh/muduo-build/release-install-cpp11/lib)

add_executable(twisted_finger01 finger01.cc)
target_link_libraries(twisted_finger01 muduo_net muduo_base)

add_executable(twisted_finger02 finger02.cc)
target_link_libraries(twisted_finger02 muduo_net muduo_base)

add_executable(twisted_finger03 finger03.cc)
target_link_libraries(twisted_finger03 muduo_net muduo_base)

add_executable(twisted_finger04 finger04.cc)
target_link_libraries(twisted_finger04 muduo_net muduo_base)

add_executable(twisted_finger05 finger05.cc)
target_link_libraries(twisted_finger05 muduo_net muduo_base)

add_executable(twisted_finger06 finger06.cc)
target_link_libraries(twisted_finger06 muduo_net muduo_base)

add_executable(twisted_finger07 finger07.cc)
target_link_libraries(twisted_finger07 muduo_net muduo_base)
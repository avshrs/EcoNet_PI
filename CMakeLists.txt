cmake_minimum_required(VERSION 2.8.9)
project(EcoNet)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(CMAKE_CXX_STANDARD 17)
# target_compile_features(myexecutable PUBLIC cxx_std_17)

include_directories(include)

set(libs 
/usr/lib/arm-linux-gnueabihf/libmosquittopp.so
/usr/lib/arm-linux-gnueabihf/libpthread.so
/usr/lib/arm-linux-gnueabihf/libyaml-cpp.so
)

set(INCLUDE_HEADER_FILES "include/*.h" )
file(GLOB mSOURCES  "src/*.cpp" )


add_executable(EcoNet "src/main.cpp" ${mSOURCES})
target_link_libraries(EcoNet  ${libs})


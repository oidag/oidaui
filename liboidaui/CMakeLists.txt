
file(GLOB src *.cpp)
include_directories(../include)
add_library(oidaui SHARED ${src})

file(GLOB src *.cpp
		*.c
		elements/*.cpp
		font/*.cpp)
include_directories(../include)
add_library(oidaui SHARED ${src})
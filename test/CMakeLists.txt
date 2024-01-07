file(GLOB lib_src
#		../liboidaui/*.cpp
#		../liboidaui/elements/*.cpp
		../liboidaui/errors.c
		../liboidaui/font/*.cpp)

include_directories(../include)

find_package(Freetype REQUIRED)

add_executable(test_glfw test_glfw.cpp ${lib_src})
target_link_libraries(test_glfw glfw GL ${FREETYPE_LIBRARIES})

target_include_directories(test_glfw PRIVATE ${FREETYPE_INCLUDE_DIRS})
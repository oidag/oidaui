include_directories(../include)

find_package(Freetype REQUIRED)

add_executable(test_label test_label.cpp
		../liboidaui/node.cpp
		../liboidaui/canvas.cpp
		../liboidaui/font/font.cpp
		../liboidaui/errors.c ${lib_src})
target_link_libraries(test_label glfw GL ${FREETYPE_LIBRARIES})

target_include_directories(test_label PRIVATE ${FREETYPE_INCLUDE_DIRS})
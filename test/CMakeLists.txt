file(GLOB lib_src ../liboidaui/*.cpp)

add_executable(test_glfw test_glfw.c ${lib_src})
target_link_libraries(test_glfw glfw GL)
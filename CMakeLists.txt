cmake_minimum_required(VERSION 3.23)
project(renderer)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

# The following moves the shader files to the build directory
# On release put the shader source code into a const char* instead of loading another file. This just makes it easier for testing.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rendering/shaders/vertex.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rendering/shaders/fragment.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders)

add_executable(${PROJECT_NAME}
        main.cpp
        glad/glad.c
        imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_impl_glfw.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp
        window/window.cpp window/window.h
        rendering/shaders/shaders.cpp
        camera/camera.cpp camera/camera.h
        input/keyboard.cpp input/keyboard.h
        input/mouse.cpp input/mouse.h
        rendering/textures/textures.cpp rendering/textures/textures.h rendering/textures/granite.c rendering/textures/brick.c
        debug/debug.cpp debug/debug.h
        rendering/vao/vao.cpp rendering/vao/vao.h
        rendering/vbo/vbo.cpp rendering/vbo/vbo.h
        loader/loader.cpp loader/loader.h)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

add_compile_options(-fpermissive)

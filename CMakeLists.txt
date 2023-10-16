cmake_minimum_required(VERSION 3.23)
project(renderer)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

# The following moves the shader files to the build directory
# On release put the shader source code into a const char* instead of loading another file. This just makes it easier for testing.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders)

add_executable(${PROJECT_NAME}
        main.cpp
        glad/glad.c
        window/window.cpp window/window.h
        shaders/shaders.cpp
        camera/camera.cpp camera/camera.h
        input/keyboard.cpp input/keyboard.h
        input/mouse.cpp input/mouse.h)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

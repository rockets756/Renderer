#include "shaders.h"

#include <glad.h>
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename) {
    // Open the file for reading
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        // MessageBox(NULL, "Error opening shader file!", "Renderer", MB_OK | MB_ICONERROR);
        return NULL;
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET); // Rewind the file pointer

    // Allocate memory to store the file contents (add 1 for null-terminator)
    char* file_contents = (char*)malloc(file_size + 1);

    if (file_contents == NULL) {
        // MessageBox(NULL, "Error allocating memory for shader code!", "Renderer", MB_OK | MB_ICONERROR);
        fclose(file);
        return NULL;
    }

    // Read the entire file into the file_contents buffer
    size_t bytes_read = fread(file_contents, 1, file_size, file);
    file_contents[bytes_read] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    return file_contents;
}


/*
 * This function does the following:
 * - Loads the vertex and fragment shaders from their files
 * - Compiles both of the shaders
 * - Creates the shader program
 * - Links the shaders to the shader program and tells opengl to use the shader program
 * - Removes the shaders after linking them to the shader program
 */
unsigned int compile_shaders() {
    const char* vertexShaderSource = read_file("resources/shaders/vertex.glsl");
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // MessageBox(NULL, "Vertex shader compilation failed!", "Renderer", MB_OK | MB_ICONERROR);
        printf("%s\n", infoLog);
        return 0;
    }
    free((void *) vertexShaderSource);
    // fragment shader
    const char* fragmentShaderSource = read_file("resources/shaders/fragment.glsl");
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        // MessageBox(NULL, "Fragment shader compilation failed!", "Renderer", MB_OK | MB_ICONERROR);
        printf("%s\n", infoLog);
        return 0;
    }
    free((void *) fragmentShaderSource);
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        // MessageBox(NULL, "Error linking the shader program!", "Renderer", MB_OK | MB_ICONERROR);
        printf("%s\n", infoLog);
        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

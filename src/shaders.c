#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

static char *__read_shader_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to load shader file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = (char*)malloc(length + 1);
    if (buffer)
        fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);

    return buffer;
}

static GLuint __compile_shader(const char *shaderSource, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Shader Compilation Failed: %s\n", infoLog);
    }

    return shader;
}

GLuint create_shader_program(void)
{
    char *vertex_shader_code = __read_shader_file("../src/shaders/vertex_shader.glsl");
    char *fragment_shader_code = __read_shader_file("../src/shaders/fragment_shader.glsl");
    GLuint vertexShader = __compile_shader(vertex_shader_code, GL_VERTEX_SHADER);
    GLuint fragmentShader = __compile_shader(fragment_shader_code, GL_FRAGMENT_SHADER);
    free(vertex_shader_code);
    free(fragment_shader_code);

    // Link the shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Shader Program Linking Failed: %s\n", infoLog);
    }

    // Delete the shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

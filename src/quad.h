#ifndef QUAD_H
#define QUAD_H

#include <GL/glew.h>

// Quad struct to manage position, size, and color
typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat width;
    GLfloat height;
    GLfloat color[3];
    GLuint VAO;
} Quad;

// Function to initialize the quad's vertex data and VAO
void init_quad(Quad *quad);

// Function to draw a quad
void draw_quad(GLuint shader_program, Quad *quad);

#endif

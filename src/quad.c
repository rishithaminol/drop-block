#include "quad.h"
#include <GL/glew.h>

// Quad vertex data (two triangles forming a quad)
GLfloat quad_vertices[] = {
    // Positions
    -0.5f,  0.5f, 0.0f,  // Top-left
     0.5f, -0.5f, 0.0f,  // Bottom-right
    -0.5f, -0.5f, 0.0f,  // Bottom-left

    -0.5f,  0.5f, 0.0f,  // Top-left
     0.5f,  0.5f, 0.0f,  // Top-right
     0.5f, -0.5f, 0.0f   // Bottom-right
};

// Function to initialize the quad
void init_quad(Quad *quad)
{
    // Generate and bind the VAO and VBO for the quad
    GLuint VBO;
    glGenVertexArrays(1, &quad->VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(quad->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); /* unbind VBO */
    glBindVertexArray(0); /* unbind VAO */
}

// Function to draw a quad
void draw_quad(GLuint shader_program, Quad *quad)
{
    // Use the shader program
    glUseProgram(shader_program);

    // Set the quad's color uniform in the shader
    GLint color_location = glGetUniformLocation(shader_program, "quadColor");
    glUniform3fv(color_location, 1, quad->color);

    // Apply transformation (translate and scale)
    GLfloat transform[16] = {
        quad->width, 0.0f, 0.0f, 0.0f,
        0.0f, quad->height, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        quad->x, quad->y, 0.0f, 1.0f
    };

    GLint transform_location = glGetUniformLocation(shader_program, "transform");
    glUniformMatrix4fv(transform_location, 1, GL_FALSE, transform);

    // Bind the VAO and draw the quad (two triangles)
    glBindVertexArray(quad->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 6 vertices (2 triangles)
    glBindVertexArray(0);
}

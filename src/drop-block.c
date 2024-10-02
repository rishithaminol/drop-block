#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "utils.h"
#include "quad.h"

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_GLContext gl_context;
    initialize_SDL_GL_window(&window, &gl_context);

    // Create and initialize the shader program
    GLuint shader_program = create_shader_program();

    // Initialize two quads with different colors
    Quad red_quad = { -0.5f, 0.0f, 0.5f, 0.5f, {1.0f, 0.0f, 0.0f}, 0 };
    Quad blue_quad = { 0.5f, 0.0f, 0.5f, 0.5f, {0.0f, 0.0f, 1.0f}, 0 };

    init_quad(&red_quad);
    init_quad(&blue_quad);

    glClearColor(0.1333f, 0.1490f, 0.1647f, 0.0f);

    // Main loop placeholder
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the quads
        draw_quad(shader_program, &red_quad);
        draw_quad(shader_program, &blue_quad);

        // Swap the window buffers (rendering here)
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &red_quad.VAO);
    glDeleteVertexArrays(1, &blue_quad.VAO);
    glDeleteProgram(shader_program);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

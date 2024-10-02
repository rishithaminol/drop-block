#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void initialize_SDL_GL_window(SDL_Window **window, SDL_GLContext *gl_context)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    // Set SDL to use OpenGL version 3.3 core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create SDL window
    *window = SDL_CreateWindow("OpenGL with SDL2", 
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               800, 600, 
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!(*window)) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    // Create OpenGL context
    *gl_context = SDL_GL_CreateContext(*window);
    if (!(*gl_context)) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(-1);
    }

    // Initialize GLEW (required for OpenGL functions beyond 1.1)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        SDL_GL_DeleteContext(*gl_context);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(-1);
    }
}

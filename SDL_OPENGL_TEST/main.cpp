//
//  main.cpp
//  SDL_OPENGL_TEST
//
//  Created by Josh on 1/26/15.
//  Copyright (c) 2015 Josh. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <OpenGL/gl3.h>

using namespace std;

int EventFilter(void* userdata, SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            SDL_Log("key down %d", event->key.keysym.sym);
            return 0;
        case SDL_KEYUP:
            SDL_Log("key up %d", event->key.keysym.sym);
            return 0;
        case SDL_MOUSEMOTION:
            SDL_Log("mouse moved X = %d, Y = %d, RelativeX = %d, RelativeY = %d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            SDL_Log("mouse button down %d", event->button.button);
            return 0;
        case SDL_MOUSEBUTTONUP:
            SDL_Log("mouse button up %d", event->button.button);
            return 0;
        case SDL_MOUSEWHEEL:
            SDL_Log("mouse wheel");
            return 0;
    }
    return 1;
}

int main(int argc, const char * argv[])
{
    int width = 800;
    int height = 600;
    
    if(0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << "Could not initialize SDL: " <<  SDL_GetError() << endl;
        return 0;
    }
    
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    auto window = SDL_CreateWindow("SDL OpenGL test", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    if(window == 0)
    {
        SDL_Quit();
        return 0;
    }
    
    auto glContext = SDL_GL_CreateContext(window);
    
    SDL_AddEventWatch(EventFilter, nullptr);
    
    SDL_Event event;
    
    bool done = false;
    
    while (!done)
    {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_APP_LOWMEMORY:
                    SDL_Log("Low memory");
                    break;
            }
        }
    }
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

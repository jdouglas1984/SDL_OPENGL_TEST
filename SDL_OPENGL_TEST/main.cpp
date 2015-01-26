//
//  main.cpp
//  SDL_OPENGL_TEST
//
//  Created by Josh on 1/26/15.
//  Copyright (c) 2015 Josh. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

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
                    cout << "Low Memory" << endl;
                    break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

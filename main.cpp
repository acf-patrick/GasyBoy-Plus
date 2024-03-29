#include "defs.h"

int main(int argc, char **argv)
{
    //Setting up SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return 1;
    }

    //Setting up OpenGL and
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    //Instance of gameboy
    Gameboy gb;
    Machine machine;

    //main loop
    Uint32 acTime = 0, prevTime = 0, delta = 0, timeToRender = 0;
    bool done = false;
    while (!done)
    {
        acTime = SDL_GetTicks();
        delta = acTime - prevTime;
        prevTime = acTime;
        //events handling
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            gb.get_debugger()->HandleEvent(event); //uisng gb debugger to handle event here
            if (event.type == SDL_QUIT)
                done = true;
        }
        timeToRender+= delta;
        gb.get_debugger()->step();
        if (timeToRender >= 100)
        {
            gb.get_debugger()->Render();               //rendering the debugger (no gameboy graphic yet!)
            machine.Render();
            timeToRender = 0;
        }

    }
    gb.get_debugger()->~Debugger();                 //destroying gameboy instance
    SDL_Quit();

    return 0;
}

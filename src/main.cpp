#include <SDL.h>
#include <iostream>
#include "KeyBoardLock.h"
extern bool isKeyboardLocked;
extern void ToggleLock();

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // create a sdl window
    SDL_Window *window = SDL_CreateWindow("Keyboard Lock Toggle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    // create an sdl renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect buttonRect = {150, 100, 100, 50};
    SDL_Color buttonColor = {0, 130, 255, 255};

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.x >= buttonRect.x && event.button.x <= buttonRect.x + buttonRect.w &&
                    event.button.y >= buttonRect.y && event.button.y <= buttonRect.y + buttonRect.h)
                {
                    ToggleLock();
                    const char* status = isKeyboardLocked ? "Keyboard Locked!" : "Keyboard Unlocked!";
                    MessageBoxA(NULL, status, "Keyboard Toggle", MB_OK);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_RenderFillRect(renderer, &buttonRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

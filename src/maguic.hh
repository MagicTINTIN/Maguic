#pragma once

#include <string>

#include <SDL.h>

namespace Maguic
{
    class Window
    {
    private:
        std::string name_;
        SDL_Window *window_;
        int width_, height_;
    public:
        Window(std::string name);
        Window(std::string name, int width, int height);
        ~Window();
    };
    
} // namespace Maguic

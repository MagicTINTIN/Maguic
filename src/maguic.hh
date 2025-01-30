#pragma once
#ifndef MAGUIC_HH
#define MAGUIC_HH

#include <string>

#include <SDL2/SDL.h>

namespace Maguic
{
    class Window
    {
    private:
        std::string _name;
        SDL_Window *_window;
        int _width, _height;
    public:
        Window(std::string name, int width, int height);
        Window(std::string name);
        ~Window();
        void setVisible(bool visible);
    };
    
} // namespace Maguic

#endif
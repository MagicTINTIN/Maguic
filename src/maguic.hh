#pragma once
#ifndef MAGUIC_HH
#define MAGUIC_HH

#include <string>
#include <thread>

#include <SDL2/SDL.h>

namespace Maguic
{
    class Window
    {
    private:
        std::string _name;
        SDL_Window *_window;
        int _width, _height;
        std::thread _mainThread;
        bool _running;

        void mainWindowLoop();
    public:
        Window(std::string name, int width, int height);
        Window(std::string name);
        ~Window();
        void setVisible(bool visible);
    };
    
} // namespace Maguic

#endif
#include "maguic.hh"
#include <string>
#include <iostream>

#include <SDL2/SDL.h>

namespace Maguic
{
    Window::Window(std::string name, int width, int height) : _width(width), _height(height), _name(name)
    {
        _window = SDL_CreateWindow(_name.c_str(),
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   _width, _height,
                                   SDL_WINDOW_SHOWN);
        if (!_window)
        {
            std::cout << "Window could not be created!" << std::endl
                      << "SDL_Error: " << SDL_GetError() << std::endl;
        }

        // SDL_Quit();
    }
    Window::Window(std::string name) : Window(name, 400, 300)
    {
    }

    Window::~Window()
    {
    }

    void Window::setVisible(bool visible)
    {
    }
} // namespace Maguic

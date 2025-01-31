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
                                   SDL_WINDOW_HIDDEN);
        if (!_window)
        {
            std::cout << "Window could not be created!" << std::endl
                      << "SDL_Error: " << SDL_GetError() << std::endl;
        }

        _mainThread = std::thread([this](){this->mainWindowLoop();});
        // SDL_Quit();
    }
    Window::Window(std::string name) : Window(name, 400, 300)
    {
    }

    Window::~Window()
    {
        _running = false;
        _mainThread.join();
    }

    void Window::setVisible(bool visible)
    {
        if (visible)
            SDL_ShowWindow(_window);
        else
            SDL_HideWindow(_window);
    }

    void Window::mainWindowLoop()
    {
        _running = true;
        while (_running)
        {
        }
    }
} // namespace Maguic

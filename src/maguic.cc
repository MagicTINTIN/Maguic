#include "maguic.hh"
#include <string>
#include <thread>
#include <iostream>
#include <functional>

#include <SDL3/SDL.h>

namespace Maguic
{
    Window::Window(std::string const name, int width, int height) : _name(name), _width(width), _height(height)
    {
        _window = SDL_CreateWindow(_name.c_str(),
                                   _width, _height,
                                   SDL_WINDOW_HIDDEN);
        if (!_window)
        {
            std::cout << "Window could not be created!" << std::endl
                      << "SDL_Error: " << SDL_GetError() << std::endl;
        }

        _mainThread = std::thread(std::bind(&Window::mainWindowLoop, this));
        // setQuitSequence(std::bind(&Window::close, this));
        setQuitSequence([this]()
                        { this->close(); });
    }
    Window::Window(std::string name) : Window(name, 400, 300)
    {
    }

    Window::~Window()
    {
        close();
        SDL_Quit();
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
        SDL_Event e;
        while (_running && SDL_WaitEvent( &e ))
        {
            handleEvents(e);
        }
    }

    void Window::handleEvents(SDL_Event &e)
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            // TODO: link the event to the correct window w/ e.window
            quitSequence();
        }
    }

    void Window::close()
    {
        if (_running)
        {
            _running = false;
            // SDL_PushEvent()
            _mainThread.join();
            SDL_DestroyWindow(_window);
        }
        // TODO: maybe sdl quit only when there is no more windows
        // SDL_Quit();
    }

    void Window::setQuitSequence(std::function<void()> callback)
    {
        quitSequence = std::move(callback);
    }

} // namespace Maguic

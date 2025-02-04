#include "maguic.hh"
#include <string>
#include <thread>
#include <iostream>
#include <functional>

#include <SDL3/SDL.h>
// #include <SDL2/SDL_ttf.h> no need

namespace Maguic
{
    Window::Window(std::string const name, int width, int height) : _name(name), _width(width), _height(height)
    {
        // TODO: init all the necessary events
        SDL_Init(SDL_INIT_EVENTS);
        
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
                        { this->close(); return true; });
    }
    Window::Window(std::string name) : Window(name, 400, 300)
    {
    }

    Window::~Window()
    {
        printf("~Window\n");
        this->close();
        printf("Joining\n");
        _mainThread.join();
        printf("Joined\n");
        SDL_Quit();
        printf("SDLquited\n");
    }

    void Window::setVisible(bool visible)
    {
        if(!_running) return;
        if (visible)
            SDL_ShowWindow(_window);
        else
            SDL_HideWindow(_window);
    }

    void Window::mainWindowLoop()
    {
        _running = true;
        SDL_Event e;
        while (_running)
        {
            printf("Waiting for event...\n");
            SDL_WaitEvent(&e);
            if (handleEvents(e) == CLOSING) {
                this->close();
            }
            printf("Post-Event, type=");
            std::cout << "0x" << std::hex << e.type << std::endl;
        }
    }

    MaguicStatus Window::handleEvents(SDL_Event &e)
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            printf("Quit event received\n");
            // TODO: link the event to the correct window w/ e.window
            if (quitSequence())
                return CLOSING;
            else 
                return RUNNING;
        }
        return RUNNING;
    }

    void Window::close()
    {
        printf("C\n");
        if (!_closingCounter++)
        {
            printf("X\n");
            _running = false; //BEFORE DESTORYING WINDOW

            // SDL_Event* event = new SDL_Event(SDL_QuitEvent());
            //event->type = SDL_EVENT_USER;
            // SDL_PushEvent(static_cast<SDL_Event*>(event));

            // SDL_PushEvent(nullptr);
            // _mainThread.join(); // joining itself...
            SDL_DestroyWindow(_window);
        }
        // TODO: maybe sdl quit only when there is no more windows
        // SDL_Quit();
    }

    void Window::setQuitSequence(std::function<bool()> callback)
    {
        quitSequence = std::move(callback);
    }

} // namespace Maguic

#pragma once
#ifndef MAGUIC_HH
#define MAGUIC_HH

#include <string>
#include <thread>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>

#include <SDL3/SDL.h>

namespace Maguic
{
    enum MaguicStatus {RUNNING, CLOSING};

    class Window
    {
    private:
        std::string _name;
        SDL_Window *_window;
        int _width, _height;
        std::thread _mainThread;
        
        std::atomic<bool> _running;
        std::atomic<int> _closingCounter = 0;

        std::vector<void (*)()> actions;
        std::function<bool()> quitSequence;

        void mainWindowLoop();
        MaguicStatus handleEvents(SDL_Event &e);

    public:
        Window(std::string const name, int width, int height);
        Window(std::string name);
        ~Window();
        void setVisible(bool visible);
        void close();
        void setQuitSequence(std::function<bool()> callback);
    };

    // ##################### COMPONENTS ##################### //

    // Abstract component
    class Component
    {
    protected:
        int _width, _height;

    public:
        Component(int w, int h);
        virtual ~Component() = default;

        int getWidth() const;
        int getHeight() const;

        void setSize(int width, int height);

        virtual void render() const = 0;
    };

    class Button : public Component
    {
    private:
        std::string _name;
        std::function<void()> _action;

    public:
        Button(int width, int height, const std::string &name, std::function<void()> action);
        Button(const std::string &name);

        std::string getName() const;
        void setName(const std::string &name);
        void setAction(std::function<void()> action);

        void render() const;
    };

    class Panel : public Component
    {
    protected:
        std::vector<std::shared_ptr<Component>> _components;

    public:
        Panel();
        Panel(int width, int height);
        ~Panel();

        void removeAllComponents();
        void addComponent(std::shared_ptr<Component> component);

        void render() const;
    };

} // namespace Maguic

#endif
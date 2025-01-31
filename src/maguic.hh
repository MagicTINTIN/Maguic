#pragma once
#ifndef MAGUIC_HH
#define MAGUIC_HH

#include <string>
#include <thread>
#include <vector>
#include <memory>

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

    // ##################### COMPONENTS ##################### //

    // Abstract component
    class Component
    {
    protected:
        int _width, _height;

    public:
        Component(int w, int h) : _width(w), _height(h) {}

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

    public:
        Button(int width, int height, const std::string &name);
        Button(const std::string &name);

        std::string getName() const;
        void setName(const std::string &name);

        void render() const;
    };

    class Panel : public Component
    {
    protected:
        std::vector<std::shared_ptr<Component>> _components;

    public:
        Panel();
        Panel(int width, int height);

        void removeAllComponents();
        void addComponent(std::shared_ptr<Component> component);

        void render() const;
    };

} // namespace Maguic

#endif
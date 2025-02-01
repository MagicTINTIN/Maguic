#include "maguic.hh"
#include <string>
#include <thread>
#include <iostream>
#include <functional>

#include <SDL3/SDL.h>

namespace Maguic
{
    // Component
    Component::Component(int w, int h) : _width(w), _height(h) {}

    int Component::getWidth() const { return _width; }
    int Component::getHeight() const { return _height; }
    void Component::setSize(int w, int h) { _width = w;  _height = h; }

    // Button
    Button::Button(int width, int height, const std::string &name) : Component(width, height), _name(name) {}
    Button::Button(const std::string &name) : Button(-1,-1, name) {}

    std::string Button::getName() const { return _name; }
    void Button::setName(const std::string &name) { _name = name; }

    void Button::render() const
    {
        std::cout << "Button [" << _name << "] of size (" << _width << ", " << _height << ")\n";
    }

    // Panel
    Panel::Panel(int width, int height) : Component(width, height), _components() {}
    Panel::Panel() : Panel(-1, -1) {}
    Panel::~Panel()
    {
        for (std::shared_ptr<Maguic::Component> &comp : _components)
        {
            comp->~Component();
        }
    }
    void Panel::removeAllComponents()
    {
        _components.clear();
    }

    void Panel::addComponent(std::shared_ptr<Component> component)
    {
        _components.push_back(component);
    }

    void Panel::render() const {
    std::cout << "Panel of size (" << _width << ", " << _height << ") containing:\n";
    for (const std::shared_ptr<Maguic::Component> &comp : _components) {
        comp->render();
    }
}
} // namespace Maguic

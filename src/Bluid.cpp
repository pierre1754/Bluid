/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#include "Bluid.hpp"
#include "Button.hpp"

BluidEngine::BluidEngine(void) : _fluid(512, 2, 0.2, 0, 0.0000001)
{
    this->_window.create(sf::VideoMode(1920, 1080), "Bluid", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_lastPos = {0, 0};
    this->_actPos = {0, 0};
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f,   0}, "diffusion", {3, 4}, 3.2));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 100}, "viscosity", {0, 200}, 50.0));
    this->_buttonList.push_back(new Button({this->_window.getSize().x - 400.f, 200}, "timestep", {-1, 1}, 0.8));
    this->_buf.create(262144);
}

BluidEngine::~BluidEngine(void)
{
    for (Button *button : this->_buttonList)
        delete button;
}

void BluidEngine::eventHandler(void)
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (this->_event.type == sf::Event::KeyPressed)
            if (this->_event.key.code == sf::Keyboard::Escape)
                this->_window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        this->_lastPos = this->_actPos;
        this->_actPos = sf::Mouse::getPosition(this->_window);
        if (this->_lastPos.x != this->_actPos.x && this->_lastPos.y != this->_actPos.y)
            this->_fluid.mouseDragged(_actPos, _lastPos);
        for (Button *button : this->_buttonList)
            button->setValue(this->_actPos);
    }
    _fluid.step();
}

bool BluidEngine::isOpen()
{
    return this->_window.isOpen();
}

sf::RenderWindow &BluidEngine::getWindow(void)
{
    return this->_window;
}

sf::Vector2i BluidEngine::getActPos(void)
{
    return this->_actPos;
}

sf::Vector2i BluidEngine::getLastPos(void)
{
    return this->_lastPos;
}

void BluidEngine::draw(void)
{
    this->_window.clear(sf::Color::Black);
    for (Button *button : this->_buttonList)
        button->draw(this->_window);
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            _vertices[IX(i, j, 512)].position = {(float)i, (float)j};
            _vertices[IX(i, j, 512)].color = {0, 0, (sf::Uint8)(20 + _fluid.getDensity(i, j))};
        }
    }
    this->_buf.update(this->_vertices);
    this->_window.display();
}

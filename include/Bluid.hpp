/*
** EPITECH PROJECT, 2022
** BLUID
** File description:
** bluid
*/

#ifndef BLUID_HPP
#define BLUID_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <array>

#include "Button.hpp"
#include "FluidSquare.hpp"

class BluidEngine
{
private:
    sf::RenderWindow _window;
    sf::Event _event;
    sf::Vector2i _actPos;
    sf::Vector2i _lastPos;
    std::vector<Button *> _buttonList;
    std::vector<sf::Vertex> _vertices;
    sf::VertexBuffer _buf;
    FluidSquare _fluid;
    std::size_t _size;
    std::size_t _scale;
    sf::Texture _logoTexture;
    sf::Sprite _logoSprite;
public:
    BluidEngine(std::size_t size, std::size_t scale);
    ~BluidEngine();
    bool isOpen(void);
    void update(void);
    void eventHandler(void);
    void draw(void);
};

#endif // BLUID_HPP

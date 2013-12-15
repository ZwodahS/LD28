/*
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 * 
 * Copyright (C) 2013 ZwodahS(ericnjf@gmail.com) 
 * zwodahs.wordpress.com
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE **** YOU WANT TO.
 * 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. 
 */
#include "Collector.hpp"
#include "Board.hpp"
const sf::Vector2f Collector::NorthArrowOffset = sf::Vector2f(29, 16);
const sf::Vector2f Collector::SouthArrowOffset = sf::Vector2f(29, 41);
const sf::Vector2f Collector::EastArrowOffset = sf::Vector2f(42, 29);
const sf::Vector2f Collector::WestArrowOffset = sf::Vector2f(16, 29);
const sf::Vector2f Collector::PixelOffset = sf::Vector2f(27, 27);
const sf::Color Collector::ArrowColor = sf::Color(0, 255, 0);
Collector::Collector(Game& game, Board* board)
    : Chip(game, board)
{
    _westArrow = _game.assets.arrow_right.createSprite();
    _eastArrow = _game.assets.arrow_left.createSprite();
    _northArrow = _game.assets.arrow_down.createSprite();
    _southArrow = _game.assets.arrow_up.createSprite();
    _westArrow.setColor(ArrowColor);
    _eastArrow.setColor(ArrowColor);
    _northArrow.setColor(ArrowColor);
    _southArrow.setColor(ArrowColor);
    _pixel = _game.assets.shadedBox.createSprite();
}

Collector::~Collector()
{
}

void Collector::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->chipDrawState == Board::Draw_Icon)
    {
        window.draw(_westArrow);
        window.draw(_eastArrow);
        window.draw(_northArrow);
        window.draw(_southArrow);
        window.draw(_pixel);
    }
}

void Collector::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}
void Collector::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _westArrow.setPosition(_position + WestArrowOffset);
    _eastArrow.setPosition(_position + EastArrowOffset);
    _northArrow.setPosition(_position + NorthArrowOffset);
    _southArrow.setPosition(_position + SouthArrowOffset);
    _pixel.setPosition(_position + PixelOffset);
}

void Collector::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
    zf::setAlpha(_westArrow, alpha);
    zf::setAlpha(_eastArrow, alpha);
    zf::setAlpha(_northArrow, alpha);
    zf::setAlpha(_southArrow, alpha);
    zf::setAlpha(_pixel, alpha);
}


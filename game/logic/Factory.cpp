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
#include "Factory.hpp"
#include "Board.hpp"
const sf::Vector2f Factory::PowerOffset = sf::Vector2f(13, 29);
const sf::Vector2f Factory::ArrowOffset = sf::Vector2f(25, 29);
const sf::Vector2f Factory::OutputOffset = sf::Vector2f(40, 29);
Factory::Factory(Game& game, Board* board)
    : Chip(game, board)
{
    setPixelProduction(Pixel::Red);
    _powerIcon = _game.assets.power.createSprite();
    _arrowIcon = _game.assets.conversionArrow.createSprite();
    _outputIcon = _game.assets.shadedBox.createSprite();
}

Factory::~Factory()
{
}

void Factory::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->chipDrawState == Board::Draw_Icon)
    {
        window.draw(_powerIcon);
        window.draw(_arrowIcon);
        window.draw(_outputIcon);
    }
}

void Factory::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}

void Factory::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _powerIcon.setPosition(position + PowerOffset);
    _arrowIcon.setPosition(position + ArrowOffset);
    _outputIcon.setPosition(position + OutputOffset);
}

void Factory::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
    zf::setAlpha(_powerIcon, alpha);
    zf::setAlpha(_arrowIcon, alpha);
    zf::setAlpha(_outputIcon, alpha);
}

void Factory::setPixelProduction(Pixel::Type type)
{ 
    _factoryType = type;
    _outputIcon.setColor(Pixel::getColor(type));
}

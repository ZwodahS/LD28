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
#include "ArrowControl.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
const sf::Vector2f ArrowControl::NorthArrowOffset = sf::Vector2f(29, 1);
const sf::Vector2f ArrowControl::SouthArrowOffset = sf::Vector2f(29, 56);
const sf::Vector2f ArrowControl::EastArrowOffset = sf::Vector2f(57, 29);
const sf::Vector2f ArrowControl::WestArrowOffset = sf::Vector2f(1, 29);
const sf::Color ArrowControl::OutColor = sf::Color(128, 255 , 128);
const sf::Color ArrowControl::InColor = sf::Color(255, 255, 128);
ArrowControl::ArrowControl(Game& game)
    : _game(game), _north(None), _east(None), _south(None), _west(None)
{
}

void ArrowControl::setPosition(const sf::Vector2f& position)
{
    _position = position;
    _northSprite.setPosition(_position + NorthArrowOffset);
    _southSprite.setPosition(_position + SouthArrowOffset);
    _eastSprite.setPosition(_position + EastArrowOffset);
    _westSprite.setPosition(_position + WestArrowOffset);
}

ArrowControl& ArrowControl::setArrow(zf::Direction direction, ArrowType type)
{
    if(direction == zf::North)
    {
        _north = type;
        if(type == None)
        {
            _northSprite = sf::Sprite();
        }
        else if(type == Out)
        {
            _northSprite = _game.assets.arrow_up.createSprite();
            _northSprite.setColor(OutColor);
        }
        else
        {
            _northSprite = _game.assets.arrow_down.createSprite();
            _northSprite.setColor(InColor);
        }
        _northSprite.setPosition(_position + NorthArrowOffset);
    }
    else if(direction == zf::South)
    {
        _south = type;
        if(type == None)
        {
            _southSprite = sf::Sprite();
        }
        else if(type == Out)
        {
            _southSprite = _game.assets.arrow_down.createSprite();
            _southSprite.setColor(OutColor);
        }
        else 
        {
            _southSprite = _game.assets.arrow_up.createSprite();
            _southSprite.setColor(InColor);
        }
        _southSprite.setPosition(_position + SouthArrowOffset);
    }
    else if(direction == zf::East)
    {
        _east = type;
        if(type == None)
        {
            _eastSprite = sf::Sprite();
        }
        else if(type == Out)
        {
            _eastSprite = _game.assets.arrow_right.createSprite();
            _eastSprite.setColor(OutColor);
        }
        else if(type == In)
        {
            _eastSprite = _game.assets.arrow_left.createSprite();
            _eastSprite.setColor(InColor);
        }
        _eastSprite.setPosition(_position + EastArrowOffset);
    }
    else if(direction == zf::West)
    {
        _west = type;
        if(type == None)
        {
            _westSprite = sf::Sprite();
        }
        else if(type == Out)
        {
            _westSprite = _game.assets.arrow_left.createSprite();
            _westSprite.setColor(OutColor);
        }
        else if(type == In)
        {
            _westSprite = _game.assets.arrow_right.createSprite();
            _westSprite.setColor(InColor);
        }
        _westSprite.setPosition(_position + WestArrowOffset);
    }
    return *this;
}

void ArrowControl::rotate()
{
    ArrowType temp = _east; // store the east value.
    setArrow(zf::East, _north);
    setArrow(zf::North, _west);
    setArrow(zf::West, _south);
    setArrow(zf::South, temp);
}

void ArrowControl::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(_northSprite);
    window.draw(_eastSprite);
    window.draw(_southSprite);
    window.draw(_westSprite);
}

void ArrowControl::update(sf::RenderWindow& window, const sf::Time& delta)
{
}


void ArrowControl::setAlpha(float alpha)
{
    zf::setAlpha(_northSprite, alpha);
    zf::setAlpha(_eastSprite, alpha);
    zf::setAlpha(_southSprite, alpha);
    zf::setAlpha(_westSprite, alpha);
}

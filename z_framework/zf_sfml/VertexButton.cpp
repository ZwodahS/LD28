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

#include "VertexButton.hpp"
#include "f_common.hpp"
namespace zf
{
    VertexButton::VertexButton()
        : _border(sf::LinesStrip, 5), _background(sf::Quads, 4), _bound(0,0,0,0)
    {
    }

    VertexButton::~VertexButton()
    {
        _text.setString(" ");
    }

    VertexButton::VertexButton(sf::Color borderColor, sf::Color backgroundColor, sf::FloatRect bound, sf::Text text)
        : _border(sf::LinesStrip, 5), _background(sf::Quads, 4), _bound(bound), _borderColor(borderColor), _backgroundColor(backgroundColor), _text(text), _hovered(false)
    {
        updatePosition();
        updateColor();
    }

    void VertexButton::updatePosition()
    {
        _border[0].position = sf::Vector2f(_bound.left, _bound.top);
        _border[1].position = sf::Vector2f(_bound.left + _bound.width, _bound.top);
        _border[2].position = sf::Vector2f(_bound.left + _bound.width, _bound.top + _bound.height);
        _border[3].position = sf::Vector2f(_bound.left, _bound.top + _bound.height);
        _border[4].position = sf::Vector2f(_bound.left, _bound.top);

        _background[0].position = sf::Vector2f(_bound.left, _bound.top);
        _background[1].position = sf::Vector2f(_bound.left + _bound.width, _bound.top);
        _background[2].position = sf::Vector2f(_bound.left + _bound.width, _bound.top + _bound.height);
        _background[3].position = sf::Vector2f(_bound.left, _bound.top + _bound.height);
        
        zf::alignText(_text, _bound, AlignmentData());
    }
    
    void VertexButton::updateColor()
    {
        _border[0].color = _borderColor;
        _border[1].color = _borderColor;
        _border[2].color = _borderColor;
        _border[3].color = _borderColor;
        _border[4].color = _borderColor;

        _background[0].color = _backgroundColor;
        _background[1].color = _backgroundColor;
        _background[2].color = _backgroundColor;
        _background[3].color = _backgroundColor;
    }

    void VertexButton::draw(sf::RenderWindow& window, const sf::Time& delta)
    {
        if(_hovered)
        {
            window.draw(_background);
        }
        window.draw(_border);
        window.draw(_text);
    }

    void VertexButton::update(sf::RenderWindow& window, const sf::Time& delta)
    {
    }

    bool VertexButton::inputs(sf::RenderWindow& window, const sf::Time& delta, const zf::Mouse& mouse)
    {
        sf::Vector2f mousePos = mouse.getWorldPosition(window);
        _hovered = _bound.contains(mousePos);
        return _hovered;
    }
}

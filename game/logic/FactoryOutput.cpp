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
#include "FactoryOutput.hpp"
#include "../../z_framework/zf_sfml/animations/CompositeInstruction.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
FactoryOutput::FactoryOutput(Game& game, Type type)
    : _game(game), markedForDestruction(false)
{
    setType(type);
}

FactoryOutput::Type FactoryOutput::getType()
{
    return _type;
}

void FactoryOutput::setType(const FactoryOutput::Type& type)
{
    _type = type;
    if(_type == None)
    {
        _sprite = zf::AnimatableSprite();
    }
    else if(_type == Power)
    {
        _sprite = zf::AnimatableSprite(_game.assets.power.createSprite());
        _sprite.setColor(sf::Color(255, 255, 0));
    }
    else
    {
        _sprite = zf::AnimatableSprite(_game.assets.shadedBox.createSprite());
        _sprite.setColor(FactoryOutput::getColor(type));
    }
}

void FactoryOutput::moveTo(sf::Vector2f startPos, sf::Vector2f endPos, int delay)
{
    _sprite.setScale(1, 1);
    _sprite.setPosition(startPos);
    _sprite.setScale(0.1, 0.1);
    _sprite.setAlpha(255);
    _sprite.animateComposite(_sprite.createCompositeAnimation(true)
            .wait(delay * 0.6 + 0.1)
            .scale(0.1, 1, 0.5)
            .moveTo(startPos, endPos, 1)
            .scale(1, 0.1, 0.5)
            .fade(255, 0, 0.1));
}

void FactoryOutput::moveToAndDestroy(sf::Vector2f startPos, sf::Vector2f endPos, int delay)
{
    _sprite.setScale(1, 1);
    _sprite.setPosition(startPos);
    _sprite.setScale(0.1, 0.1);
    _sprite.setAlpha(255);
    _sprite.animateComposite(_sprite.createCompositeAnimation(true)
            .wait(delay * 0.6 + 0.1)
            .scale(0.1, 1, 0.5)
            .moveTo(startPos, endPos, 1)
            .fade(255, 0, 0.1));
}

void FactoryOutput::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _sprite.update(window, delta);
}

void FactoryOutput::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _sprite.draw(window, delta);
}

bool FactoryOutput::isAnimating()
{
    return _sprite.isAnimating();
}

sf::Sprite FactoryOutput::getSprite()
{
    return _sprite.getSprite();
}

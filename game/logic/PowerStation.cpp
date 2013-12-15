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
#include "PowerStation.hpp"
#include "Board.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
const sf::Vector2f PowerStation::PowerIconOffset = sf::Vector2f(27,28);
PowerStation::PowerStation(Game& game, Board* board)
    : Chip(game, board, Chip::PowerStation)
{
    _background = _game.assets.chipOutline.createSprite();
    _icon = _game.assets.power.createSprite();
}

PowerStation::~PowerStation()
{
}

void PowerStation::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->chipDrawState == Board::Draw_Icon)
    {
        window.draw(_icon);
    }
}

void PowerStation::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}

void PowerStation::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _background.setPosition(_position);
    _icon.setPosition(_position + PowerIconOffset);
}

void PowerStation::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
    zf::setAlpha(_icon, alpha);
}

void PowerStation::beginProcessing()
{
    if(_arrows.hasOut(zf::North))
    {
        _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(new FactoryOutput(_game, FactoryOutput::Power), zf::Grid(-1, 0)));
    }
    if(_arrows.hasOut(zf::East))
    {
        _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(new FactoryOutput(_game, FactoryOutput::Power), zf::Grid(0, 1)));
    }
    if(_arrows.hasOut(zf::South))
    {
        _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(new FactoryOutput(_game, FactoryOutput::Power), zf::Grid(1, 0)));
    }
    if(_arrows.hasOut(zf::West))
    {
        _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(new FactoryOutput(_game, FactoryOutput::Power), zf::Grid(0, -1)));
    }
}

bool PowerStation::isProcessing()
{
    return false;
}

std::vector<std::pair<FactoryOutput*, zf::Grid> > PowerStation::getOutputs()
{
    std::vector<std::pair<FactoryOutput*, zf::Grid> > outputs = _outputs;
    _outputs.clear();
    return outputs;
}

bool PowerStation::acceptInput(FactoryOutput* output)
{
    return false;
}

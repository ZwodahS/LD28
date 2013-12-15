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
#include "Multiplier.hpp"
#include "Board.hpp"
const sf::Vector2f Multiplier::PowerOffset = sf::Vector2f(12, 20);
const sf::Vector2f Multiplier::InputOffset = sf::Vector2f(12, 32);
const sf::Vector2f Multiplier::ArrowOffset = sf::Vector2f(25, 29);
const sf::Vector2f Multiplier::Output1Offset = sf::Vector2f(43, 16);
const sf::Vector2f Multiplier::Output2Offset = sf::Vector2f(43, 32);
Multiplier::Multiplier(Game& game, Board* board)
    : Chip(game, board, Chip::Multiplier), _input("?", game.assets.font, 14)
    , _output1("?", game.assets.font, 14), _output2("?", game.assets.font, 14)
{
    _conversionArrow = _game.assets.conversionArrow.createSprite();
    _powerIcon = _game.assets.power.createSprite();
}

Multiplier::~Multiplier()
{
}

void Multiplier::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->chipDrawState == Board::Draw_Icon)
    {
        window.draw(_powerIcon);
        window.draw(_input);
        window.draw(_conversionArrow);
        window.draw(_output1);
        window.draw(_output2);
    }
}

void Multiplier::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}

void Multiplier::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _powerIcon.setPosition(_position + PowerOffset);
    _conversionArrow.setPosition(_position + ArrowOffset);
    _input.setPosition(_position + InputOffset);
    _output1.setPosition(_position + Output1Offset);
    _output2.setPosition(_position + Output2Offset);
}

void Multiplier::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
    zf::setAlpha(_powerIcon, alpha);
    zf::setAlpha(_conversionArrow, alpha);
    zf::setAlpha(_input, alpha);
    zf::setAlpha(_output1, alpha);
    zf::setAlpha(_output2, alpha);
}

void Multiplier::beginProcessing()
{
}

bool Multiplier::isProcessing()
{
    return false;
}

std::vector<std::pair<FactoryOutput*, zf::Grid> > Multiplier::getOutputs()
{
    std::vector<std::pair<FactoryOutput*, zf::Grid> > outputs;
    return outputs;
}

bool Multiplier::acceptInput(FactoryOutput* output)
{
    if(output == 0 || output->getType() == FactoryOutput::None)
    {
        return false;
    }
    return true;
}

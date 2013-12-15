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
#include "Combiner.hpp"
#include "Board.hpp"
const sf::Vector2f Combiner::Input1Offset = sf::Vector2f(12, 12);
const sf::Vector2f Combiner::Input2Offset = sf::Vector2f(12, 25);
const sf::Vector2f Combiner::Input3Offset = sf::Vector2f(13, 38);
const sf::Vector2f Combiner::ArrowOffset = sf::Vector2f(25, 29);
const sf::Vector2f Combiner::OutputOffset = sf::Vector2f(40, 27);
Combiner::Combiner(Game& game, Board* board)
    : Chip(game, board, Chip::Combiner)
{
    _input1 = _game.assets.shadedBox.createSprite();
    _input2 = _game.assets.shadedBox.createSprite();
    _input3 = _game.assets.power.createSprite();
    _output = _game.assets.shadedBox.createSprite();
    _conversionArrow = _game.assets.conversionArrow.createSprite();
}

Combiner::~Combiner()
{
}

void Combiner::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->chipDrawState == Board::Draw_Icon)
    {
        window.draw(_input1);
        window.draw(_input2);
        window.draw(_input3);
        window.draw(_output);
        window.draw(_conversionArrow);
    }
}

void Combiner::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}

void Combiner::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _conversionArrow.setPosition(_position + ArrowOffset);
    _input1.setPosition(_position + Input1Offset);
    _input2.setPosition(_position + Input2Offset);
    _input3.setPosition(_position + Input3Offset);
    _output.setPosition(_position + OutputOffset);
}

void Combiner::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
    zf::setAlpha(_input1, alpha);
    zf::setAlpha(_input2, alpha);
    zf::setAlpha(_input3, alpha);
    zf::setAlpha(_output, alpha);
    zf::setAlpha(_conversionArrow, alpha);
}

void Combiner::setConversion(FactoryOutput::Type in1, FactoryOutput::Type in2, FactoryOutput::Type output)
{
    _type1 = in1;
    _input1.setColor(FactoryOutput::getColor(in1));
    _type2 = in2;
    _input2.setColor(FactoryOutput::getColor(in2));
    _outputType = output;
    _output.setColor(FactoryOutput::getColor(_outputType));
}

void Combiner::beginProcessing()
{
    FactoryOutput* out1 = 0;
    FactoryOutput* out2 = 0;
    FactoryOutput* power = 0;
    for(std::vector<FactoryOutput*>::iterator it = _inputs.begin() ; it != _inputs.end() ; ++it)
    {
        if((**it).getType() == _type1)
        {
            if(out1 == 0)
            {
                out1 = *it;
            }
        }
        else if((**it).getType() == _type2)
        {
            if(out2 == 0)
            {
                out2 = *it;
            }
        }
        else if((**it).getType() == FactoryOutput::Power)
        {
            if(power == 0)
            {
                power = *it;
            }
        }
    }
    zf::Grid direction;
    if(_arrows.hasOut(zf::North))
    {
        direction = zf::Grid(-1, 0);
    }
    else if(_arrows.hasOut(zf::East))
    {
        direction = zf::Grid(0, 1);
    }
    else if(_arrows.hasOut(zf::South))
    {
        direction = zf::Grid(1, 0);
    }
    else if(_arrows.hasOut(zf::West))
    {
        direction = zf::Grid(0, -1);
    }
    else
    {
        return;
    }
    if(out1 != 0 && out2 != 0 && power != 0)
    {
        for(std::vector<FactoryOutput*>::iterator it = _inputs.begin() ; it != _inputs.end() ; )
        {    
            if(*it == out1 || *it == out2 || *it == power)
            {
                it = _inputs.erase(it);
                continue;
            }
            ++it;
        }
        delete out1;
        delete out2;
        delete power;
        _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(new FactoryOutput(_game, _outputType), direction));
    }
}

bool Combiner::isProcessing()
{
    return false;
}

bool Combiner::acceptInput(FactoryOutput* output)
{
    if(output == 0 || output->getType() == FactoryOutput::None)
    {
        return false;
    }
    if(output->getType() == FactoryOutput::Power || 
            output->getType() == _type1 || output->getType() == _type2)
    {
        return true;
    }
    return false;
}

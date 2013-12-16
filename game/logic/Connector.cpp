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
#include "Connector.hpp"
#include "Board.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
const sf::Vector2f Connector::Arrow1Offset = sf::Vector2f(18, 30);
const sf::Vector2f Connector::Arrow2Offset = sf::Vector2f(25, 30);
const sf::Vector2f Connector::TransferTextBoundOffset = sf::Vector2f(33, 28);
Connector::Connector(Game& game, Board* board)
    : Chip(game, board, Chip::Connector), _transferSpeed(1), _transferSpeedText("1", game.assets.font, 14)
{
    _arrow1Sprite = _game.assets.arrow_right.createSprite();
    _arrow2Sprite = _game.assets.arrow_right.createSprite();
    _transferSpeedTextBound = sf::FloatRect(TransferTextBoundOffset.x , TransferTextBoundOffset.y, 18, 13);
}

Connector::~Connector()
{
}

void Connector::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::draw(window, delta);
    if(_board == 0 || _board->getChipDrawState() == Board::Draw_Icon)
    {
        window.draw(_arrow1Sprite);
        window.draw(_arrow2Sprite);
        window.draw(_transferSpeedText);
    }
}

void Connector::update(sf::RenderWindow& window, const sf::Time& delta)
{
    Chip::update(window, delta);
}

void Connector::setPosition(const sf::Vector2f& position)
{
    Chip::setPosition(position);
    _arrow1Sprite.setPosition(_position + Arrow1Offset);
    _arrow2Sprite.setPosition(_position + Arrow2Offset);
    _transferSpeedTextBound.left = _position.x + TransferTextBoundOffset.x;
    _transferSpeedTextBound.top = _position.y + TransferTextBoundOffset.y;
    zf::alignText(_transferSpeedText, _transferSpeedTextBound, zf::AlignmentData());
}

void Connector::setAlpha(float alpha)
{
    Chip::setAlpha(alpha);
}

void Connector::setTransferSpeed(int speed)
{
    _transferSpeed = speed;
    _transferSpeedText.setString(zf::toString(speed));
}

void Connector::beginProcessing()
{
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
    for(int i = 0 ; i < _transferSpeed; i++)
    {
        if(_inputs.size() > 0)
        {
            FactoryOutput* out = _inputs[0];
            _inputs.erase(_inputs.begin());
            _outputs.push_back(std::pair<FactoryOutput*, zf::Grid>(out, direction));
        }
        else
        {
            break;
        }
    }
}

bool Connector::isProcessing()
{
    return false;
}

bool Connector::acceptInput(FactoryOutput* output)
{
    return true;
}

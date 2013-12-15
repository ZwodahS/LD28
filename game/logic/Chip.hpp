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
#ifndef _GAME_LOGIC_CHIP_H_
#define _GAME_LOGIC_CHIP_H_
#include "Pixel.hpp"
#include "ArrowControl.hpp"
class Game;
class Board;
class Chip
{
public:
    static const sf::Vector2f TimerOffset;
    static const sf::Vector2f TextBoundOffset;
    Chip(Game& game, Board& board);
    virtual ~Chip();

    virtual void draw(sf::RenderWindow& window, const sf::Time& delta);
    virtual void update(sf::RenderWindow& window, const sf::Time& delta);
    virtual void setPosition(const sf::Vector2f& position);
    virtual void rotate();
protected:
    Game& _game;
    Board& _board;
    sf::Sprite _background;
    sf::Sprite _timer;
    sf::Text _timeText;
    sf::FloatRect _textBound;
    sf::Vector2f _position;
    ArrowControl _arrows;
private:
};
#endif

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
#ifndef _GAME_LOGIC_ARROWCONTROL_H_
#define _GAME_LOGIC_ARROWCONTROL_H_
#include <SFML/Graphics.hpp>
#include "../../z_framework/zf_common/Direction.hpp"
#include "../Game.hpp"
class ArrowControl
{
public:
    const static sf::Vector2f NorthArrowOffset;
    const static sf::Vector2f SouthArrowOffset;
    const static sf::Vector2f EastArrowOffset;
    const static sf::Vector2f WestArrowOffset;
    const static sf::Color OutColor;
    const static sf::Color InColor;
    enum ArrowType
    {
        None,
        Out,
        In,
    };
    ArrowControl(Game& game);
    
    /**
     * Return reference for chaining
     */
    ArrowControl& setArrow(zf::Direction direction, ArrowType type);
    void rotate();
    void rotateAnti();

    void setPosition(const sf::Vector2f& position);
    void setAlpha(float alpha);
    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);

    bool hasOut(zf::Direction direction);
    bool hasIn(zf::Direction direction);
private:
    Game& _game;
    ArrowType _north;
    ArrowType _east;
    ArrowType _south;
    ArrowType _west;
    
    sf::Sprite _northSprite;
    sf::Sprite _eastSprite;
    sf::Sprite _southSprite;
    sf::Sprite _westSprite;

    sf::Vector2f _position; // the top left position
};
#endif

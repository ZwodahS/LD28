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
#ifndef _GAME_LOGIC_PIXEL_H_
#define _GAME_LOGIC_PIXEL_H_
#include "../../z_framework/zf_sfml/animations/AnimatableSprite.hpp"
class Game;
class Pixel 
{
public:
    enum Type
    {
        White,
        Red,
        Blue,
        Green,
        Yellow, // Red + Green
        Teal, // Green + Blue
        Magenta, // Blue + Red
    } ;
    
    Pixel(Game& game, Type type = White);

    Type getPixelType();
    void setType(const Type& type);
    static sf::Color getColor(const Type& type)
    {
        switch(type)
        {
            case White : return sf::Color(255,255,255);
            case Red : return sf::Color(255,0,0);
            case Blue : return sf::Color(0,0,255);
            case Green : return sf::Color(0,255,0);
            case Yellow : return sf::Color(255,255,0);
            case Teal : return sf::Color(0,255,255);
            case Magenta : return sf::Color(255,0,255);
        }
    }
    void moveTo(sf::Vector2f startPos, sf::Vector2f endPos, float time);

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
private:
    Game& _game;
    Type _type;
    zf::AnimatableSprite _sprite;
    void updateColor();
};
#endif

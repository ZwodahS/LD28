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
#ifndef _GAME_LOGIC_FACTORYOUTPUT_H_
#define _GAME_LOGIC_FACTORYOUTPUT_H_
#include "../../z_framework/zf_sfml/animations/AnimatableSprite.hpp"
class Game;
class FactoryOutput
{
public:
    enum Type
    {
        None, 
        Pixel_White,
        Pixel_Red,
        Pixel_Green,
        Pixel_Blue,
        Pixel_Yellow,
        Pixel_Teal,
        Pixel_Magenta,
        Power,
    };
    FactoryOutput(Game& game, Type type = None);

    Type getType();
    void setType(const Type& tpye);
    // this will make the object slowly scale up , then move to the location, then scale down.
    // The delay adds a wait instruction before the other animation starts.
    // the delay is the "queue" number of this output.
    void moveTo(sf::Vector2f startPos, sf::Vector2f endPos, int delay);
    void moveToAndDestroy(sf::Vector2f startPos, sf::Vector2f endPos, int delay);
    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    bool isAnimating();

    bool markedForDestruction;
    zf::Grid targetGrid;
    static sf::Color getColor(const Type& type)
    {
        switch(type)
        {
            case Pixel_White : return sf::Color(255,255,255);
            case Pixel_Red : return sf::Color(255,0,0);
            case Pixel_Blue : return sf::Color(0,0,255);
            case Pixel_Green : return sf::Color(0,255,0);
            case Pixel_Yellow : return sf::Color(255,255,0);
            case Pixel_Teal : return sf::Color(0,255,255);
            case Pixel_Magenta : return sf::Color(255,0,255);
            case Power : return sf::Color(255, 255, 0);
            case None : return sf::Color(0, 0, 0);
        }
    }

    sf::Sprite getSprite();
private:
    
    Game& _game;
    Type _type;
    zf::AnimatableSprite _sprite;

};
#endif

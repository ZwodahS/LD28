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
#include "Chip.hpp"
class Connector : public Chip
{
public:
    static const sf::Vector2f Arrow1Offset;
    static const sf::Vector2f Arrow2Offset;
    static const sf::Vector2f TransferTextBoundOffset;
    Connector(Game& game, Board* board = 0);
    ~Connector();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);

    void setPosition(const sf::Vector2f& position);
    void setAlpha(float alpha);

    void setTransferSpeed(int speed);
protected:
    int _transferSpeed;

    sf::Sprite _arrow1Sprite;
    sf::Sprite _arrow2Sprite;
    sf::Text _transferSpeedText;
    sf::FloatRect _transferSpeedTextBound;
};

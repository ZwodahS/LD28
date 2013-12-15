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
class Collector : public Chip
{
public:
    static const sf::Vector2f WestArrowOffset;
    static const sf::Vector2f EastArrowOffset;
    static const sf::Vector2f NorthArrowOffset;
    static const sf::Vector2f SouthArrowOffset;
    static const sf::Vector2f PixelOffset;
    static const sf::Color ArrowColor;
    Collector(Game& game, Board* board = 0);
    ~Collector();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);

    void setPosition(const sf::Vector2f& position);
    void setAlpha(float alpha);

    void beginProcessing();
    bool isProcessing();
    bool acceptInput(FactoryOutput* factory);
    std::vector<std::pair<FactoryOutput*, zf::Grid> > getOutputs();
private:
    sf::Sprite _westArrow;
    sf::Sprite _eastArrow;
    sf::Sprite _northArrow;
    sf::Sprite _southArrow;
    sf::Sprite _pixel;
};

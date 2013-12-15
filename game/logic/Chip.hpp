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
#include "FactoryOutput.hpp"
#include "ArrowControl.hpp"
#include "../../z_framework/zf_common/Grid.hpp"
class Game;
class Board;
class Chip
{
public:
    enum ChipType
    {
        PowerStation,
        Factory,
        Connector,
        Combiner,
        Multiplier,
        Collector,
    } type;
    static const sf::Vector2f TimerOffset;
    static const sf::Vector2f TextBoundOffset;
    Chip(Game& game, Board* board , ChipType type);
    virtual ~Chip();

    virtual void draw(sf::RenderWindow& window, const sf::Time& delta);
    /**
     * Draw a "shadow" of the chip on the board.
     */
    void drawShadow(sf::RenderWindow& window, const sf::Time& delta, const sf::Vector2f& position);
    virtual void update(sf::RenderWindow& window, const sf::Time& delta);
    virtual void setPosition(const sf::Vector2f& position);
    virtual void rotate();
    virtual const sf::FloatRect& getBound();
    virtual void setAlpha(float alpha);
    virtual void setBoard(Board* board);
    void setArrow(ArrowControl::ArrowType north, ArrowControl::ArrowType east, ArrowControl::ArrowType south, ArrowControl::ArrowType west);

    virtual void beginProcessing() = 0;
    virtual bool isProcessing() = 0;
    virtual bool acceptInput(FactoryOutput* factory) = 0;
    bool acceptInputFrom(zf::Direction direction);
    const std::vector<FactoryOutput*>& getInputs();
    virtual std::vector<std::pair<FactoryOutput*, zf::Grid> > getOutputs() = 0;
    void put(FactoryOutput* input);
    bool clockDeplete();
    void animateDestroy();
    bool isAnimating();
    bool markedForDestruction();

    void setClockValue(int clockValue);
protected:
    Game& _game;
    Board* _board;
    int _runLeft;
    sf::Sprite _background;
    sf::Sprite _timer;
    sf::Text _timeText;
    sf::FloatRect _textBound;
    sf::Vector2f _position;
    ArrowControl _arrows;
    sf::FloatRect _bound;

    std::vector<FactoryOutput*> _inputs;
private:
};
#endif

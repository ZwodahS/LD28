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
#ifndef _GAME_LOGIC_BOARD_H_
#define _GAME_LOGIC_BOARD_H_
#include <SFML/Graphics.hpp>
#include "../../z_framework/zf_common/TwoDSpace.hpp"
#include "../../z_framework/zf_common/InputState.hpp"
class Chip;
class Game;
class FactoryOutput;
class Board
{
public:
    static const sf::Vector2f BoardOffset;
    static const float BlinkInterval;
    static const int Max_Row;
    static const int Max_Col;
    Board(Game& game);

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void drawSelectedChip(sf::RenderWindow& window, const sf::Time& delta, Chip* currentChip);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void inputs(sf::RenderWindow& window, const sf::Time& delta);
    Chip* getChip(sf::Vector2f position);
    bool canPlaceChip(const zf::Grid& grid);
    bool inRange(const zf::Grid& grid);
    void placeChip(Chip* chip, const zf::Grid& grid);
    zf::Grid toGrid(sf::Vector2f position);
    
    enum BoardState
    {
        State_Idle,
        State_Processing,
        State_MovingObject,
        State_DestructionOfChip,
    } boardState;

    enum ChipDrawState
    {
        Draw_Icon,
        Draw_Timer,
    } ;

    void runOnce();
    std::vector<FactoryOutput*> getCollectorGoods();
    void collect(FactoryOutput* output);
    int getChipCount();

    ChipDrawState getChipDrawState();
private:
    Game& _game;

    zf::TwoDSpace<Chip*> _chips;

    std::vector<sf::VertexArray> _lines;

    sf::Vector2f chipPosition(int row, int col);
    float _blink;

    std::vector<FactoryOutput*> _factoryOutputs;
    std::vector<FactoryOutput*> _collectorGoods;

    ChipDrawState _chipDrawState;
    zf::InputState _showTimer;
};
#endif

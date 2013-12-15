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
#ifndef _GAME_LOGIC_SHOP_H_
#define _GAME_LOGIC_SHOP_H_
#include <SFML/Graphics.hpp>
#include "../../z_framework/zf_sfml/VertexButton.hpp"
class Player;
class Game;
class Shop
{
public:
    static const int Cost_One_C = 100;
    static const int Cost_Five_C = 400;
    static const int Cost_One_U = 300;
    static const int Cost_Five_U = 1200;
    static const int Cost_One_R = 500;
    static const int Cost_Five_R = 2000;

    static const int StartingPriceBasic = 50;
    static const int StartingPriceAdvanced = 200;
    static const int StartingPriceExpert = 500;

    static const sf::FloatRect Text_RedPrice;
    static const sf::FloatRect Text_GreenPrice;
    static const sf::FloatRect Text_BluePrice;
    static const sf::FloatRect Text_YellowPrice;
    static const sf::FloatRect Text_TealPrice;
    static const sf::FloatRect Text_MagentaPrice;
    static const sf::FloatRect Text_WhitePrice;

    static const sf::FloatRect Text_RedStock;
    static const sf::FloatRect Text_GreenStock;
    static const sf::FloatRect Text_BlueStock;
    static const sf::FloatRect Text_YellowStock;
    static const sf::FloatRect Text_TealStock;
    static const sf::FloatRect Text_MagentaStock;
    static const sf::FloatRect Text_WhiteStock;
    
    static const sf::Vector2f Sprite_Red;
    static const sf::Vector2f Sprite_Green;
    static const sf::Vector2f Sprite_Blue;
    static const sf::Vector2f Sprite_Yellow;
    static const sf::Vector2f Sprite_Teal;
    static const sf::Vector2f Sprite_Magenta;
    static const sf::Vector2f Sprite_White;
    
    static const sf::FloatRect BuyOneCommonButton;
    static const sf::FloatRect BuyFiveCommonButton;
    static const sf::FloatRect BuyOneUncommonButton;
    static const sf::FloatRect BuyFiveUncommonButton;
    static const sf::FloatRect BuyOneRareButton;
    static const sf::FloatRect BuyFiveRareButton;

    Shop(Game& game, Player& player);

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void inputs(sf::RenderWindow& window, const sf::Time& delta);
    void simulatePriceMovement();
    void updateValues();
private:
    Game& _game;
    Player& _player;

    int _price_red;
    int _price_green;
    int _price_blue;
    int _price_yellow;
    int _price_teal;
    int _price_magenta;
    int _price_white;

    zf::VertexButton _button_redSell;
    zf::VertexButton _button_greenSell;
    zf::VertexButton _button_blueSell;
    zf::VertexButton _button_yellowSell;
    zf::VertexButton _button_tealSell;
    zf::VertexButton _button_magentaSell;
    zf::VertexButton _button_whiteSell;

    sf::Text _stock_red;
    sf::Text _stock_green;
    sf::Text _stock_blue;
    sf::Text _stock_yellow;
    sf::Text _stock_teal;
    sf::Text _stock_magenta;
    sf::Text _stock_white;

    sf::Sprite _sprite_red;
    sf::Sprite _sprite_green;
    sf::Sprite _sprite_blue;
    sf::Sprite _sprite_yellow;
    sf::Sprite _sprite_teal;
    sf::Sprite _sprite_magenta;
    sf::Sprite _sprite_white;

    zf::VertexButton _button_buy1C;
    zf::VertexButton _button_buy5C;
    zf::VertexButton _button_buy1U;
    zf::VertexButton _button_buy5U;
    zf::VertexButton _button_buy1R;
    zf::VertexButton _button_buy5R;
    void updatePositions();
};
#endif

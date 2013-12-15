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
#include "Player.hpp"
#include "FactoryOutput.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
const sf::Vector2f Player::DollarIcon = sf::Vector2f(730,18);
const sf::FloatRect Player::DollarText = sf::FloatRect(750, 10, 50, 30);
Player::Player(Game& game)
    : cash(2000), redPixel(0), bluePixel(0), greenPixel(0), magentaPixel(0)
    , tealPixel(0), yellowPixel(0), whitePixel(0), _game(game)
    , _cashText(zf::toString(cash), _game.assets.font, 14), _cashIcon(_game.assets.dollar.createSprite())
{
    updateValues();
    _cashIcon.setPosition(DollarIcon);
    _cashIcon.setColor(sf::Color(0,200,0));
}

void Player::collect(FactoryOutput* output)
{
    switch(output->getType())
    {
        case FactoryOutput::Pixel_Red : redPixel++; break;
        case FactoryOutput::Pixel_Blue : bluePixel++; break;
        case FactoryOutput::Pixel_Green : greenPixel++; break;
        case FactoryOutput::Pixel_Teal : tealPixel++; break;
        case FactoryOutput::Pixel_Yellow : yellowPixel++; break;
        case FactoryOutput::Pixel_Magenta : magentaPixel++; break;
        case FactoryOutput::Pixel_White : whitePixel++; break;
        default : break;
    }
    delete output;
}

void Player::updateValues()
{
    _cashText.setString(zf::toString(cash));
    zf::alignText(_cashText, DollarText, zf::AlignmentData());
}

void Player::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(_cashText);
    window.draw(_cashIcon);
}

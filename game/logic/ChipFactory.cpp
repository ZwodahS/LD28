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
#include "ChipFactory.hpp"

ChipFactory::ChipFactory(Game& game)
    : _game(game)
{
}

PowerStation* ChipFactory::createRandomPowerStation(ChipFactory::Rarity rarity)
{
    PowerStation* station = new PowerStation(_game);
    if(rarity == Common)
    {
        int x = rand() % 2;
        if(x == 0)
        {
            station->setArrow(true, true, false, false);
        }
        else
        {
            station->setArrow(true, false, true, false);
        }
    }
    else if(rarity == Uncommon)
    {
        station->setArrow(true, true, false, true);
    }
    else 
    {
        station->setArrow(true, true, true, true);
    }
    return station;
}

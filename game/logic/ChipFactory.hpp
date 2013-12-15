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
#ifndef _GAME_LOGIC_CHIPFACTORY_H_
#define _GAME_LOGIC_CHIPFACTORY_H_
#include "Chip.hpp"
#include "Collector.hpp"
#include "Combiner.hpp"
#include "Connector.hpp"
#include "Factory.hpp"
#include "Multiplier.hpp"
#include "PowerStation.hpp"
class ChipFactory
{
public:
    enum Rarity
    {
        Common,
        Uncommon,
        Rare,
    };
    ChipFactory(Game& game);
    PowerStation* createPowerStation(Rarity rarity);
    Factory* createFactory(Rarity rarity);
    Connector* createConnector(Rarity rarity);
    Multiplier* createMultiplier(Rarity rarity);
    Collector* createCollector(Rarity rarity);
    Combiner* createCombiner(Rarity rarity);

    std::vector<Chip*> buyChips(Rarity rarity, int amount);
private:
    Game& _game;
};
#endif

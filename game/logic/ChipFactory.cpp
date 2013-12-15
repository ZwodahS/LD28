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

PowerStation* ChipFactory::createPowerStation(ChipFactory::Rarity rarity)
{
    PowerStation* station = new PowerStation(_game);
    if(rarity == Common)
    {
        int x = rand() % 2;
        if(x == 0)
        {
            station->setArrow(ArrowControl::Out, ArrowControl::Out, ArrowControl::None, ArrowControl::None);
        }
        else
        {
            station->setArrow(ArrowControl::Out, ArrowControl::None, ArrowControl::Out, ArrowControl::None);
        }
    }
    else if(rarity == Uncommon)
    {
        station->setArrow(ArrowControl::Out, ArrowControl::Out, ArrowControl::None, ArrowControl::Out);
    }
    else 
    {
        station->setArrow(ArrowControl::Out, ArrowControl::Out, ArrowControl::Out, ArrowControl::Out);
    }
    return station;
}

Factory* ChipFactory::createFactory(ChipFactory::Rarity rarity)
{
    Factory* factory = new Factory(_game);
    if(rarity == Common)
    {
        int r = rand() % 3;
        if(r == 0)
        {
            factory->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::None, ArrowControl::None);
        }
        else if(r == 1)
        {
            factory->setArrow(ArrowControl::Out, ArrowControl::None, ArrowControl::In, ArrowControl::None);
        }
        else if(r == 2)
        {
            factory->setArrow(ArrowControl::Out, ArrowControl::None, ArrowControl::None, ArrowControl::In);
        }   
    }
    else if(rarity == Uncommon)
    {
        int r = rand() % 3;
        if(r == 0)
        {
            factory->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::None);
        }
        else if(r == 1)
        {
            factory->setArrow(ArrowControl::Out, ArrowControl::None, ArrowControl::In, ArrowControl::In);
        }
        else if(r == 2)
        {
            factory->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::None, ArrowControl::In);
        }   
    }
    else if(rarity == Rare)
    {
        factory->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::In);
    }
    int r = rand() % 3;
    if(r == 0)
    {
        factory->setPixelProduction(Pixel::Red);
    }
    else if(r == 1)
    {
        factory->setPixelProduction(Pixel::Blue);
    }
    else 
    {
        factory->setPixelProduction(Pixel::Green);
    }
    return factory;
}

Connector* ChipFactory::createConnector(ChipFactory::Rarity rarity)
{
    Connector* connector = new Connector(_game);
    int r = rand() % 3;
    if(r == 0)
    {
        connector->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::None, ArrowControl::None);
    }
    else if(r == 1)
    {
        connector->setArrow(ArrowControl::Out, ArrowControl::None, ArrowControl::In, ArrowControl::None);
    }
    else if(r == 2)
    {
        connector->setArrow(ArrowControl::Out, ArrowControl::None, ArrowControl::None, ArrowControl::In);
    }
    if(rarity == Common)
    {
        connector->setTransferSpeed(1);
    }
    else if(rarity == Uncommon)
    {
        connector->setTransferSpeed(2);
    }
    else if(rarity == Rare)
    {
        connector->setTransferSpeed(3);
    }
    return connector;
}

Multiplier* ChipFactory::createMultiplier(ChipFactory::Rarity rarity)
{
    Multiplier* multiplier = new Multiplier(_game);
    multiplier->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::In);
    return multiplier;
}

Collector* ChipFactory::createCollector(ChipFactory::Rarity rarity)
{
    Collector* collector = new Collector(_game);
    if(rarity == Common)
    {
        int x = rand() % 2;
        if(x == 0)
        {
            collector->setArrow(ArrowControl::In, ArrowControl::In, ArrowControl::None, ArrowControl::None);
        }
        else
        {
            collector->setArrow(ArrowControl::In, ArrowControl::None, ArrowControl::In, ArrowControl::None);
        }
    }
    else if(rarity == Uncommon)
    {
        collector->setArrow(ArrowControl::In, ArrowControl::In, ArrowControl::None, ArrowControl::In);
    }
    else 
    {
        collector->setArrow(ArrowControl::In, ArrowControl::In, ArrowControl::In, ArrowControl::In);
    }
    return collector;
}

Combiner* ChipFactory::createCombiner(ChipFactory::Rarity rarity)
{
    Combiner* combiner = new Combiner(_game);
    combiner->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::In);
    int r = rand() % 3;
    if(r == 0)
    {
        combiner->setConversion(Pixel::Red, Pixel::Blue, Pixel::Magenta);
    }
    else if(r == 1)
    {
        combiner->setConversion(Pixel::Blue, Pixel::Green, Pixel::Teal);
    }
    else 
    {
        combiner->setConversion(Pixel::Red, Pixel::Green, Pixel::Yellow);
    }
    return combiner;
}

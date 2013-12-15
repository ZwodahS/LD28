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
        station->setClockValue(rand() % 3 + 6);
    }
    else if(rarity == Uncommon)
    {
        station->setArrow(ArrowControl::Out, ArrowControl::Out, ArrowControl::None, ArrowControl::Out);
        station->setClockValue(rand() % 3 + 8);
    }
    else 
    {
        station->setArrow(ArrowControl::Out, ArrowControl::Out, ArrowControl::Out, ArrowControl::Out);
        station->setClockValue(rand() % 3 + 10);
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
        factory->setClockValue(10);
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
        factory->setClockValue(10);
    }
    else if(rarity == Rare)
    {
        factory->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::In);
        factory->setClockValue(10);
    }
    int r = rand() % 3;
    if(r == 0)
    {
        factory->setFactoryOutputProduction(FactoryOutput::Pixel_Red);
    }
    else if(r == 1)
    {
        factory->setFactoryOutputProduction(FactoryOutput::Pixel_Blue);
    }
    else 
    {
        factory->setFactoryOutputProduction(FactoryOutput::Pixel_Green);
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
        connector->setClockValue(20);
    }
    else if(rarity == Uncommon)
    {
        connector->setTransferSpeed(2);
        connector->setClockValue(20);
    }
    else if(rarity == Rare)
    {
        connector->setTransferSpeed(3);
        connector->setClockValue(20);
    }
    return connector;
}

Multiplier* ChipFactory::createMultiplier(ChipFactory::Rarity rarity)
{
    Multiplier* multiplier = new Multiplier(_game);
    multiplier->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::In);
    if(rarity == Common)
    {
        multiplier->setClockValue(4);
    }
    else if(rarity == Uncommon)
    {
        multiplier->setClockValue(6);
    }
    else if(rarity == Rare)
    {
        multiplier->setClockValue(8);
    }
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
        collector->setClockValue(rand() % 3 + 8);
    }
    else if(rarity == Uncommon)
    {
        collector->setArrow(ArrowControl::In, ArrowControl::In, ArrowControl::None, ArrowControl::In);
        collector->setClockValue(rand() % 3 + 13);
    }
    else 
    {
        collector->setArrow(ArrowControl::In, ArrowControl::In, ArrowControl::In, ArrowControl::In);
        collector->setClockValue(rand() % 3 + 18);
    }
    return collector;
}

Combiner* ChipFactory::createCombiner(ChipFactory::Rarity rarity)
{
    Combiner* combiner = new Combiner(_game);
    combiner->setArrow(ArrowControl::Out, ArrowControl::In, ArrowControl::In, ArrowControl::In);
    if(rarity != Rare)
    {
        int r = rand() % 3;
        if(r == 0)
        {
            combiner->setConversion(FactoryOutput::Pixel_Red, FactoryOutput::Pixel_Blue, FactoryOutput::Pixel_Magenta);
        }
        else if(r == 1)
        {
            combiner->setConversion(FactoryOutput::Pixel_Blue, FactoryOutput::Pixel_Green, FactoryOutput::Pixel_Teal);
        }
        else 
        {
            combiner->setConversion(FactoryOutput::Pixel_Red, FactoryOutput::Pixel_Green, FactoryOutput::Pixel_Yellow);
        }
        combiner->setClockValue(rand() % 3 + 8);
    }
    else
    {
        int r = rand() % 3;
        if(r == 0)
        {
            combiner->setConversion(FactoryOutput::Pixel_Red, FactoryOutput::Pixel_Teal, FactoryOutput::Pixel_White);
        }
        else if(r == 1)
        {
            combiner->setConversion(FactoryOutput::Pixel_Blue, FactoryOutput::Pixel_Yellow, FactoryOutput::Pixel_White);
        }
        else 
        {
            combiner->setConversion(FactoryOutput::Pixel_Green, FactoryOutput::Pixel_Magenta, FactoryOutput::Pixel_White);
        }
        combiner->setClockValue(rand() % 3 + 8);
    }
    return combiner;
}

std::vector<Chip*> ChipFactory::buyChips(ChipFactory::Rarity rarity, int amount)
{
    std::vector<Chip*> chips;
    for(int i = 0 ; i < amount ; i++)
    {
        int prob = rand() % 100;
        if(prob < 20)
        {
            chips.push_back(createPowerStation(rarity));
        }
        else if(prob < 40)
        {
            chips.push_back(createFactory(rarity));
        }
        else if(prob < 60)
        {
            chips.push_back(createConnector(rarity));
        }
        else if(prob < 80)
        {
            chips.push_back(createCollector(rarity));
        }
        else if(prob < 90)
        {
            chips.push_back(createCombiner(rarity));
        }
        else
        {
            chips.push_back(createMultiplier(rarity));
        }
    }
    return chips;
}

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
#ifndef _ZF_SFML_FUNCTIONCOMMON_H_
#define _ZF_SFML_FUNCTIONCOMMON_H_
#include "AlignmentData.hpp"
#include "iBoundable.hpp"
#include "../zf_common/Grid.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
namespace zf
{
    static void setAlpha(sf::Sprite& sprite, sf::Int32 alpha, sf::Uint8 max = 255, sf::Uint8 min = 0)
    {
        sf::Color c = sprite.getColor();
        c.a = alpha > max ? max : alpha < min ? min : alpha;
        sprite.setColor(c);
    }

    static void setAlpha(sf::Text& text, sf::Uint8 alpha)
    {
        sf::Color c = text.getColor();
        c.a = alpha;
        text.setColor(c);
    }

    static void setColor(sf::Sprite& sprite, sf::Color color)
    {
        sf::Color c = sprite.getColor();
        c.r = color.r;
        c.g = color.g;
        c.b = color.b;
        sprite.setColor(c);
    }
    /**
     * This is to replace the bug in sf::String which when an empty string is freed, causes a seg fault.
     *
     */
    static void setString(sf::Text& text, std::string value)
    {
        if(value == "")
        {
            text.setString(" ");
        }
        else
        {
            text.setString(value);
        }
    }

    // deprecated
    static void alignTextTopRight(sf::Text& text, sf::Vector2f position)
    {
        sf::FloatRect rect = text.getGlobalBounds();
        text.setPosition(position.x - rect.width, position.y);
    }

    // deprecated
    static void alignTextTopCenter(sf::Text& text, sf::Vector2f position)
    {
        sf::FloatRect rect = text.getGlobalBounds();
        text.setPosition(position.x - (rect.width/2), position.y);
    }

    static void alignSpriteCenter(sf::Sprite& sprite, sf::Vector2f position)
    {
        sf::FloatRect rect = sprite.getGlobalBounds();
        sprite.setPosition(position.x - (rect.width/2), position.y - (rect.height/2));
    }

    /**
     * Align a text based on some data and a position.
     * How this works ?
     * Say I have a text that have a width of 100 and height of 30.
     * Now I want to align it inside a rectangle. I can do it in many ways.
     * If I want to align it to the left side of the rectangle, I can specify a alignmentData of AlignmentX = X_Left, AlignmentY = Y_Center.
     * In this case the offset value is the offset from position. The position is the position of the rectangle that you want the text
     * to align to.
     * The final position of the text will be 
     *      x = (position.x + offset.x)
     *      y = (position.y + height/2 |(15)| + offset.y)
     * Example 2:
     * If I want to align the text to bottom right , I will specify the position value to be the bottom right position That I want to align to.
     * The final position of the text will be
     *      x = (position.x - width |(100)| - offset.x) <- (-)offset.x because you want to "move AWAY" from the position. a negative value will move it towards the position
     *      y = (position.y - height |(30)| - offset.y) <- (-)offset.y , same reason as offset.x
     * 
     * For the case of alignment to center, a positive value will move it downwards, and a negative value will move it upwards.
     */
    static void alignText(sf::Text& text, const sf::Vector2f& position, const AlignmentData& alignmentData)
    {
        // need to take into account the non-zero value in the local bound of text.
        // see http://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
        sf::FloatRect rect = text.getLocalBounds();
        sf::Vector2f finalPosition;
        if(alignmentData.alignmentX == X_Left)
        {
            finalPosition.x = position.x - rect.left + alignmentData.offset.x;
        }
        else if(alignmentData.alignmentX == X_Center)
        {
            finalPosition.x = position.x - rect.left - (rect.width/2) + alignmentData.offset.x;
        }
        else //if(alignmentData.alignmentX == X_Right)
        {
            finalPosition.x = position.x - rect.left - rect.width - alignmentData.offset.x;
        }

        if(alignmentData.alignmentY == Y_Top)
        {
            finalPosition.y = position.y - rect.top + alignmentData.offset.y;
        }
        else if(alignmentData.alignmentY == Y_Center)
        {
            finalPosition.y = position.y - rect.top - (rect.height/2) + alignmentData.offset.y;
        }
        else //if(alignmentData.alignmentY == Y_Bottom)
        {
            finalPosition.y = position.y - rect.top - rect.height - alignmentData.offset.y;
        }
        text.setPosition(finalPosition);
    }
    /**
     * This is the method for aligning a text withing a bound. It makes use of the align Text based on position.
     */ 
    static void alignText(sf::Text& text, const sf::FloatRect& bound, const AlignmentData& alignmentData)
    {
        // need to take into account the non-zero value in the local bound of text.
        // see http://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
        sf::FloatRect rect = text.getLocalBounds();
        sf::Vector2f finalPosition;
        if(alignmentData.alignmentX == X_Left)
        {
            finalPosition.x = bound.left - rect.left + alignmentData.offset.x;
        }
        else if(alignmentData.alignmentX == X_Center)
        {
            finalPosition.x = bound.left + (bound.width/2) - rect.left - (rect.width/2) + alignmentData.offset.x;
        }
        else //if(alignmentData.alignmentX == X_Right)
        {
            finalPosition.x = bound.left + bound.width - rect.left - rect.width - alignmentData.offset.x;
        }
        if(alignmentData.alignmentY == Y_Top)
        {
            finalPosition.y = bound.top - rect.top + alignmentData.offset.y;
        }
        else if(alignmentData.alignmentY == Y_Center)
        {
            finalPosition.y = bound.top + (bound.height/2) - rect.top - (rect.height/2) + alignmentData.offset.y;
        }
        else //if(alignmentData.alignmentY == Y_Bottom)
        {
            finalPosition.y = bound.top + bound.height - rect.top - rect.height - alignmentData.offset.y;
        }
        text.setPosition(finalPosition);
    }
    /**
     * Return the bound of this grid.
     * order ==> 
     * top left, top right, bottom right, bottom left
     */
    static std::vector<sf::Vector2f> toVector2f(zf::Grid grid, float width, float height)
    {
        std::vector<sf::Vector2f> positions;
        positions.push_back(sf::Vector2f(grid.col * width, grid.row * height));
        positions.push_back(sf::Vector2f((grid.col + 1) * width , grid.row * height));
        positions.push_back(sf::Vector2f((grid.col + 1) * width , (grid.row + 1) * height ));
        positions.push_back(sf::Vector2f(grid.col * width, (grid.row + 1) * height ));
        return positions;
    }
    static sf::FloatRect toFloatRect(zf::Grid grid, float width, float height)
    {
        return sf::FloatRect(grid.col * width, grid.row * height, width, height);
    }

    static sf::Vector2f centerOf(zf::Grid grid, float width, float height)
    {
        return sf::Vector2f(grid.col * width + (width/2), grid.row * height + (height / 2));
    }
    template <typename T>
    static sf::Rect<T> moveRect(sf::Rect<T> rect, sf::Vector2<T> moveVec)
    {
        return sf::Rect<T>(rect.left + moveVec.x, rect.top + moveVec.y, rect.width, rect.height); 
    }
    
    static sf::Vector2f getTopLeftPosition(sf::FloatRect boundingBox, sf::Vector2f centerPoint)
    {
        sf::Vector2f finalPosition = sf::Vector2f(
                centerPoint.x - boundingBox.width / 2,
                centerPoint.y - boundingBox.height / 2);
        return finalPosition;
    }

    static void setCenterPosition(iBoundable& boundable, sf::Vector2f position)
    {
        sf::Vector2f finalPosition = getTopLeftPosition(boundable.getBoundingBox(), position);
        boundable.setPosition(finalPosition);
    }

}

#endif

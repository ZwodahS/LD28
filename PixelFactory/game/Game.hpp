#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "Assets.hpp"
#include "../z_framework/zf_sfml/Mouse.hpp"
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
class Screen;
class Game
{
    public:
        Game();
        ~Game();
        void run(); 




        const sf::Int32 width;
        const sf::Int32 height;

        int StartingPriceBasic;
        int StartingPriceAdvanced;
        int StartingPriceExpert;
        int StartingCash;

        std::string title;
        sf::RenderWindow window; 
        zf::Mouse mouse;
        bool isFocused;
        Assets assets;
        void loadAssets();
    private:
        void update(sf::Time delta);
        void draw(sf::Time delta);
        
        Screen* _currentScreen;        
};


#endif


#include "Game.hpp"
#include "screens/Screen.hpp"
#include "screens/GameScreen.hpp"
#include <SFML/Graphics.hpp>

#define CLEAR_COLOR sf::Color(20,20,20,255)
#define GAME_TITLE "Pixel Factory"
#define GAME_WIDTH 960
#define GAME_HEIGHT 960
Game::Game()
    :width(GAME_WIDTH), height(GAME_HEIGHT), title(GAME_TITLE),
    window(sf::VideoMode(width,height),title),mouse(), isFocused(true)
{
}

Game::~Game()
{

}

void Game::run()
{
    loadAssets();
    sf::Clock clock; // set up the clock for delta
    _currentScreen = new GameScreen(*this);
    bool quit = false;
    // Default Generator
    while(!quit && window.isOpen())
    {
        // update clock 
        sf::Time delta = clock.restart();
        // update mouse.
        mouse.update(delta);
        

        // check for events, especially mousewheel
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                quit = true;
            }
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                mouse.wheelDelta = event.mouseWheel.delta;
            }
            else if(event.type == sf::Event::LostFocus)
            {
                isFocused = false;
            }
            else if(event.type == sf::Event::GainedFocus)
            {
                isFocused = true;
            }
        }

        // if not quit , update then draw.
        if(!quit)
        {
            update(delta);
            draw(delta);
        }
    }
}

void Game::update(sf::Time delta)
{
    if(_currentScreen != 0)
    {
        if(isFocused || true)
        {
            _currentScreen->inputs(window, delta);
        }
        _currentScreen->update(window, delta);    
    }
}

void Game::draw(sf::Time delta)
{
    window.clear(CLEAR_COLOR);
    if(_currentScreen != 0)
    {
        _currentScreen->draw(window,delta);   
    }
    window.display();
}

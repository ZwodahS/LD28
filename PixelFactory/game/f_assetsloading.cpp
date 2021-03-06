#include "Game.hpp"
#ifdef APPBUNDLE
#include "../ResourcePath.hpp"
#endif
void Game::loadAssets()
{
    std::string path = ""; 
    #ifdef APPBUNDLE
    path = resourcePath();
    #endif  
    assets.font.loadFromFile(path + "data/upheavtt.ttf");

    assets.master1.create(1280, 1280);
    assets.masterS1.create(&assets.master1, sf::IntRect(0, 0, 300, 300));

    sf::Image image;
    image.loadFromFile(path + "data/chipoutline.png");
    assets.chipOutline = assets.masterS1.createRegion(image, 0, 0);
    image.loadFromFile(path + "data/conversionarrow.png");
    assets.conversionArrow = assets.masterS1.createRegion(image, 64, 0);
    image.loadFromFile(path + "data/box.png");
    assets.shadedBox = assets.masterS1.createRegion(image, 77, 0);
    image.loadFromFile(path + "data/power.png");
    assets.power = assets.masterS1.createRegion(image, 88, 0);
    image.loadFromFile(path + "data/clock.png");
    assets.clock = assets.masterS1.createRegion(image, 101, 0);
    image.loadFromFile(path + "data/dollar.png");
    assets.dollar = assets.masterS1.createRegion(image, 114, 0);
    image.loadFromFile(path + "data/downarrow.png");
    assets.arrow_down = assets.masterS1.createRegion(image, 140, 0);
    image.loadFromFile(path + "data/leftarrow.png");
    assets.arrow_left = assets.masterS1.createRegion(image, 146, 0);
    image.loadFromFile(path + "data/rightarrow.png");
    assets.arrow_right = assets.masterS1.createRegion(image, 152, 0);
    image.loadFromFile(path + "data/uparrow.png");
    assets.arrow_up = assets.masterS1.createRegion(image, 158, 0);

}

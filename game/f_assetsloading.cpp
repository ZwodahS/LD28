#include "Game.hpp"

void Game::loadAssets()
{
    assets.font.loadFromFile("data/upheavtt.ttf");

    assets.master1.create(1280, 1280);
    assets.masterS1.create(&assets.master1, sf::IntRect(0, 0, 300, 300));

    sf::Image image;
    image.loadFromFile("data/chipoutline.png");
    assets.chipOutline = assets.masterS1.createRegion(image, 0, 0);
    image.loadFromFile("data/conversionarrow.png");
    assets.conversionArrow = assets.masterS1.createRegion(image, 64, 0);
    image.loadFromFile("data/box.png");
    assets.shadedBox = assets.masterS1.createRegion(image, 77, 0);
    image.loadFromFile("data/power.png");
    assets.power = assets.masterS1.createRegion(image, 88, 0);
    image.loadFromFile("data/clock.png");
    assets.clock = assets.masterS1.createRegion(image, 101, 0);
    image.loadFromFile("data/dollar.png");
    assets.dollar = assets.masterS1.createRegion(image, 114, 0);
    image.loadFromFile("data/downarrow.png");
    assets.arrow_down = assets.masterS1.createRegion(image, 140, 0);
    image.loadFromFile("data/leftarrow.png");
    assets.arrow_left = assets.masterS1.createRegion(image, 146, 0);
    image.loadFromFile("data/rightarrow.png");
    assets.arrow_right = assets.masterS1.createRegion(image, 152, 0);
    image.loadFromFile("data/uparrow.png");
    assets.arrow_up = assets.masterS1.createRegion(image, 158, 0);

}

#include "../Game.hpp"
#include "Player.hpp"
#include "Shop.hpp"
#include "../screens/GameScreen.hpp" // I really hate to do this
#include "../../z_framework/zf_sfml/f_common.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
const sf::FloatRect Shop::Text_RedPrice     = sf::FloatRect(920, 50, 150, 30);
const sf::FloatRect Shop::Text_GreenPrice   = sf::FloatRect(920, 90, 150, 30);
const sf::FloatRect Shop::Text_BluePrice    = sf::FloatRect(920, 130, 150, 30);
const sf::FloatRect Shop::Text_YellowPrice  = sf::FloatRect(920, 170, 150, 30);
const sf::FloatRect Shop::Text_TealPrice    = sf::FloatRect(920, 210, 150, 30);
const sf::FloatRect Shop::Text_MagentaPrice = sf::FloatRect(920, 250, 150, 30);
const sf::FloatRect Shop::Text_WhitePrice   = sf::FloatRect(920, 290, 150, 30);

const sf::FloatRect Shop::Text_RedStock     = sf::FloatRect(880, 50,  50, 30);
const sf::FloatRect Shop::Text_GreenStock   = sf::FloatRect(880, 90, 50, 30);
const sf::FloatRect Shop::Text_BlueStock    = sf::FloatRect(880, 130, 50, 30);
const sf::FloatRect Shop::Text_YellowStock  = sf::FloatRect(880, 170, 50, 30);
const sf::FloatRect Shop::Text_TealStock    = sf::FloatRect(880, 210, 50, 30);
const sf::FloatRect Shop::Text_MagentaStock = sf::FloatRect(880, 250, 50, 30);
const sf::FloatRect Shop::Text_WhiteStock   = sf::FloatRect(880, 290, 50, 30);

const sf::Vector2f Shop::Sprite_Red     = sf::Vector2f(870, 60);
const sf::Vector2f Shop::Sprite_Green   = sf::Vector2f(870, 100);
const sf::Vector2f Shop::Sprite_Blue    = sf::Vector2f(870, 140);
const sf::Vector2f Shop::Sprite_Yellow  = sf::Vector2f(870, 180);
const sf::Vector2f Shop::Sprite_Teal    = sf::Vector2f(870, 220);
const sf::Vector2f Shop::Sprite_Magenta = sf::Vector2f(870, 260);
const sf::Vector2f Shop::Sprite_White   = sf::Vector2f(870, 300);

const sf::FloatRect Shop::BuyOneCommonButton    = sf::FloatRect(850, 350, 220, 40);
const sf::FloatRect Shop::BuyFiveCommonButton   = sf::FloatRect(850, 400, 220, 40);
const sf::FloatRect Shop::BuyOneUncommonButton  = sf::FloatRect(850, 450, 220, 40);
const sf::FloatRect Shop::BuyFiveUncommonButton = sf::FloatRect(850, 500, 220, 40);
const sf::FloatRect Shop::BuyOneRareButton      = sf::FloatRect(850, 550, 220, 40);
const sf::FloatRect Shop::BuyFiveRareButton     = sf::FloatRect(850, 600, 220, 40);
Shop::Shop(Game& game, Player& player, GameScreen& parent)
    : _game(game), _player(player), _parent(parent)
    , _price_red(_game.StartingPriceBasic), _price_green(_game.StartingPriceBasic), _price_blue(_game.StartingPriceBasic)
    , _price_yellow(_game.StartingPriceAdvanced), _price_teal(_game.StartingPriceAdvanced), _price_magenta(_game.StartingPriceAdvanced)
    , _price_white(_game.StartingPriceExpert)
    , _stock_red("0", game.assets.font, 14)
    , _stock_green("0", game.assets.font, 14)
    , _stock_blue("0", game.assets.font, 14)
    , _stock_yellow("0", game.assets.font, 14)
    , _stock_teal("0", game.assets.font, 14)
    , _stock_magenta("0", game.assets.font, 14)
    , _stock_white("0", game.assets.font, 14)
{
    for(int i = 0 ; i < 20 ; i++)
    {
        simulatePriceMovement();
    }
    _button_redSell = zf::VertexButton(sf::Color(255, 0, 0, 255), sf::Color(255, 0, 0, 100), Text_RedPrice, sf::Text("Sell : " + zf::toString(_price_red), _game.assets.font, 14));
    _button_greenSell = zf::VertexButton(sf::Color(0, 255, 0, 255), sf::Color(0, 255, 0, 100), Text_GreenPrice, sf::Text("Sell : " + zf::toString(_price_green), _game.assets.font, 14));
    _button_blueSell = zf::VertexButton(sf::Color(0, 0, 255, 255), sf::Color(0, 0, 255, 100), Text_BluePrice, sf::Text("Sell : " + zf::toString(_price_blue), _game.assets.font, 14));
    _button_yellowSell = zf::VertexButton(sf::Color(255, 255, 0, 255), sf::Color(255, 255, 0, 100), Text_YellowPrice, sf::Text("Sell : " + zf::toString(_price_yellow), _game.assets.font, 14));
    _button_tealSell = zf::VertexButton(sf::Color(0, 255, 255, 255), sf::Color(0, 255, 255, 100), Text_TealPrice, sf::Text("Sell : " + zf::toString(_price_teal), _game.assets.font, 14));
    _button_magentaSell = zf::VertexButton(sf::Color(255, 0, 255, 255), sf::Color(255, 0, 255, 100), Text_MagentaPrice, sf::Text("Sell : " + zf::toString(_price_magenta), _game.assets.font, 14));
    _button_whiteSell = zf::VertexButton(sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 100), Text_WhitePrice, sf::Text("Sell : " + zf::toString(_price_white), _game.assets.font, 14));

    _button_buy1C = zf::VertexButton(sf::Color(255,255,255), sf::Color(255,255,255,100), BuyOneCommonButton, sf::Text("Buy 1 Common Chip 100", _game.assets.font, 14));
    _button_buy5C = zf::VertexButton(sf::Color(255,255,255), sf::Color(255,255,255,100), BuyFiveCommonButton, sf::Text("Buy 5 Common Chips 400", _game.assets.font, 14));
    _button_buy1U = zf::VertexButton(sf::Color(255,255,255), sf::Color(255,255,255,100), BuyOneUncommonButton, sf::Text("Buy 1 Uncommon Chip 300", _game.assets.font, 14));
    _button_buy5U = zf::VertexButton(sf::Color(255,255,255), sf::Color(255,255,255,100), BuyFiveUncommonButton, sf::Text("Buy 5 Uncommon Chips 1200", _game.assets.font, 14));
    _button_buy1R = zf::VertexButton(sf::Color(255,255,255), sf::Color(255,255,255,100), BuyOneRareButton, sf::Text("Buy 1 Rare Chip 500", _game.assets.font, 14));
    _button_buy5R = zf::VertexButton(sf::Color(255,255,255), sf::Color(255,255,255,100), BuyFiveRareButton, sf::Text("Buy 5 Rare Chips 2000", _game.assets.font, 14));
    
    _sprite_red = _game.assets.shadedBox.createSprite();
    _sprite_red.setColor(sf::Color(255, 0, 0));
    _sprite_red.setPosition(Sprite_Red);
    _sprite_green = _game.assets.shadedBox.createSprite();
    _sprite_green.setColor(sf::Color(0, 255, 0));
    _sprite_green.setPosition(Sprite_Green);
    _sprite_blue = _game.assets.shadedBox.createSprite();
    _sprite_blue.setColor(sf::Color(0, 0, 255));
    _sprite_blue.setPosition(Sprite_Blue);
    _sprite_yellow = _game.assets.shadedBox.createSprite();
    _sprite_yellow.setColor(sf::Color(255, 255, 0));
    _sprite_yellow.setPosition(Sprite_Yellow);
    _sprite_teal = _game.assets.shadedBox.createSprite();
    _sprite_teal.setColor(sf::Color(0, 255, 255));
    _sprite_teal.setPosition(Sprite_Teal);
    _sprite_magenta = _game.assets.shadedBox.createSprite();
    _sprite_magenta.setColor(sf::Color(255, 0, 255));
    _sprite_magenta.setPosition(Sprite_Magenta);
    _sprite_white = _game.assets.shadedBox.createSprite();
    _sprite_white.setColor(sf::Color(255, 255, 255));
    _sprite_white.setPosition(Sprite_White);

    updateValues();
}

void Shop::updateValues()
{
    _stock_red.setString(zf::toString(_player.redPixel));
    _stock_green.setString(zf::toString(_player.greenPixel));
    _stock_blue.setString(zf::toString(_player.bluePixel));
    _stock_yellow.setString(zf::toString(_player.yellowPixel));
    _stock_teal.setString(zf::toString(_player.tealPixel));
    _stock_magenta.setString(zf::toString(_player.magentaPixel));
    _stock_white.setString(zf::toString(_player.whitePixel));
    _button_redSell.setString("Sell : " + zf::toString(_price_red));
    _button_greenSell.setString("Sell : " + zf::toString(_price_green));
    _button_blueSell.setString("Sell : " + zf::toString(_price_blue));
    _button_yellowSell.setString("Sell : " + zf::toString(_price_yellow));
    _button_tealSell.setString("Sell : " + zf::toString(_price_teal));
    _button_magentaSell.setString("Sell : " + zf::toString(_price_magenta));
    _button_whiteSell.setString("Sell : " + zf::toString(_price_white));
    updatePositions();
}

void Shop::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _button_redSell.draw(window, delta);
    _button_greenSell.draw(window, delta);
    _button_blueSell.draw(window, delta);
    _button_yellowSell.draw(window, delta);
    _button_tealSell.draw(window, delta);
    _button_magentaSell.draw(window, delta);
    _button_whiteSell.draw(window, delta);

    window.draw(_stock_red);
    window.draw(_stock_green);
    window.draw(_stock_blue);
    window.draw(_stock_yellow);
    window.draw(_stock_teal);
    window.draw(_stock_magenta);
    window.draw(_stock_white);

    window.draw(_sprite_red);
    window.draw(_sprite_green);
    window.draw(_sprite_blue);
    window.draw(_sprite_yellow);
    window.draw(_sprite_teal);
    window.draw(_sprite_magenta);
    window.draw(_sprite_white);

    _button_buy1C.draw(window, delta);
    _button_buy5C.draw(window, delta);
    _button_buy1U.draw(window, delta);
    _button_buy5U.draw(window, delta);
    _button_buy1R.draw(window, delta);
    _button_buy5R.draw(window, delta);
}

void Shop::update(sf::RenderWindow& window, const sf::Time& delta)
{
}

void Shop::inputs(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_button_redSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.redPixel > 0)
            {
                _player.cash += _price_red;
                _player.redPixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }
    if(_button_greenSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.greenPixel > 0)
            {
                _player.cash += _price_green;
                _player.greenPixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }
    if(_button_blueSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.bluePixel > 0)
            {
                _player.cash += _price_blue;
                _player.bluePixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }
    if(_button_yellowSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.yellowPixel > 0)
            {
                _player.cash += _price_yellow;
                _player.yellowPixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }
    if(_button_tealSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.tealPixel > 0)
            {
                _player.cash += _price_teal;
                _player.tealPixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }
    if(_button_magentaSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.magentaPixel > 0)
            {
                _player.cash += _price_magenta;
                _player.magentaPixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }
    if(_button_whiteSell.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.whitePixel > 0)
            {
                _player.cash += _price_white;
                _player.whitePixel -= 1;
                updateValues();
                _player.updateValues();
            }
        }
    }

    if(_button_buy1C.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.cash >= Cost_One_C)
            {
                _player.cash -= Cost_One_C;
                _player.updateValues();
                _parent.chipsBought(ChipFactory::Common, 1);
            }
        }
    }
    if(_button_buy5C.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.cash >= Cost_Five_C)
            {
                _player.cash -= Cost_Five_C;
                _player.updateValues();
                _parent.chipsBought(ChipFactory::Common, 5);
            }
        }
    }
    if(_button_buy1U.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.cash >= Cost_One_U)
            {
                _player.cash -= Cost_One_U;
                _player.updateValues();
                _parent.chipsBought(ChipFactory::Uncommon, 1);
            }
        }
    }
    if(_button_buy5U.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.cash >= Cost_Five_U)
            {
                _player.cash -= Cost_Five_U;
                _player.updateValues();
                _parent.chipsBought(ChipFactory::Uncommon, 5);
            }
        }
    }
    if(_button_buy1R.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.cash >= Cost_One_R)
            {
                _player.cash -= Cost_One_R;
                _player.updateValues();
                _parent.chipsBought(ChipFactory::Rare, 1);
            }
        }
    }
    if(_button_buy5R.inputs(window, delta, _game.mouse))
    {
        if(_game.mouse.left.thisReleased)
        {
            if(_player.cash >= Cost_Five_R)
            {
                _player.cash -= Cost_Five_R;
                _player.updateValues();
                _parent.chipsBought(ChipFactory::Rare, 5);
            }
        }
    }
}

void Shop::simulatePriceMovement()
{
    _price_red += rand() % 9 - (_price_red < 20 ? 0 : 4);
    _price_green += rand() % 9 - (_price_green < 20 ? 0 : 4);
    _price_blue += rand() % 9 - (_price_blue < 20 ? 0 : 4);
    _price_yellow += rand() % 9 - (_price_yellow < 80 ? 0 : 4);
    _price_teal += rand() % 9 - (_price_teal < 80 ? 0 : 4);
    _price_magenta += rand() % 9 - (_price_magenta < 80 ? 0 : 4);
    _price_white += rand() % 9 - (_price_white < 200 ? 0 : 4);
    updateValues();
}

void Shop::updatePositions()
{
    zf::alignText(_stock_red, Text_RedStock, zf::AlignmentData());
    zf::alignText(_stock_green, Text_GreenStock, zf::AlignmentData());
    zf::alignText(_stock_blue, Text_BlueStock, zf::AlignmentData());
    zf::alignText(_stock_yellow, Text_YellowStock, zf::AlignmentData());
    zf::alignText(_stock_teal, Text_TealStock, zf::AlignmentData());
    zf::alignText(_stock_magenta, Text_MagentaStock, zf::AlignmentData());
    zf::alignText(_stock_white, Text_WhiteStock, zf::AlignmentData());
}

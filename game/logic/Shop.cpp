#include "../Game.hpp"
#include "Player.hpp"
#include "Shop.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
const sf::FloatRect Shop::Text_RedPrice     = sf::FloatRect(780, 70, 150, 30);
const sf::FloatRect Shop::Text_GreenPrice   = sf::FloatRect(780, 120, 150, 30);
const sf::FloatRect Shop::Text_BluePrice    = sf::FloatRect(780, 170, 150, 30);
const sf::FloatRect Shop::Text_YellowPrice  = sf::FloatRect(780, 220, 150, 30);
const sf::FloatRect Shop::Text_TealPrice    = sf::FloatRect(780, 270, 150, 30);
const sf::FloatRect Shop::Text_MagentaPrice = sf::FloatRect(780, 320, 150, 30);
const sf::FloatRect Shop::Text_WhitePrice   = sf::FloatRect(780, 370, 150, 30);

const sf::FloatRect Shop::Text_RedStock     = sf::FloatRect(730, 70,  50, 30);
const sf::FloatRect Shop::Text_GreenStock   = sf::FloatRect(730, 120, 50, 30);
const sf::FloatRect Shop::Text_BlueStock    = sf::FloatRect(730, 170, 50, 30);
const sf::FloatRect Shop::Text_YellowStock  = sf::FloatRect(730, 220, 50, 30);
const sf::FloatRect Shop::Text_TealStock    = sf::FloatRect(730, 270, 50, 30);
const sf::FloatRect Shop::Text_MagentaStock = sf::FloatRect(730, 320, 50, 30);
const sf::FloatRect Shop::Text_WhiteStock   = sf::FloatRect(730, 370, 50, 30);

const sf::Vector2f Shop::Sprite_Red = sf::Vector2f(720, 80);
const sf::Vector2f Shop::Sprite_Green = sf::Vector2f(720, 130);
const sf::Vector2f Shop::Sprite_Blue = sf::Vector2f(720, 180);
const sf::Vector2f Shop::Sprite_Yellow = sf::Vector2f(720, 230);
const sf::Vector2f Shop::Sprite_Teal = sf::Vector2f(720, 280);
const sf::Vector2f Shop::Sprite_Magenta = sf::Vector2f(720, 330);
const sf::Vector2f Shop::Sprite_White = sf::Vector2f(720, 380);

const sf::FloatRect Shop::BuyOneCommonButton = sf::FloatRect(720, 500, 220, 40);
const sf::FloatRect Shop::BuyFiveCommonButton = sf::FloatRect(720, 550, 220, 40);
const sf::FloatRect Shop::BuyOneUncommonButton = sf::FloatRect(720, 600, 220, 40);
const sf::FloatRect Shop::BuyFiveUncommonButton = sf::FloatRect(720, 650, 220, 40);
const sf::FloatRect Shop::BuyOneRareButton = sf::FloatRect(720, 700, 220, 40);
const sf::FloatRect Shop::BuyFiveRareButton = sf::FloatRect(720, 750, 220, 40);
Shop::Shop(Game& game, Player& player)
    : _game(game), _player(player)
    , _price_red(StartingPriceBasic), _price_green(StartingPriceBasic), _price_blue(StartingPriceBasic)
    , _price_yellow(StartingPriceAdvanced), _price_teal(StartingPriceAdvanced), _price_magenta(StartingPriceAdvanced)
    , _price_white(StartingPriceExpert)
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
    _button_redSell.inputs(window, delta, _game.mouse);
    _button_greenSell.inputs(window, delta, _game.mouse);
    _button_blueSell.inputs(window, delta, _game.mouse);
    _button_yellowSell.inputs(window, delta, _game.mouse);
    _button_tealSell.inputs(window, delta, _game.mouse);
    _button_magentaSell.inputs(window, delta, _game.mouse);
    _button_whiteSell.inputs(window, delta, _game.mouse);

    _button_buy1C.inputs(window, delta, _game.mouse);
    _button_buy5C.inputs(window, delta, _game.mouse);
    _button_buy1U.inputs(window, delta, _game.mouse);
    _button_buy5U.inputs(window, delta, _game.mouse);
    _button_buy1R.inputs(window, delta, _game.mouse);
    _button_buy5R.inputs(window, delta, _game.mouse);
}

void Shop::simulatePriceMovement()
{
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

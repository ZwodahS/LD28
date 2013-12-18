#include "ManagedText.hpp"
#include "f_common.hpp"
namespace zf
{
    ManagedText::ManagedText(const sf::Text& t)
        : text(t)
    {
    }

    ManagedText::ManagedText(const sf::String& string, const sf::Font& font, unsigned int characterSize, const sf::Color& color)
        : text(string, font, characterSize)
    {
        text.setColor(color);
    }

    ManagedText::~ManagedText()
    {
        text.setString(" ");
    }

    void ManagedText::setAlignment(const zf::AlignmentData& data, const sf::FloatRect& bBox)
    {
        alignmentData = data;
        boundingBox = bBox;
        updatePosition();
    }

    void ManagedText::setPosition(sf::Vector2f position)
    {
        boundingBox.left = position.x;
        boundingBox.top = position.y;
        updatePosition();
    }

    void ManagedText::updatePosition()
    {
        zf::alignText(text, boundingBox, alignmentData);
    }
}

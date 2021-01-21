#include "Strength.h"

void Strength::settingUpStrength(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    strength = sf::RectangleShape(size);
    strength.setOrigin(sf::Vector2f(size.x/2, size.y/2));
    strength.setFillColor(fillColor);
    strength.setOutlineColor(outlineColor);
    strength.setOutlineThickness(thickness);
    strength.setPosition(position);
    strength.setSize(size);
}

void Strength::setPosition(sf::Vector2f position)
{
    strength.setPosition(position);
}

sf::Shape& Strength::getShape()
{
	return strength;
}
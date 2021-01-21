/********************************************  
Course : TGD2251 Game Physics  
Session: Trimester 2, 2020/21  
ID and Name #1 : 1171100973 Foo Fang Jee
Contacts #1 : 012-6820674 foofangjee@gmail.com  
ID and Name #2 : 1171101517 Michelle Chai Mei Wei  
Contacts #2 : 016-5727809 michelle123679@gmail.com  
********************************************/ 
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
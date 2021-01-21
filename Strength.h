#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Strength
{
    private:
    sf::RectangleShape strength;

    public:
    void settingUpStrength(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void setPosition(sf::Vector2f position);
    sf::Shape& getShape();
};
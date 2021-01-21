#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Wall
{
    private:
    sf::RectangleShape wall;
    b2Body* body;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;

    public:
    void settingUpWall(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void update();
    void setPosition(sf::Vector2f position);
    sf::Shape& getShape();
};
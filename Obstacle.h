#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Obstacle
{
    private:
    sf::CircleShape obstacle;
    //sf::RectangleShape obstacle;
    b2Body* body;
    b2BodyDef bodyDef;
    //b2PolygonShape shape;
    b2CircleShape shape;
    b2FixtureDef fixture;

    public:
    void settingUpObstacle(b2World& world, float radius, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    //void settingUpObstacle(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void update();
    sf::Shape& getShape();
};
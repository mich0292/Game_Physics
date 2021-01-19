#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player
{
    private:
    sf::RectangleShape player;
    b2Body* body;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;

    public:
    void settingUpPlayer(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void update();
    void updateAngle(float angle);
    void updateMovement(b2Vec2 force);
    sf::Shape& getShape();
};
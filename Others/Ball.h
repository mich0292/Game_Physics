#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ball
{
    private:
    sf::CircleShape ball;
    b2Body* body;
    b2BodyDef bodyDef;
    b2CircleShape bodyShape;
    b2FixtureDef bodyFixtureDef;
    float radius;
    float speed;

    public:
    Ball(b2World& world, float speed, float radius, sf::Vector2f position);
    void update();
    sf::Shape& getShape();
};
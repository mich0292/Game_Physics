#include "Ball.h"

static const float PIXEL_PER_METER = 32.0f;

Ball::Ball(b2World& world, float speed, float radius, sf::Vector2f position)
{
    this.speed = speed;
    this.radius = radius;

    sf::CircleShape ball;
    ball.setRadius(radius);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(radius / 2, radius / 2);

    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyShape.m_radius = radius / PIXEL_PER_METER;

    bodyFixtureDef.shape = bodyShape;
    //bodyFixtureDef.density = ;
    //bodyFixtureDef.friction = ;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&bodyFixtureDef);
}

void Ball::update()
{

}

sf::Shape& Ball::getShape()
{
    return ball;
}
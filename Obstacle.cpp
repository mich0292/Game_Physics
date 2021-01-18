#include "Obstacle.h"

static const float PIXEL_PER_METER = 32.0f;

void Obstacle::settingUpObstacle(b2World& world, float radius, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    obstacle = sf::CircleShape(radius);
    obstacle.setOrigin(sf::Vector2f(radius/2, radius/2));
    obstacle.setFillColor(fillColor);
    obstacle.setOutlineColor(outlineColor);
    obstacle.setOutlineThickness(thickness);

    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyDef.type = b2_staticBody;

    shape.m_radius = radius;

	fixture.shape = &shape;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixture);    
}

void Obstacle::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    obstacle.setRotation(body->GetAngle() * 180/b2_pi);
    obstacle.setPosition(body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);
}

sf::Shape& Obstacle::getShape()
{
	return obstacle;
}
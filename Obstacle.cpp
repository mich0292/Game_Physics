#include "Obstacle.h"

static const float PIXEL_PER_METER = 32.0f;

void Obstacle::settingUpObstacle(b2World& world, float radius, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    obstacle = sf::CircleShape(radius);
    obstacle.setOrigin(sf::Vector2f(radius, radius));
    obstacle.setFillColor(fillColor);
    obstacle.setOutlineColor(outlineColor);
    obstacle.setOutlineThickness(thickness);

    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyDef.type = b2_staticBody;

    shape.m_radius = radius/PIXEL_PER_METER;

	fixture.shape = &shape;
    fixture.density = 0.3f;
	fixture.friction = 0.5f;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixture);    
}

// void Obstacle::settingUpObstacle(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
// {
//     obstacle = sf::RectangleShape(size);
//     obstacle.setOrigin(sf::Vector2f(size.x/2, size.y/2));
//     obstacle.setFillColor(fillColor);
//     obstacle.setOutlineColor(outlineColor);
//     obstacle.setOutlineThickness(thickness);

//     bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
//     bodyDef.type = b2_dynamicBody;

//     shape.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);

// 	fixture.shape = &shape;
//     fixture.density = 0.3f;
// 	fixture.friction = 0.5f;

// 	body = world.CreateBody(&bodyDef);
// 	body->CreateFixture(&fixture);    
// }

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
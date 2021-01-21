#include "Wall.h"

static const float PIXEL_PER_METER = 32.0f;

void Wall::settingUpWall(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    wall = sf::RectangleShape(size);
    wall.setOrigin(sf::Vector2f(size.x/2, size.y/2));
    wall.setFillColor(fillColor);
    wall.setOutlineColor(outlineColor);
    wall.setOutlineThickness(thickness);

    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyDef.type = b2_staticBody;

    shape.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);

	fixture.shape = &shape;
    fixture.density = 0.3f;
	fixture.friction = 0.5f;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixture);    
}

void Wall::setPosition(sf::Vector2f position)
{
    body->SetTransform(b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER), body->GetAngle());
}

void Wall::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    wall.setRotation(body->GetAngle() * 180/b2_pi);
    wall.setPosition(body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);
}

sf::Shape& Wall::getShape()
{
	return wall;
}
#include "Planet.h"

static const float PIXEL_PER_METER = 32.0f;

void Planet::settingUpPlanet(b2World& world, float radius, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    planet = sf::CircleShape(radius);
    planet.setOrigin(sf::Vector2f(radius, radius));  

    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyDef.type = b2_staticBody;

    shape.m_radius = radius/PIXEL_PER_METER;
	fixture.shape = &shape;
    fixture.density = 0.3f;
	fixture.friction = 0.5f;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixture);    
}

void Planet::setTexture(sf::Texture* texture)
{
    planet.setTexture(texture, true);
}

void Planet::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    planet.setRotation(body->GetAngle() * 180/b2_pi);
    planet.setPosition(body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);
}

sf::Shape& Planet::getShape()
{
	return planet;
}
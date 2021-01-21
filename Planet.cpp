#include "Planet.h"
#include <cmath>
#include <iostream>

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
	gravitationalForce = 0.02f;
	
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

void Planet::exertGravity(b2Body* playerBody)
{
	//https://mentalgrain.com/box2d/simulating-multiple-sources-of-gravity-in-box2d/
	//https://www.emanueleferonato.com/2012/03/28/simulate-radial-gravity-also-know-as-planet-gravity-with-box2d-as-seen-on-angry-birds-space/
	
	//Find the distance between the player and the planet
	b2Vec2 planetDistance = body->GetWorldCenter() - playerBody->GetWorldCenter();
	float distanceBetween = planetDistance.Length();
		
	//Ensure that the distance is within 3 x planet's radius to calculate the gravitational pull
	if (distanceBetween < 5.0f) //This isn't working, need to fix
	{
		//Get the sum of distance vector components
		//float vecSum = std::abs(planetDistance.x) + std::abs(planetDistance.y);
		
		//planetDistance.x += ((1/vecSum)*planet.getRadius()/distanceBetween);
		//planetDistance.y += ((1/vecSum)*planet.getRadius()/distanceBetween);
		planetDistance *= gravitationalForce;
		playerBody->ApplyForce(planetDistance, playerBody->GetWorldCenter(), true);
		//std::cout << planetDistance.x << " " << planetDistance.y;
	}
	
}

sf::Shape& Planet::getShape()
{
	return planet;
}
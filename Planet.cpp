/********************************************  
Course : TGD2251 Game Physics  
Session: Trimester 2, 2020/21  
ID and Name #1 : 1171100973 Foo Fang Jee
Contacts #1 : 012-6820674 foofangjee@gmail.com  
ID and Name #2 : 1171101517 Michelle Chai Mei Wei  
Contacts #2 : 016-5727809 michelle123679@gmail.com  
********************************************/ 
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
	body->SetUserData(this);
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
		
	//Ensure that when the player is within this distance then it is pulled
	if (distanceBetween < 5.0f)
	{
		planetDistance *= gravitationalForce;
		playerBody->ApplyForce(planetDistance, playerBody->GetWorldCenter(), true);
	}
	
}

b2Body* Planet::getBody() 
{
	return body;
}

sf::Shape& Planet::getShape()
{
	return planet;
}
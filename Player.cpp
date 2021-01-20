#include "Player.h"
#include <stdio.h>    
#include <math.h>

static const float PIXEL_PER_METER = 32.0f;

void Player::settingUpPlayer(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    player = sf::RectangleShape(size);
    player.setOrigin(sf::Vector2f(size.x/2, size.y/2));

    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyDef.type = b2_dynamicBody;

    shape.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);

	fixture.shape = &shape;
    fixture.density = 0.3f;
	fixture.friction = 0.5f;
	
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixture);
	body->SetLinearDamping(0.5f);
	body->SetAngularDamping(0.5f);
    //body->SetFixedRotation(true);
}

//angle in degree
void Player::updateAngle(float angle)
{
    float tempAngle = body->GetAngle();
    tempAngle = tempAngle + (angle * b2_pi/180); //convert degree to radian
    
    body->SetTransform(body->GetPosition(), tempAngle);         
}

void Player::updateMovement(float force)
{
    b2Vec2 forceDirection(cos(body->GetAngle()) * force, sin(body->GetAngle()) * force);
    body->ApplyForceToCenter(forceDirection, true);
}

void Player::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    player.setRotation(body->GetAngle() * 180/b2_pi);
    player.setPosition(body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);
}

void Player::setTexture(sf::Texture* texture)
{
    player.setTexture(texture, true);
}

sf::Shape& Player::getShape()
{
	return player;
}

b2FixtureDef& Player::getFixture()
{
	return fixture;
}

b2Body *Player::getBody() {
  return body;
}



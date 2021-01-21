/********************************************  
Course : TGD2251 Game Physics  
Session: Trimester 2, 2020/21  
ID and Name #1 : 1171100973 Foo Fang Jee
Contacts #1 : 012-6820674 foofangjee@gmail.com  
ID and Name #2 : 1171101517 Michelle Chai Mei Wei  
Contacts #2 : 016-5727809 michelle123679@gmail.com  
********************************************/ 
#include "Player.h"
#include <stdio.h>    
#include <math.h>

static const float PIXEL_PER_METER = 32.0f;

void Player::settingUpPlayer(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness)
{
    player = sf::RectangleShape(size);
    player.setOrigin(sf::Vector2f(size.x/2, size.y/2));
	
	oriPosition = position;
	health = 1;
	
    bodyDef.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
    bodyDef.type = b2_dynamicBody;

    shape.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);

	fixture.shape = &shape;
    fixture.density = 0.3f;
	fixture.friction = 0.5f;
	
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixture);
	body->SetLinearDamping(0.5f);
	body->SetAngularDamping(1.0f);
	body->SetUserData(this);
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
    b2Vec2 forceDirection(cos(body->GetAngle())*force, sin(body->GetAngle())*force);
    body->ApplyForceToCenter(forceDirection, true);
}

void Player::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    player.setRotation(body->GetAngle() * 180/b2_pi);
    player.setPosition(body->GetPosition().x*PIXEL_PER_METER, body->GetPosition().y*PIXEL_PER_METER);
}

void Player::startContact()
{

}

void Player::endContact()
{
	health--;
}

void Player::setTexture(sf::Texture* texture)
{
    player.setTexture(texture, true);
}

sf::Shape& Player::getShape()
{
	return player;
}

b2Body *Player::getBody() 
{
	return body;
}

sf::Vector2f Player::getOriPosition()
{
    return oriPosition;
}

int Player::getHealth()
{
	return health;
}
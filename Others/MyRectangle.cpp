#include "MyRectangle.h"

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
// Why? Refer to Computer Graphics
static const float PIXEL_PER_METER = 32.0f;

MyRectangle::MyRectangle(b2World& world,
                         sf::Vector2f size,
								 sf::Vector2f position,
								 float rotation,
                         bool isDynamic
                         )
{
	rect_ = sf::RectangleShape(size);
	rect_.setOrigin(sf::Vector2f(size.x/2,size.y/2));
	rect_.setFillColor(sf::Color(255, 255, 255, 255));
	rect_.setOutlineThickness(1);
	rect_.setOutlineColor(sf::Color::Black);

	bodyDef_.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);

	if (isDynamic)
   {
      bodyDef_.type = b2_dynamicBody;
   }
   else  
   {
      bodyDef_.type = b2_staticBody;
   }

	bodyShape_.SetAsBox((size.x/2)/PIXEL_PER_METER, (size.y/2)/PIXEL_PER_METER);

	bodyFixtureDef_.shape = &bodyShape_;
	bodyFixtureDef_.density = 0.3f;
	bodyFixtureDef_.friction = 0.5f;

	body_ = world.CreateBody(&bodyDef_);
	body_->CreateFixture(&bodyFixtureDef_);
}

void MyRectangle::setFillColor(sf::Color col)
{
	rect_.setFillColor(col);
}

void MyRectangle::setOutlineThickness(float thickness)
{
	rect_.setOutlineThickness(thickness);
}

void MyRectangle::setOutlineColor(sf::Color col)
{
	rect_.setOutlineColor(col);
}

void MyRectangle::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    rect_.setRotation( body_->GetAngle() * 180/b2_pi);
    rect_.setPosition( body_->GetPosition().x*PIXEL_PER_METER, body_->GetPosition().y*PIXEL_PER_METER);
}

sf::Shape& MyRectangle::getShape()
{
	return rect_;
}
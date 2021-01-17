#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class MyRectangle
{
 private:
	sf::RectangleShape rect_;
	b2Body* body_;
	b2BodyDef bodyDef_;
	b2PolygonShape bodyShape_;
	b2FixtureDef bodyFixtureDef_;

 public:
	MyRectangle(b2World& world,
               sf::Vector2f size,
					sf::Vector2f position,
					float rotation = 0,
               bool isDynamic = true
              );
	void setFillColor(sf::Color col);
	void setOutlineThickness(float thickness);
	void setOutlineColor(sf::Color col);
	void update();
	sf::Shape& getShape();
};
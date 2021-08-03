/********************************************  
Course : TGD2251 Game Physics  
Session: Trimester 2, 2020/21  
ID and Name #1 : 1171100973 Foo Fang Jee
Contacts #1 : 012-6820674 foofangjee@gmail.com  
ID and Name #2 : 1171101517 Michelle Chai Mei Wei  
Contacts #2 : 016-5727809 michelle123679@gmail.com  
********************************************/ 
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player
{
    private:
    sf::RectangleShape player;
    b2Body* body;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
	sf::Vector2f oriPosition;
	int health;

    public:

    void settingUpPlayer(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void update();
    void updateAngle(float angle);
    void updateMovement(float force);
	void startContact();
	void endContact();
	void setTexture(sf::Texture* texture);
    sf::Shape& getShape();
	b2Body* getBody();
	sf::Vector2f getOriPosition();
	int getHealth();
};
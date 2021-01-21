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

class Strength
{
    private:
    sf::RectangleShape strength;

    public:
    void settingUpStrength(b2World& world, sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void setPosition(sf::Vector2f position);
    sf::Shape& getShape();
};
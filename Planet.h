#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Planet
{
    private:
    sf::CircleShape planet;
    b2Body* body;
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixture;

    public:
    void settingUpPlanet(b2World& world, float radius, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness);
    void update();
    void setTexture(sf::Texture* texture);
    sf::Shape& getShape();
};
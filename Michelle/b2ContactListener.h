#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class b2ContactListener
{
	private:
	b2Fixture* GetFixtureA();
	b2Fixture* GetFixtureB();
	
	public:
    vitual void BeginContact(b2Contact* contact);
	vitual void EndContact(b2Contact* contact);
	
};
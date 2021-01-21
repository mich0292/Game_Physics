#include <stdio.h>    
#include <math.h>

class MyContactListener : public b2ContactListener
  {
	//https://www.iforce2d.net/b2dtut/collision-callbacks
    void BeginContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->startContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->startContact();
  
    }
  
    void EndContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Player*>( bodyUserData )->endContact();
    }
  };
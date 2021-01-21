#include <stdio.h>    
#include <math.h>
#include <iostream>

class MyContactListener : public b2ContactListener
  {
	//https://www.iforce2d.net/b2dtut/collision-callbacks
    void BeginContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

      if(bodyUserData && bodyUserData2){
        Planet* planet = (Planet*)contact->GetFixtureB()->GetBody()->GetUserData();
        Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();

        if(planet && player)
        {
            player->startContact();
        }
      }
      
      // if(bodyUserData && bodyUserData2)
      // {
      //   b2Fixture* fixtureA = bodyUserData.GetFixtureList();
      //   b2Fixture* fixtureB = bodyUserData2.GetFixtureList();

      //   if(fixtureA[0].GetShape() == b2CircleShape &&  fixtureB[0].GetShape() == b2RectangleShape)
      //     static_cast<Player*>(bodyUserData2)->startContact();

      //   if(fixtureB[0].GetShape() == b2CircleShape &&  fixtureA[0].GetShape() == b2RectangleShape)
      //     static_cast<Player*>(bodyUserData)->startContact();
      // }
      // void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      // if ( bodyUserData )
      //   static_cast<Player*>( bodyUserData )->startContact();
  
      // //check if fixture B was a ball
      // bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      // if ( bodyUserData )
      //   static_cast<Player*>( bodyUserData )->startContact();
  
    }
  
    void EndContact(b2Contact* contact) {
      
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

      if(bodyUserData && bodyUserData2){
        Planet* planet = (Planet*)contact->GetFixtureB()->GetBody()->GetUserData();
        Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();

        if(planet && player)
        {
            player->endContact();
        }
      }

      // void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      // void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

      // if(bodyUserData && bodyUserData2)
      // {
      //   b2Fixture* fixtureA = bodyUserData.GetFixtureList();
      //   b2Fixture* fixtureB = bodyUserData2.GetFixtureList();

      //   if(fixtureA[0].GetShape() == b2CircleShape &&  fixtureB[0].GetShape() == b2RectangleShape)
      //     static_cast<Player*>(bodyUserData2)->endContact();

      //   if(fixtureB[0].GetShape() == b2CircleShape &&  fixtureA[0].GetShape() == b2RectangleShape)
      //     static_cast<Player*>(bodyUserData)->endContact();
      // }

      // //check if fixture A was a ball
      // void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      // if ( bodyUserData )
      //   static_cast<Player*>( bodyUserData )->endContact();
  
      // //check if fixture B was a ball
      // bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      // if ( bodyUserData )
      //   static_cast<Player*>( bodyUserData )->endContact();
    }
  };
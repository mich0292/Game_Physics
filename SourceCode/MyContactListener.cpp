/********************************************  
Course : TGD2251 Game Physics  
Session: Trimester 2, 2020/21  
ID and Name #1 : 1171100973 Foo Fang Jee
Contacts #1 : 012-6820674 foofangjee@gmail.com  
ID and Name #2 : 1171101517 Michelle Chai Mei Wei  
Contacts #2 : 016-5727809 michelle123679@gmail.com  
********************************************/ 
#include <stdio.h>    
#include <math.h>
#include <iostream>

class MyContactListener : public b2ContactListener
{
	//https://www.iforce2d.net/b2dtut/collision-callbacks
    void BeginContact(b2Contact* contact) 
	{    
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();	

		if(bodyUserData && bodyUserData2)
		{
			Planet* planet = (Planet*)contact->GetFixtureB()->GetBody()->GetUserData();
			Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();

			//check if the collision is between player and planet
			if(planet && player)
			{
				player->startContact();
			}
		}
    }
  
    void EndContact(b2Contact* contact) 
	{    
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

		if(bodyUserData && bodyUserData2)
		{
			Planet* planet = (Planet*)contact->GetFixtureB()->GetBody()->GetUserData();
			Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();

			//check if the collision is between player and planet
			if(planet && player)
			{
				player->endContact();
			}
		}
    }
};
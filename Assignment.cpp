#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "MyRectangle.h"
#include <iostream>
#include <sstream>  // for ostringstream
#include <vector>

int main()
{
    // Timer for fixed update
	float fixedTimeStep = 0.02f; // 50 times per second
	sf::Clock fixedUpdateClock;
	float timeElapsedSinceLastFrame = 0;

	// Window creation
    int windowSizeX=800, windowSizeY=600;
    int windowBorderSize = 16;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML with Box2D");

	// Set vSync to true (and as a result, we have a cap of 60FPS)
	window.setVerticalSyncEnabled(true);
    window.setActive();

	// Create gravity and world, then assign gravity to world
	b2Vec2 gravity(0.f, 9.81f);
	b2World world(gravity);

	// Border creation
	sf::Vector2f horizontalBorderSize(windowSizeX,windowBorderSize);
	sf::Vector2f verticalBorderSize(windowBorderSize,windowSizeY-windowBorderSize*2);
	sf::Vector2f topBorderPos(windowSizeX/2,windowBorderSize/2);
	sf::Vector2f leftBorderPos(windowBorderSize/2,windowSizeY/2);
	sf::Vector2f rightBorderPos(windowSizeX-windowBorderSize/2,windowSizeY/2);
	MyRectangle topBorder(world, horizontalBorderSize, topBorderPos, 0.0, false);
            	topBorder.setOutlineThickness(-1);
	            topBorder.setOutlineColor(sf::Color::Black);
	            topBorder.setFillColor(sf::Color(100, 100, 100));
	MyRectangle leftBorder(world, verticalBorderSize, leftBorderPos, 0.0, false);
              leftBorder.setOutlineThickness(-1);
              leftBorder.setOutlineColor(sf::Color::Black);
              leftBorder.setFillColor(sf::Color(100, 100, 100));
	MyRectangle rightBorder(world, verticalBorderSize, rightBorderPos, 0.0, false);
              rightBorder.setOutlineThickness(-1);
              rightBorder.setOutlineColor(sf::Color::Black);
              rightBorder.setFillColor(sf::Color(100, 100, 100));

	while(window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event));
		{
			// This is input handling via poll event
			// Do not use this for game input
			// Why? Delay issues
			// READ SFML DOCUMENTATION!
			if(event.type == sf::Event::Closed)
			    window.close();
		}

        // We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
		timeElapsedSinceLastFrame += fixedUpdateClock.restart().asSeconds();

		// If sufficient time has elapsed, we update the physics
		if(timeElapsedSinceLastFrame >= fixedTimeStep)
		{
			// Step is used to update physics position/rotation
			world.Step(fixedTimeStep, //update frequency
                    8,                //velocityIterations
                    3                 //positionIterations  
                   );

			// Update the objects that uses physics
			topBorder.update();
			leftBorder.update();
			rightBorder.update();

			// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
			// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
			timeElapsedSinceLastFrame -= fixedTimeStep;
		}

		// Rendering
		window.clear(sf::Color(100, 149, 237));	// CORNFLOWER BLUE!

		// Render all objects
		window.draw(topBorder.getShape());
		window.draw(leftBorder.getShape());
		window.draw(rightBorder.getShape());
		
		window.display();
	}

	return 0;
}

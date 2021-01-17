#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

int main()
{
    //Window size
    int windowSizeX = 800;
    int windowSizeY = 600;

    //gravity
    b2Vec2 gravity(0, 9.81f);

    //World Simulation & Clock
    float timeStep = 1.0f/60.0f;
    float timeElapsedSinceLastFrame = 0;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    sf::Clock fixedUpdateClock;
    
    //Box2D Variables
    b2World world(gravity);

    //load the font
    sf::Font font;
    if(!font.loadFromFile("Assets/Font.ttf"))
        return EXIT_FAILURE;

    //Create the text
    sf::Text text("Testing here", font, 50);

    //create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Title here");

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        //Clock things (restart can get time.delta time and as seconds return value in seconds)
        timeElapsedSinceLastFrame += fixedUpdateClock.restart().asSeconds();

        //Update physics after reach the time step
        if(timeElapsedSinceLastFrame >= timeStep)
        {
            //this functions performs collision detection, integration and constraint solution
            world.Step(timeStep, velocityIterations, positionIterations);
            
            //Update others physics here


            //reset the time
            timeElapsedSinceLastFrame -= timeStep;
        }

        //clear the screen
        window.clear(sf::Color(100, 149, 237));

        //draw here
        window.draw(text);

        //Update the window
        window.display();
    }

    return 0;
}
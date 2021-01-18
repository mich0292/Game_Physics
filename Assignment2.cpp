#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Wall.h"
#include "Obstacle.h"

int main()
{
    //Window size
    int windowSizeX = 800;
    int windowSizeY = 600;
    int windowBorderSize = 16;
    
    //gravity
    b2Vec2 gravity(0, 9.81f);

    //World Simulation & Clock
    float timeStep = 1.0f/60.0f;
    float timeElapsedSinceLastFrame = 0;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    sf::Clock fixedUpdateClock;
    
    //Spawn obstacle clock
    float timeToSpawn = 1.0f;
    float timeElapsedSinceLastSpawn = 0;

    //delta time
    float deltaTime = 0;

    //Box2D Variables
    b2World world(gravity);

    //vector to store a list obstacles
    std::vector<Obstacle> obstacles;

    //load the font
    sf::Font font;
    if(!font.loadFromFile("Assets/Font.ttf"))
        return EXIT_FAILURE;

    //Create the text
    sf::Text text("Testing here", font, 50);

    //create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Title here");

    //Create the wall
    Wall leftWall;
    Wall rightWall;
    Wall topWall;
    Wall bottomWall;

    //Setting up the wall
    leftWall.settingUpWall(world, sf::Vector2f(windowBorderSize, windowSizeY-windowBorderSize*2), sf::Vector2f(windowBorderSize/2,windowSizeY/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    rightWall.settingUpWall(world, sf::Vector2f(windowBorderSize, windowSizeY-windowBorderSize*2), sf::Vector2f(windowSizeX-windowBorderSize/2,windowSizeY/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    topWall.settingUpWall(world, sf::Vector2f(windowSizeX, windowBorderSize), sf::Vector2f(windowSizeX/2,windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    bottomWall.settingUpWall(world, sf::Vector2f(windowSizeX, windowBorderSize), sf::Vector2f(windowSizeX/2,windowSizeY-windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // (restart can get time.delta time and as seconds return value in seconds)
        deltaTime = fixedUpdateClock.restart().asSeconds();

        //Clock things
        timeElapsedSinceLastFrame += deltaTime;
        timeElapsedSinceLastSpawn += deltaTime;

        if(timeElapsedSinceLastSpawn >= timeToSpawn)
        {
            //create new obstacle
            Obstacle temp;
            float tempX = rand() % windowSizeX;
            float tempY = rand() % windowSizeY;
            temp.settingUpObstacle(world, 15.0f, sf::Vector2f(tempX, tempY), sf::Color(100, 100, 100), sf::Color::Black, -1);
            obstacles.push_back(temp);
            
            //reset the time
            timeElapsedSinceLastSpawn -= timeToSpawn;
        }

        //Update physics after reach the time step
        if(timeElapsedSinceLastFrame >= timeStep)
        {
            //this functions performs collision detection, integration and constraint solution
            world.Step(timeStep, velocityIterations, positionIterations);
            
            //Update wall physics
            leftWall.update();
            rightWall.update();
            topWall.update();
            bottomWall.update();

            //update obstacles physics
            for(int i = 0; i < obstacles.size(); i++)
                obstacles[i].update();

            //reset the time
            timeElapsedSinceLastFrame -= timeStep;
        }

        //clear the screen
        window.clear(sf::Color(100, 149, 237));

        //draw text
        window.draw(text);

        //draw wall
        window.draw(leftWall.getShape());
        window.draw(rightWall.getShape());
        window.draw(topWall.getShape());
        window.draw(bottomWall.getShape());

        //draw obstacles
        for(int i = 0; i < obstacles.size(); i++)
                window.draw(obstacles[i].getShape());

        //Update the window
        window.display();
    }

    return 0;
}
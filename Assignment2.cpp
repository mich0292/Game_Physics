#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include "Wall.h"
#include "Obstacle.h"
#include "Player.h"
#include "Strength.h"

//compile assignment2.cpp player.cpp wall.cpp obstacle.cpp strength.cpp
int main()
{
    //Window creation
    int windowSizeX = 800;
    int windowSizeY = 600;
    int windowBorderSize = 16;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Title here");

    //View
    sf::View view;
    view.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    //gravity
    b2Vec2 gravity(0, 0.0f);

    //World Simulation & Clock
    float timeStep = 1.0f/60.0f;
    float timeElapsedSinceLastFrame = 0;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    sf::Clock fixedUpdateClock;
    
    //Spawn obstacle clock
    float timeToSpawn = 1.0f;
    float timeElapsedSinceLastSpawn = 0;

    //Strength clock & variables
    float timeToIncreaseStrength = 1.0f;
    float timeElapsedSinceLastIncrease = 0;
    int totalTimePressed = 0;
    int maxTimePressed = 5;
    float forcePerStrength = 100.0f;

    //button press
    bool buttonPressed = false;

    //score 
    int score = 0;

    //background
    int backgroundWidth = 4155;

    //delta time
    float deltaTime = 0;

    //Box2D Variables
    b2World world(gravity);

    //vector
    std::vector<Obstacle> obstacles;
    std::vector<Strength> strength;
    std::vector<sf::Texture> obstacleTextureV;

    //load the font
    sf::Font font;
    if(!font.loadFromFile("Assets/Font.ttf"))
        return EXIT_FAILURE;

    //load obstacle texture
    sf::Texture obstacleTexture;
    for(int i = 1; i < 12; i++)
    {
        std::string temp = std::to_string(i);
        if(!obstacleTexture.loadFromFile("Assets/Obstacles/" + temp + ".png"))
            return EXIT_FAILURE; 
        obstacleTextureV.push_back(obstacleTexture);
    }

    //load player texture
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("Assets/basic ship.png"))
        return EXIT_FAILURE;

    //load background
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("Assets/background.jpg"))
        return EXIT_FAILURE;

    //Set up background 
    sf::Sprite background(backgroundTexture);
    sf::Sprite background2(backgroundTexture);
    background.setPosition(0, 0);
    background2.setPosition(4155, 0);

    //Create the text
    sf::Text text("Score: ", font, 30);
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setPosition(100, 0);

    //Create the player
    Player player;

    //Setting up the player
    player.settingUpPlayer(world, sf::Vector2f(30.0f, 30.0f), sf::Vector2f(windowSizeX/2,windowSizeY/2), sf::Color(255, 182, 193), sf::Color::Black, -1);
    player.setTexture(&playerTexture);

    //Create the wall
    // Wall leftWall;
    // Wall rightWall;
    // Wall topWall;
    // Wall bottomWall;

    //Setting up the wall
    // leftWall.settingUpWall(world, sf::Vector2f(windowBorderSize, windowSizeY-windowBorderSize*2), sf::Vector2f(windowBorderSize/2,windowSizeY/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    // rightWall.settingUpWall(world, sf::Vector2f(windowBorderSize, windowSizeY-windowBorderSize*2), sf::Vector2f(windowSizeX-windowBorderSize/2,windowSizeY/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    // topWall.settingUpWall(world, sf::Vector2f(windowSizeX, windowBorderSize), sf::Vector2f(windowSizeX/2,windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    // bottomWall.settingUpWall(world, sf::Vector2f(windowSizeX, windowBorderSize), sf::Vector2f(windowSizeX/2,windowSizeY-windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);

    //Creating and setting up strength
    for(int i = 0, posY = 400; i < 5; i++, posY -= 30)
    {
        Strength temp;
        temp.settingUpStrength(world, sf::Vector2f(15.0f, 15.0f), sf::Vector2f(50.0f, posY), sf::Color(0, 255, 0), sf::Color::Black, -1);
        strength.push_back(temp);
    }

    //Game loop
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
        
        //check keyboard event
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(!buttonPressed)
            {
                player.updateAngle(20.0f);
                buttonPressed = true;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(!buttonPressed)
            {
                player.updateAngle(-20.0f);
                buttonPressed = true;
            }
        }
        else
        {
            buttonPressed = false;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            //clock things
            timeElapsedSinceLastIncrease += deltaTime;

            if(timeElapsedSinceLastIncrease >= timeToIncreaseStrength)
            {
                totalTimePressed++;

                //reset the time
                if(totalTimePressed > maxTimePressed * 2)
                    totalTimePressed = 0;
                timeElapsedSinceLastIncrease -= timeToIncreaseStrength;
            }
        }
        else
        {
            int temp = totalTimePressed;

            if(totalTimePressed > maxTimePressed)
                temp = maxTimePressed - (temp - maxTimePressed);

            player.updateMovement(temp * forcePerStrength);
            totalTimePressed = 0;
            timeElapsedSinceLastIncrease = 0;
        }

        //Clock things
        timeElapsedSinceLastFrame += deltaTime;
        timeElapsedSinceLastSpawn += deltaTime;

        if(timeElapsedSinceLastSpawn >= timeToSpawn)
        {
            //create new obstacle
            Obstacle temp;
            float tempX = rand() % windowSizeX;
            float tempY = rand() % windowSizeY;
            int random = rand() % obstacleTextureV.size();
            temp.settingUpObstacle(world, 15.0f, sf::Vector2f(tempX, tempY), sf::Color(100, 100, 100), sf::Color::Black, -1);
            temp.setTexture(&obstacleTextureV[random]);
            obstacles.push_back(temp);
            
            //reset the time
            timeElapsedSinceLastSpawn -= timeToSpawn;
        }

        //Update physics & UI after reach the time step
        if(timeElapsedSinceLastFrame >= timeStep)
        {
            //update physics
            //this functions performs collision detection, integration and constraint solution
            world.Step(timeStep, velocityIterations, positionIterations);
            
            // //Update wall physics
            // leftWall.update();
            // rightWall.update();
            // topWall.update();
            // bottomWall.update();

            //update obstacles physics
            for(int i = 0; i < obstacles.size(); i++)
                obstacles[i].update();

            //update player physics
            player.update();

            //update background
            background.setPosition(background.getPosition().x - 2, background.getPosition().y);
            background2.setPosition(background2.getPosition().x - 2, background2.getPosition().y);

            if (background.getPosition().x <= -backgroundWidth)
                background.setPosition(background2.getPosition().x + backgroundWidth, background.getPosition().y);

            if (background2.getPosition().x <= -backgroundWidth)
                background2.setPosition(background.getPosition().x + backgroundWidth, background.getPosition().y);

            //update UI            
            scoreText.setString(std::to_string(score));

            //reset the time
            timeElapsedSinceLastFrame -= timeStep;
        }

        //set view
        view.setCenter(player.getShape().getPosition());
        window.setView(view);

        //clear the screen
        window.clear(sf::Color(100, 149, 237));

        //draw background
        window.draw(background);
        window.draw(background2);

        //draw text
        window.draw(text);
        window.draw(scoreText);

        // //draw wall
        // window.draw(leftWall.getShape());
        // window.draw(rightWall.getShape());
        // window.draw(topWall.getShape());
        // window.draw(bottomWall.getShape());

        //draw obstacles
        for(int i = 0; i < obstacles.size(); i++)
            window.draw(obstacles[i].getShape());

        //draw player
        window.draw(player.getShape());

        //draw strength
        int temp = totalTimePressed;

        if(totalTimePressed > maxTimePressed)
            temp = maxTimePressed - (temp - maxTimePressed);
        
        for(int i = 0; i < temp; i++)
            window.draw(strength[i].getShape());

        //Update the window
        window.display();
    }

    return 0;
}
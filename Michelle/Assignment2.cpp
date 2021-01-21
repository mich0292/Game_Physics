#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "Wall.h"
#include "Planet.h"
#include "Player.h"
#include "Strength.h"
#include "MyContactListener.cpp"

void saveScore(int);
void readScore();

//compile Assignment2.cpp Planet.cpp Strength.cpp Player.cpp Wall.cpp MyContactListener.cpp
int main()
{
    //Window creation
    int windowSizeX = 800;
    int windowSizeY = 600;
    int windowBorderSize = 16;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Journey");

    //View
    sf::View view;
    view.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    sf::View HUDView;
    HUDView.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
    HUDView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    //gravity
    b2Vec2 gravity(0, 0.0f);

    //World Simulation & Clock
    float timeStep = 1.0f/60.0f;
    float timeElapsedSinceLastFrame = 0;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    sf::Clock fixedUpdateClock;
    
    //Spawn planet clock
    float timeToSpawn = 1.0f;
    float timeElapsedSinceLastSpawn = 0;

    //Strength clock & variables
    float timeToIncreaseStrength = 0.3f;
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
    int backgroundHeight = 2770;

    //delta time
    float deltaTime = 0;

    //Box2D Variables
    b2World world(gravity);

    //vector
    std::vector<Planet> planets;
    std::vector<Strength> strength;
    std::vector<sf::Texture> planetTextureV;

    //load bgm
    sf::Music bgm;
    if (!bgm.openFromFile("Assets/bgm.ogg"))
        return EXIT_FAILURE;

    // Play the music
    bgm.setLoop(true);
    bgm.play();

    //load the font
    sf::Font font;
    if(!font.loadFromFile("Assets/Font.ttf"))
        return EXIT_FAILURE;

    //load planet texture
    sf::Texture planetTexture;
    for(int i = 1; i < 9; i++)
    {
        std::string temp = std::to_string(i);
        if(!planetTexture.loadFromFile("Assets/Planets/" + temp + ".png"))
            return EXIT_FAILURE; 
        planetTextureV.push_back(planetTexture);
    }

    //load player texture
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("Assets/basic ship.png"))
        return EXIT_FAILURE;

    //load background texture
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("Assets/background.jpg"))
        return EXIT_FAILURE;

    //Set up background 
    sf::Sprite background(backgroundTexture);
    sf::Sprite background2(backgroundTexture);
    background.setPosition(0, 0);
    background2.setPosition(4155, 0);

    /*Set up text*/
	//Score text
    sf::Text sText("Score: ", font, 30);
	sText.setPosition(20, 0);
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setPosition(120, 0);
	
	//Health text
	sf::Text hText("Health: ", font, 30);
	hText.setPosition(660, 0);
    sf::Text healthText;
    healthText.setFont(font);
    healthText.setCharacterSize(30);
    healthText.setPosition(770, 0);
	
	//Lose text
	sf::Text endText("You lost.", font, 50);	
	sf::Text retryText("Press Enter to try again.", font, 30);

    //Player
    Player player;
    player.settingUpPlayer(world, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(windowSizeX/2,backgroundHeight/2), sf::Color(255, 182, 193), sf::Color::Black, -1);
    player.setTexture(&playerTexture);
    int playerCurrentBackground = 1;
	
	//Collision
	MyContactListener myContactListenerInstance;
	world.SetContactListener(&myContactListenerInstance);
	
	//Lose
	bool isPlaying = true;
	
    //Create the wall
    Wall leftWall;
    // Wall rightWall;
    Wall topWall;
    Wall bottomWall;

    //Setting up the wall
    leftWall.settingUpWall(world, sf::Vector2f(windowBorderSize, windowSizeY), sf::Vector2f(view.getCenter().x - windowSizeX/2 + windowBorderSize/2, view.getCenter().y), sf::Color(100, 100, 100), sf::Color::Black, -1);
    //rightWall.settingUpWall(world, sf::Vector2f(windowBorderSize, windowSizeY-windowBorderSize*2), sf::Vector2f(windowSizeX-windowBorderSize/2,windowSizeY/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    //topWall.settingUpWall(world, sf::Vector2f(backgroundWidth - windowBorderSize, windowBorderSize), sf::Vector2f((background.getPosition().x + backgroundWidth)/2, background.getPosition().y + windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    //bottomWall.settingUpWall(world, sf::Vector2f(backgroundWidth - windowBorderSize, windowBorderSize), sf::Vector2f((background.getPosition().x + backgroundWidth)/2, background.getPosition().y + backgroundHeight - windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    topWall.settingUpWall(world, sf::Vector2f(windowSizeX, windowBorderSize), sf::Vector2f(view.getCenter().x, background.getPosition().y + windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
    bottomWall.settingUpWall(world, sf::Vector2f(windowSizeX, windowBorderSize), sf::Vector2f(view.getCenter().x, background.getPosition().y + backgroundHeight - windowBorderSize/2), sf::Color(100, 100, 100), sf::Color::Black, -1);
	
    //Creating and setting up strength (the boxes)
    for(int i = 0, posY = 0; i < 5; i++, posY -= 20)
    {
        Strength temp; 
		// 150 -> view is 150.0f and the ship is 40.0f
        temp.settingUpStrength(world, sf::Vector2f(15.0f, 15.0f), sf::Vector2f(windowSizeX/2 - 190.0f, windowSizeY/2 + posY), sf::Color(0, 255, 0), sf::Color::Black, -1);
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
                player.updateAngle(-20.0f);
                buttonPressed = true;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(!buttonPressed)
            {
                player.updateAngle(20.0f);
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
        if (isPlaying)
		{
			timeElapsedSinceLastFrame += deltaTime;
			timeElapsedSinceLastSpawn += deltaTime;
		}

        //create new planet
        if(timeElapsedSinceLastSpawn >= timeToSpawn)
        {            
            Planet temp;
			//150 view, 24 planet radius, 20 wall
            int minX = player.getShape().getPosition().x - view.getSize().x/2 + 194.0f;
			int maxX = player.getShape().getPosition().x + view.getSize().x/2 + 150.0f;
			int minY = player.getShape().getPosition().y - view.getSize().y/2;
			int maxY = player.getShape().getPosition().y + view.getSize().y/2;
            // //float tempX = rand() % windowSizeX;
            // //float tempY = rand() % windowSizeY;
            int tempX = rand() % (maxX - minX) + minX;
            int tempY = rand() % (maxY - minY) + minY;
			/*
			for(int i = 0; i < planets.size(); i++)
			{
				//Ensure the generated posX and posY of the new planet doesn't overlap 
				//Can get stuck
				while (tempX <= planets[i].getShape().getPosition().x + 48.0f && tempX >= planets[i].getShape().getPosition().x - 48.0f)
					tempX = rand() % (maxX - minX) + minX;	
				while (tempY <= planets[i].getShape().getPosition().y + 48.0f && tempX >= planets[i].getShape().getPosition().y - 48.0f)
					tempY = rand() % (maxY - minY) + minY;
			}*/
			srand(time(0));
            int random = rand() % planetTextureV.size();
            temp.settingUpPlanet(world, 48.0f, sf::Vector2f(tempX, tempY), sf::Color(100, 100, 100), sf::Color::Black, -1);
            temp.setTexture(&planetTextureV[random]);
            planets.push_back(temp);
            
            //reset the time
            timeElapsedSinceLastSpawn -= timeToSpawn;
        }

        //Update physics & UI after reach the time step
        if(timeElapsedSinceLastFrame >= timeStep)
        {
            //update physics
            //this functions performs collision detection, integration and constraint solution
            world.Step(timeStep, velocityIterations, positionIterations);
            
            //Update wall physics
            topWall.setPosition(sf::Vector2f(view.getCenter().x, background.getPosition().y + windowBorderSize/2));
            bottomWall.setPosition(sf::Vector2f(view.getCenter().x, background.getPosition().y + backgroundHeight - windowBorderSize/2));
            leftWall.setPosition(sf::Vector2f(view.getCenter().x - windowSizeX/2 + windowBorderSize/2, view.getCenter().y));

            leftWall.update();
            // rightWall.update();
            topWall.update();
            bottomWall.update();

            //update planets physics
            for(int i = 0; i < planets.size(); i++)
			{
				planets[i].update();
				planets[i].exertGravity(player.getBody());
			}               

            //update player physics
            player.update();
			
            //update background
            if(background.getGlobalBounds().contains(player.getShape().getPosition()))
                playerCurrentBackground = 1;
            else
                playerCurrentBackground = 2;

            int rightContraint;

            if(playerCurrentBackground == 1)
            {
                rightContraint = background.getPosition().x + (backgroundWidth * 3/4);
                
                //move the background if the player reach the certain point
                if(player.getShape().getPosition().x >= rightContraint)
                    background2.setPosition(background.getPosition().x + backgroundWidth, background.getPosition().y);
            }
            else
            {
                rightContraint = background2.getPosition().x + (backgroundWidth * 3/4);

                //move the background if the player reach the certain point
                if(player.getShape().getPosition().x >= rightContraint)
                    background.setPosition(background2.getPosition().x + backgroundWidth, background2.getPosition().y);
            }

            //update UI            
            score = player.getShape().getPosition().x - player.getOriPosition().x;
			if (score <= 0) score = 0;
            scoreText.setString(std::to_string(score));
			healthText.setString(std::to_string(player.getHealth()));
            
			//Lose condition
			if (player.getHealth() <= 0)
			{
                std::cout << "Lose all health "<<std::endl;
				isPlaying = false;
				//endText.setPosition(view.getCenter().x, view.getCenter().y);
				//retryText.setPosition(view.getCenter().x, view.getCenter().y);
                endText.setPosition(100, 100);
                retryText.setPosition(100, 200);
				bgm.stop();												
			}	
			
            //reset the time
            timeElapsedSinceLastFrame -= timeStep;
        }

        //set view
        if(player.getShape().getPosition().x + 150.0f > view.getCenter().x)
            view.setCenter(player.getShape().getPosition()+ sf::Vector2f (150.0f, 0.0f));
        else
            view.setCenter(sf::Vector2f(view.getCenter().x, player.getShape().getPosition().y));
		
        window.setView(view);

        //clear the screen
        window.clear(sf::Color(100, 149, 237));

        //draw background
        window.draw(background);
        window.draw(background2);

        //draw player
        window.draw(player.getShape());

        //draw planets
        for(int i = 0; i < planets.size(); i++)
            window.draw(planets[i].getShape());

        //draw wall
        window.draw(leftWall.getShape());
        // window.draw(rightWall.getShape());
        window.draw(topWall.getShape());
        window.draw(bottomWall.getShape());

        //set HUDView
        window.setView(HUDView);
        
        //draw text
        window.draw(sText);
        window.draw(scoreText);
		window.draw(hText);
        window.draw(healthText);
		
		if (!isPlaying)
		{
           // std::cout << "drawText "<<std::endl;
			window.draw(endText);
			window.draw(retryText);
		}
		
        //draw strength
        int temp = totalTimePressed;

        if(totalTimePressed > maxTimePressed)
            temp = maxTimePressed - (temp - maxTimePressed);
        
        for(int i = 0; i < temp; i++)
            window.draw(strength[i].getShape());

        //Update the window
        window.display();
		
		if (!isPlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
		{
			isPlaying = true;
			saveScore(score);
			score = 0;
			planets.clear();
			player.restart(sf::Vector2f(windowSizeX/2,backgroundHeight/2));
			view.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
			HUDView.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
			bgm.play();			
		}
    }

    return 0;
}

void readScore()
{
    std::string score;
    std::ifstream scoreFile("score.txt");

    if (scoreFile.is_open())
    {
        while ( getline (scoreFile,score) )
        {
            std::cout << score << '\n';
        }
        scoreFile.close();
    }
    else std::cout << "Unable to open file"; 
}

void saveScore(int score)
{
    std::ofstream scoreFile("score.txt");
    if (scoreFile.is_open())
    {
        scoreFile << score << '\n';
        scoreFile.close();
    }
    else 
        std::cout << "Unable to open file";
}
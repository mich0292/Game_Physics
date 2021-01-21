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
bool checkSpawnLocationX(float, float, std::vector<Planet>);
bool checkSpawnLocationY(float, float, std::vector<Planet>);
void readScore(std::vector<int>& scoreVector);
bool sortFunction(int num1, int num2);
bool checkSpawn(Player player, sf::Vector2f randomPosition, std::vector<Planet>);

//compile Assignment2.cpp Planet.cpp Strength.cpp Player.cpp Wall.cpp MyContactListener.cpp
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
    float forcePerStrength = 100.0f;
    int totalTimePressed = 0;
    int maxTimePressed = 5;

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
    std::vector<int> scores;
    std::vector<sf::Text> scoreTextV;

    //Score board
    bool drawScoreBoard = false;
    bool readFile = false;
    bool saveFile = false;

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
    sf::Text retryText2("Press Enter to try again.", font, 30);
    sf::Text checkScoreText("Press Tab to check score.", font, 30);
    endText.setPosition(100, 100);
    retryText.setPosition(100, 200);
    retryText2.setPosition(220, 500);
    checkScoreText.setPosition(100, 300);
    sf::Text scoreBoardText("Score Board", font, 50);
    scoreBoardText.setPosition(250, 10);

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

            while(!checkSpawn(player, sf::Vector2f(tempX, tempY), planets))
            {
                tempX = rand() % (maxX - minX) + minX;
                tempY = rand() % (maxY - minY) + minY;
            }
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
            scoreText.setString(std::to_string(score));
			healthText.setString(std::to_string(player.getHealth()));
            
            //update strength UI
            for(int i = 0, posY = 0; i < 5; i++, posY -= 20)
            {
                sf::Vector2i pixelPosition = window.mapCoordsToPixel(sf::Vector2f(player.getShape().getPosition().x - 40.0f, player.getShape().getPosition().y + 10 + posY), view);
                sf::Vector2f newPosition = window.mapPixelToCoords(pixelPosition, HUDView);
                //sf::Vector2i pixelPosition = render.mapCoordsToPixel(sf::Vector2f(player.getShape().getPosition().x - 40.0f, player.getShape().getPosition().y - 40 + posY));
                // sf::Vector2f newPosition = sf::RenderTarget::mapPixelToCoords(&pixelPosition, &HUDView);
                strength[i].setPosition(newPosition);
            }

			//Lose condition
			if (player.getHealth() <= 0)
			{
				isPlaying = false;
			}	
			
            //reset the time
            timeElapsedSinceLastFrame -= timeStep;
        }

        //set view
        if(player.getShape().getPosition().x + 150.0f > view.getCenter().x && player.getShape().getPosition().y > windowSizeY/2 && player.getShape().getPosition().y < backgroundHeight - windowSizeY/2)
            view.setCenter(player.getShape().getPosition()+ sf::Vector2f (150.0f, 0.0f));
        else if(player.getShape().getPosition().y > windowSizeY/2 && player.getShape().getPosition().y > windowSizeY/2 && player.getShape().getPosition().y < backgroundHeight - windowSizeY/2)
            view.setCenter(sf::Vector2f(view.getCenter().x, player.getShape().getPosition().y));     
        else if(player.getShape().getPosition().x + 150.0f > view.getCenter().x)
            view.setCenter(sf::Vector2f(player.getShape().getPosition().x + 150.0f, view.getCenter().y));           
        window.setView(view);

        //clear the screen
        window.clear(sf::Color(100, 149, 237));

        //draw background
        window.draw(background);
        window.draw(background2);

        if(isPlaying)
        {
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
        }

        //set HUDView
        window.setView(HUDView);
        
        //draw text
        if(isPlaying)
        {
            window.draw(sText);
            window.draw(scoreText);
            window.draw(hText);
            window.draw(healthText);
        }		
		else if(!drawScoreBoard)
		{
			window.draw(endText);
			window.draw(retryText);
            window.draw(checkScoreText);
		}		
        else
        {
            if(!readFile)
            {                
                readFile = true;
                readScore(scores);
                std::sort(scores.begin(), scores.end(), sortFunction);
                
                int size;
                if(scores.size() > 10)
                    size = 10;
                else
                    size = scores.size();

                for(int i = 0, posY = 0; i < size; i++, posY += 30)
                {
                    sf::Text temp;
                    temp.setFont(font);
                    temp.setCharacterSize(30);
                    temp.setPosition(250, 100 + posY);
                    temp.setString(std::to_string(i+1) + "    " + std::to_string(scores[i]));
                    scoreTextV.push_back(temp);
                }
            }            
            window.draw(scoreBoardText);
            window.draw(retryText2);
            for(int i = 0; i < scoreTextV.size(); i++)
                window.draw(scoreTextV[i]);
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
            drawScoreBoard = false;
            readFile = false;
			isPlaying = true;
            scoreTextV.clear();
            scores.clear();
            if(!saveFile)
			    saveScore(score);
            saveFile = false;
			score = 0;
            timeElapsedSinceLastFrame = 0;
            timeElapsedSinceLastIncrease = 0;
            timeElapsedSinceLastSpawn = 0;
            totalTimePressed = 0;
            playerCurrentBackground = 1;

            background.setPosition(0, 0);
            background2.setPosition(4155, 0);

            for(int i = 0; i < planets.size(); i++)
                world.DestroyBody(planets[i].getBody());

            world.DestroyBody(player.getBody());
			planets.clear();

            player.settingUpPlayer(world, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(windowSizeX/2,backgroundHeight/2), sf::Color(255, 182, 193), sf::Color::Black, -1);
            player.setTexture(&playerTexture);

			view.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
			HUDView.reset(sf::FloatRect(0, 0, windowSizeX, windowSizeY));
			bgm.play();	
		}
        else if(!isPlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !drawScoreBoard)
        {
            saveFile = true;
            saveScore(score);
            drawScoreBoard = true;
        }
    }

    return 0;
}

void readScore(std::vector<int>& scoreVector)
{
    std::string score;
    std::ifstream scoreFile("score.txt");

    if (scoreFile.is_open())
    {
        while ( getline (scoreFile,score) )
        {
            scoreVector.push_back(std::stoi(score));
        }
        scoreFile.close();
    }
    else std::cout << "Unable to open file"; 
}

void saveScore(int score)
{
    std::ofstream file;

    file.open("score.txt", std::ios_base::app);

    if(file.is_open())
    {
        file << score << std::endl;
        file.close();
    }
    else
        std::cout << "Unable to open file";
    
    // std::fstream fs;
	// fs.open ("score.txt",std::fstream::in | std::fstream::out | std::fstream::app);
	// std::string line;
    // if (fs.is_open())
    // {
	// 	while (getline(fs,line))
    //     {
    //         if (!line.empty())
	// 			fs << score << std::endl;
    //     }
    //     fs.close();
    // }
    // else 
    //     std::cout << "Unable to open file";
}

bool checkSpawnLocationX(float posX, float playerPosX, std::vector<Planet> planets)
{
	//Remember the coordinates (0,0 is top left)
	if (posX >= playerPosX + 32.0f || posX <= playerPosX - 32.0f)
	{
		for (int i = 0; i < planets.size(); i++)
		{
			//48.0 is the planet size
			if (posX <= planets[i].getShape().getPosition().x + 80.0f 
			|| posX >= planets[i].getShape().getPosition().x - 80.0f)
				return true;
		}
	}
	std:: cout << "PosX check failed";
	return false;
}

bool sortFunction(int num1, int num2)
{
    return (num2 < num1);
}

bool checkSpawnLocationY(float posY, float playerPosY, std::vector<Planet> planets)
{
	if (posY >= playerPosY + 32.0f || posY <= playerPosY - 32.0f)
	{
		for (int i = 0; i < planets.size(); i++)
		{
			if (posY <= planets[i].getShape().getPosition().y + 80.0f 
			|| posY >= planets[i].getShape().getPosition().y - 80.0f)
				return true;
		}
	}
	std:: cout << "PosY check failed";
	return false;	
}

bool checkSpawn(Player player, sf::Vector2f randomPosition, std::vector<Planet> planets)
{
    sf::FloatRect temp(randomPosition.x-48, randomPosition.y-48, 96, 96);

    if(player.getShape().getGlobalBounds().intersects(temp))
        return false;
    else
    {
        for(int i = 0; i < planets.size(); i++)
        {
            if(planets[i].getShape().getGlobalBounds().intersects(temp))
                return false;
        }
    }
    return true;
}
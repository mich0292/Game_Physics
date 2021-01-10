#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

int main(){
    //window creation
    int windowSizeX = 800;
    int windowSizeY = 600;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Game Title here");

    //Load music to play 
    sf::Music music;
    if(!music.openFromFile("filename here"))
        return EXIT_FAILURE;
    music.play();

    //create a graphical text to display
    sf::Font font;
    if(!font.openFromFile("filename here"))
        return EXIT_FAILURE;
    sf::Text text("text here", font, fontsizehere);

    while(window.isOpen()){
        //process events
        sf::Event event;

        while(window.pollEvent(event)){
            //Close window: exit
            if(event.type == sf::Event::Closed)
                window.close();
        }

        //clear screen
        window.clear();

        //draw sprite
        window.draw();

        //draw text
        window.draw();

        //Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
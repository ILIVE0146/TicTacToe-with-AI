#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "files_check.hpp"
#include <SFML/Window.hpp>
int main()
{
	
	
	imageCheck ch;
	if(ch.check_image_exist() == false){
		sf::Window ErrorWindow(sf::VideoMode(300,100), "ERROR,Files not Found!", sf::Style::Close);
		ErrorWindow.setFramerateLimit(60);
		while(ErrorWindow.isOpen()){
			sf::Event event;
			while (ErrorWindow.pollEvent(event))
        	{
            	if (event.type == sf::Event::Closed){
                	ErrorWindow.close();
					exit(0);
				}
			}
		}
	}
	GameEngine::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic-Tac-Toe");
}
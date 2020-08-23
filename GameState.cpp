#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
namespace GameEngine{
	GameState::GameState(GameDataRef data) : _data(data){ }
	void GameState::Init(){
		/*
			For loading data
		*/
        gamestate = State_playing;
        turn = Player_piece;
        this->_data->assets.LoadTexture("Pause Button",Pause_btn);
        _pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
        _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width,_pauseButton.getPosition().y);
    }
	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            if(this->_data->input.IsSpriteClicked(this->_pauseButton,sf::Mouse::Left,this->_data->window)){
                std::cout<<"pause the game"<<std::endl;
            }
		}
	}
	void GameState::Update(float dt)
	{
		
	}
	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(142,237,210));
        this->_data->window.draw(this->_pauseButton);
		this->_data->window.display();
	}
}
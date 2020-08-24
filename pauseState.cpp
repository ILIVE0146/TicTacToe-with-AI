#include <sstream>
#include "pauseState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
namespace GameEngine{
	PauseState::PauseState(GameDataRef data) : _data(data){ }
	void PauseState::Init(){
		/*
			For loading data
		*/
        this->_data->assets.LoadTexture("Home Button",Home_button);
        this->_data->assets.LoadTexture("Resume Button",resume_button);
		this->resumeButton.setTexture(this->_data->assets.GetTexture("Resume Button"));
		this->homebuton.setTexture(this->_data->assets.GetTexture("Home Button"));
		this->resumeButton.setPosition((this->_data->window.getSize().x /2) - (this->resumeButton.getLocalBounds().width/2),(this->_data->window.getSize().y/3) - (this->resumeButton.getLocalBounds().height/2));
		this->homebuton.setPosition((this->_data->window.getSize().x /2) - (this->homebuton.getLocalBounds().width/2),(this->_data->window.getSize().y/3 * 2) - (this->homebuton.getLocalBounds().height/2));
	}
	void PauseState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if(this->_data->input.IsSpriteClicked(this->resumeButton,sf::Mouse::Left,this->_data->window)){
				this->_data->machine.RemoveState();
			}
            if(this->_data->input.IsSpriteClicked(this->homebuton,sf::Mouse::Left,this->_data->window)){
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
			}
		}
	}
	void PauseState::Update(float dt)
	{
		
	}
	void PauseState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(142,237,210));
        this->_data->window.draw(this->resumeButton);
		this->_data->window.draw(this->homebuton);
		this->_data->window.display();
	}
}
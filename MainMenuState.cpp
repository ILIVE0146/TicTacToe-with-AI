#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include "playOptionState.hpp"
namespace GameEngine{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data){ }
	void MainMenuState::Init(){
		/*
			For loading data
		*/
		//this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON);
		this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->_data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);
		this->_data->assets.LoadTexture("play botton alternative",PLAY_BTN_ALTER );
		this->_data->assets.LoadTexture("X Win", X_PATH);
		this->_data->assets.LoadTexture("O Win",O_PATH);
		//this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_data->assets.LoadFont("Felt",FELT_FRONT);
		/*
			For logo
		*/
		this->x.setTexture(this->_data->assets.GetTexture("X Win"));
		this->o.setTexture(this->_data->assets.GetTexture("O Win"));
		this->x.setPosition(100,200);
		this->x.setScale(0.5,0.5);
		this->o.setPosition(150,250);
		this->o.setScale(0.4,0.4);
		/*
			for play button
		*/
		this->_play.setFont(this->_data->assets.GetFont("Felt"));
		this->_play.setPosition((SCREEN_WIDTH / 2) - (this->_play.getGlobalBounds().width / 2) - 30, (SCREEN_HEIGHT / 2) - (this->_play.getGlobalBounds().height / 2) - 20);
		this->_play.setString("PLAY");
		this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_playButton.setScale(0.1,0.1);
		this->_playButton.setPosition((SCREEN_WIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_playButton.getGlobalBounds().height / 2));
		/*
			For bottom bar lines
		*/
		this->_playButtonOuter.setPosition(75,800);
		this->_playButtonOuter.setTexture(this->_data->assets.GetTexture("Play Button Outer"));
		this->_playButtonOuter.setScale(1.25,1);
		/*
			For title card
		*/
		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height * 0.1);
		/*
			For options button
		*/	
		this->_option.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_option.setPosition(this->_playButton.getPosition().x , this->_playButton.getPosition().y + 100);
		this->_option.setScale(0.1,0.1);
		this->_options.setFont(this->_data->assets.GetFont("Felt"));
		this->_options.setPosition(this->_option.getPosition().x + 60 , this->_option.getPosition().y + 5);
		this->_options.setString("OPTIONS");

		/*
			For exit button
		*/
		this->_exit_btn.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_exit_btn.setScale(0.1,0.1);
		this->_exit_btn.setPosition(this->_playButton.getPosition().x , this->_playButton.getPosition().y + 200);
		this->_exit.setFont(this->_data->assets.GetFont("Felt"));
		this->_exit.setPosition(this->_exit_btn.getPosition().x + 85 , this->_exit_btn.getPosition().y + 5);
		this->_exit.setString("EXIT");
	}
	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if(this->_playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->_playButton.setTexture(this->_data->assets.GetTexture("play botton alternative"));
			}
			else{
				this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
			}
			if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new PlayOptionState(_data)),true);
			}
			if(this->_option.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->_option.setTexture(this->_data->assets.GetTexture("play botton alternative"));
			}
			else{
				this->_option.setTexture(this->_data->assets.GetTexture("Play Button"));
			}
			if (this->_data->input.IsSpriteClicked(this->_option, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Go To options Screen" << std::endl;
			}
			if(this->_exit_btn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->_exit_btn.setTexture(this->_data->assets.GetTexture("play botton alternative"));
			}
			else{
				this->_exit_btn.setTexture(this->_data->assets.GetTexture("Play Button"));
			}
			if (this->_data->input.IsSpriteClicked(this->_exit_btn, sf::Mouse::Left, this->_data->window))
			{
				this->_data->window.close();
			}
		}
	}
	void MainMenuState::Update(float dt)
	{
		
	}
	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(142,237,210));
		this->_data->window.draw(this->x);
		this->_data->window.draw(this->o);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_playButtonOuter);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_play);
		this->_data->window.draw(this->_option);
		this->_data->window.draw(this->_options);
		this->_data->window.draw(this->_exit_btn);
		this->_data->window.draw(this->_exit);
		this->_data->window.display();
	}
}
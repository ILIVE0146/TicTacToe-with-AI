#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "playOptionState.hpp"
#include "options.hpp"
#include "rgba.hpp"
#include <fstream>
#include <iostream>
namespace GameEngine{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data){ }
	void MainMenuState::Init(){
		this->boolIsdefaultTheme();
		/*
			For loading data
		*/
		this->_data->themeDefault = new rgba();
		this->_data->themeNew = new rgba(true);
		this->_data->assets.LoadTexture("Resume Button",resume_button);
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("Retry Button", "Resources/res/Retry Button.png");
		this->_data->assets.LoadTexture("Home Button", "Resources/res/Home Button.png");
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON);
		this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->_data->assets.LoadTexture("X Win", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Win",O_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadFont("Felt",FELT_FRONT);
		this->_data->assets.LoadFont("arial","Resources/fonts/ARIAL.TTF");

		/*
			for play button
		*/
		this->_play.setFont(this->_data->assets.GetFont("Felt"));
		this->_play.setPosition((SCREEN_WIDTH / 2) - (this->_play.getGlobalBounds().width / 2) - 30, (SCREEN_HEIGHT / 2) - (this->_play.getGlobalBounds().height / 2) - 20);
		this->_play.setString("PLAY");
		this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_playButton.setPosition((SCREEN_WIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_playButton.getGlobalBounds().height / 2));
		/*
			For bottom bar lines
		*/
		this->_playButtonOuter.setPosition(0,0);
		this->_playButtonOuter.setTexture(this->_data->assets.GetTexture("Play Button Outer"));
		/*
			For title card
		*/
		/*
			For options button
		*/	
		this->_option.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_option.setPosition(this->_playButton.getPosition().x , this->_playButton.getPosition().y + 100);
		this->_options.setFont(this->_data->assets.GetFont("Felt"));
		this->_options.setPosition(this->_option.getPosition().x + 60 , this->_option.getPosition().y + 5);
		this->_options.setString("THEMES");

		/*
			For exit button
		*/
		this->_exit_btn.setTexture(this->_data->assets.GetTexture("Play Button"));
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
				this->_playButton.setScale(1.25,1.25);
			}
			else{
				this->_playButton.setScale(1,1);
			}
			if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new PlayOptionState(_data)),true);
			}
			if(this->_option.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->_option.setScale(1.25,1.25);
			}
			else{
				this->_option.setScale(1,1);
			}
			if (this->_data->input.IsSpriteClicked(this->_option, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new Options(_data)),false);
			}
			if(this->_exit_btn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->_exit_btn.setScale(1.25,1.25);
			}
			else{
				this->_exit_btn.setScale(1,1);
			}
			if (this->_data->input.IsSpriteClicked(this->_exit_btn, sf::Mouse::Left, this->_data->window))
			{
				this->_data->window.close();
			}
		}
	}

	void MainMenuState::boolIsdefaultTheme(){
		std::fstream fileForRead("data.ini");
		int tempString = 1;
		if(fileForRead.is_open()){
			fileForRead >> tempString ;
		}
		fileForRead.close();
		if(tempString == 0 ){
			this->_data->isdefaultTheme = false;
		}
		else{
			this->_data->isdefaultTheme = true;
		}
	}

	void MainMenuState::Update(float dt)
	{
		
	}
	void MainMenuState::Draw(float dt)
	{
		if(this->_data->isdefaultTheme){
			this->_data->window.clear(sf::Color(this->_data->themeDefault->getMainMenuR(),this->_data->themeDefault->getMainMenuG(),this->_data->themeDefault->getMainMenuB()));
		}else{
			this->_data->window.clear(sf::Color(this->_data->themeNew->getMainMenuR(),this->_data->themeNew->getMainMenuG(),this->_data->themeNew->getMainMenuB()));
		}
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_playButtonOuter);
		this->_data->window.draw(this->_play);
		this->_data->window.draw(this->_option);
		this->_data->window.draw(this->_options);
		this->_data->window.draw(this->_exit_btn);
		this->_data->window.draw(this->_exit);
		this->_data->window.display();
	}
}
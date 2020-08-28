#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
namespace GameEngine{
	class MainMenuState : public State{
		GameDataRef _data;
		sf::Sprite x;
		sf::Sprite o;
		sf::Text _play;
		sf::Text _options;
		sf::Text _exit;
		sf::Sprite _background;
		sf::Sprite _playButton;
		sf::Sprite _playButtonOuter;
		sf::Sprite _title;
		sf::Sprite _option;
		sf::Sprite _exit_btn;
	public:
		MainMenuState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}
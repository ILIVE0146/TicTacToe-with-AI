#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
namespace GameEngine{
	class PlayOptionState : public State{
	public:
		PlayOptionState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;
        sf::Sprite pvpButton;
        sf::Text pvpText;
        sf::Sprite unbeatable_mode;
        sf::Text unbeatable_mode_text;
        sf::Sprite easyAI;
        sf::Text easyAI_text;
		sf::Text tytle;
		sf::Sprite back_button;
		sf::Text back_TXT;
	};
}
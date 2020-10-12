#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

#include "unbeatableAi.hpp"

namespace GameEngine
{
	class unbeatable : public State
	{
	public:
		unbeatable(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);


		void InitGridPieces();

		void CheckAndPlacePiece();

		void CheckHasPlayerWon(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
	private:
		GameDataRef _data;

		sf::Sprite _pauseButton;

		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[3][3];
		sf::Sprite _homeButton;
		sf::Sprite _retryButton;
		int _gridArray[3][3];

		int turn;
		int gameState;
		int temp;
		thinker *ai;
		sf::Clock _clock;

		sf::Text turnText;
	};
}
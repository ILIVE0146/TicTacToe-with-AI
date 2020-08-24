

#include <sstream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace GameEngine
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{
		gamestate = State_playing;
		turn = Player_piece;

		this->Ai = new ai(turn, this->_data);

		this->_data->assets.LoadTexture("Pause Button", Pause_btn);
		this->_data->assets.LoadTexture("Grid Sprite", Grid_sprite_filePath);
		this->_data->assets.LoadTexture("X Piece", X_piece);
		this->_data->assets.LoadTexture("O Piece", O_piece);
		this->_data->assets.LoadTexture("X Winning Piece", X_PATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_PATH);

		this->_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		this->gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		this->_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		this->gridSprite.setPosition((SCREEN_WIDTH / 2) - (this->gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->gridSprite.getGlobalBounds().height / 2));
	
		InitGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridArray[x][y] = Empty_piece_number;
			}
		}
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

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				// Switch To Game State
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.IsSpriteClicked(this->gridSprite, sf::Mouse::Left, this->_data->window))
			{
				if (State_playing == gamestate)
				{
					checkAndPlacePiece();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(142,237,210));

		this->_data->window.draw( this->_pauseButton );

		this->_data->window.draw( this->gridSprite );

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(this->gridPieces[x][y]);
			}
		}

		this->_data->window.display();
	}

	void GameState::InitGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				gridPieces[x][y].setPosition(gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::checkAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		//std::cout << gridLocalTouchPos.x << ", " << gridLocalTouchPos.y << std::endl;

		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column, row;

		// Check which column the user has clicked
		if (gridLocalTouchPos.x < gridSectionSize.x) // First Column
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2) // Second Column
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width) // Third Column
		{
			column = 3;
		}

		// Check which row the user has clicked
		if (gridLocalTouchPos.y < gridSectionSize.y) // First Row
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2) // Second Row
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height) // Third Row
		{
			row = 3;
		}

		if (gridArray[column - 1][row - 1] == Empty_piece_number)
		{
			gridArray[column - 1][row - 1] = turn;

			if (Player_piece == turn)
			{
				gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));

				this->checkPlayerHasWon(turn);
			}

			gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::checkPlayerHasWon(int player)
	{
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		if (State_won != gamestate)
		{
			gamestate = State_AI_playing;

			Ai->placePiece(&gridArray, gridPieces, &gamestate);

			Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_piece);
			Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_piece);
			Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_piece);
			Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_piece);
			Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_piece);
			Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_piece);
			Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_piece);
			Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_piece);
		}

		int emptyNum = 9;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (Empty_piece_number != gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}

		// check if the game is a draw
		if (0 == emptyNum && (State_won != gamestate) && (State_lose != gamestate))
		{
			gamestate = State_Draw;
		}

		// check if the game is over
		if (State_Draw == gamestate || State_lose == gamestate || State_won == gamestate)
		{
			// show game over
		}

		std::cout << gamestate << std::endl;
	}

	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3])
		{
			std::string winningPieceStr;

			if (O_piece_number == pieceToCheck)
			{
				winningPieceStr = "O Winning Piece";
			}
			else
			{
				winningPieceStr = "X Winning Piece";
			}

			gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));


			if (Player_piece == pieceToCheck)
			{
				gamestate = State_won;
			}
			else
			{
				gamestate = State_lose;
			}
		}
	}
}
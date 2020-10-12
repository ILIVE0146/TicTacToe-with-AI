

#include <sstream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"


namespace GameEngine
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;
		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
		this->turnText.setFont(this->_data->assets.GetFont("Felt"));
		this->turnText.setScale(2.5,2.5);
		
		
		
		
		
		
		this->ai = new AI(turn, this->_data);


		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));
	
		InitGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridArray[x][y] = Empty_piece_number;
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
			if(gameState == STATE_PLAYING)
			{
				if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
				{
					// Switch To Game State
					this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
				}
				else if (this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
				{
					if (STATE_PLAYING == gameState)
					{
						this->CheckAndPlacePiece();
					}
				}	
			}else if(gameState != STATE_PLAYING && gameState != state_delay){
				if(this->_data->input.IsSpriteClicked(this->_homeButton,sf::Mouse::Left,this->_data->window)){
						this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
					}
					else if(this->_data->input.IsSpriteClicked(this->_retryButton,sf::Mouse::Left,this->_data->window)){
						this->_data->machine.AddState(StateRef(new GameState(_data)),true);
					}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if(gameState == state_delay){
			
			if(_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER){
				gameState = temp;
			}
			
		}
		if(gameState != state_delay && gameState != STATE_PLAYING){
			this->turnText.setPosition(225, 90);
			if(gameState == State_won){
				this->turnText.setString("YOU WON");
				this->turnText.setPosition(175,90);
			}
			else if(gameState == State_lose ){
				this->turnText.setString("YOU LOST");
				this->turnText.setPosition(175,90);
			}else{
				this->turnText.setString("DRAW");
			}
			
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(250,181,127));
		if(gameState != STATE_PLAYING && gameState != state_delay){
			this->_data->window.draw(this->_retryButton);
			this->_data->window.draw(this->_homeButton);
			this->_data->window.draw(this->turnText);
		}
		else if(gameState == STATE_PLAYING || gameState == state_delay){

			this->_data->window.draw( this->_pauseButton );

			this->_data->window.draw( this->_gridSprite );

			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
				{
					this->_data->window.draw(this->_gridPieces[x][y]);
				}
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
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::CheckAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
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

		if (_gridArray[column - 1][row - 1] == Empty_piece_number)
		{
			_gridArray[column - 1][row - 1] = turn;

			if (PLAYER_PIECE == turn)
			{
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));

				this->CheckHasPlayerWon(turn);
			}

			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::CheckHasPlayerWon(int player)
	{
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		if (State_won != gameState)
		{
			gameState = State_AI_playing;

			ai->PlacePiece(&_gridArray, &_gridPieces, &gameState);

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
				if (Empty_piece_number != _gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}

		// check if the game is a draw
		if (0 == emptyNum && (State_won != gameState) && (State_lose != gameState))
		{
			gameState = state_delay;
			temp=State_Draw;
		}

		// check if the game is over
		if (gameState == state_delay)
		{
			// show game over
			this->_clock.restart( );
		}

	}

	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == _gridArray[x1][y1] && pieceToCheck == _gridArray[x2][y2] && pieceToCheck == _gridArray[x3][y3])
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

			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));


			if(PLAYER_PIECE == pieceToCheck){
				gameState = state_delay;
				this->temp = State_won;
			}else{
				gameState = state_delay;
				this->temp = State_lose;
			}
		}
	}
}
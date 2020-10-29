#include <sstream>
#include "pvp.hpp"
#include "DEFINITIONS.hpp"

#include "pauseState.hpp"
#include "MainMenuState.hpp"
namespace GameEngine{
	pvp::pvp(GameDataRef data) : _data(data){ }
	void pvp::Init(){
		
		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));

		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
		/*
			For loading data
		*/
        gamestate = STATE_PLAYING;
        turn = PLAYER_PIECE;
		this->turnText.setFont(this->_data->assets.GetFont("Felt"));
		this->turnText.setString("'s turn");
		this->turnText.setScale(2.5,2.5);
        this->_data->assets.LoadTexture("Pause Button",PAUSE_BUTTON);
        _pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
        _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width,_pauseButton.getPosition().y);
		gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));
		gridSprite.setPosition((SCREEN_WIDTH/2) - (gridSprite.getGlobalBounds().width/2),(SCREEN_HEIGHT/2) - (gridSprite.getGlobalBounds().height/2));
		this->showCurrentPlayer.setScale(0.5,0.5);
		InitGridPieces();
		for(int x = 0; x< 3; x++){
			for(int y=0; y<3;y++){
				gridArray[x][y] = Empty_piece_number;
			}
		}
	}
	void pvp::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            
			if(gamestate != STATE_PLAYING){
					if(this->_data->input.IsSpriteClicked(this->_homeButton,sf::Mouse::Left,this->_data->window)){
						this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
					}
					else if(this->_data->input.IsSpriteClicked(this->_retryButton,sf::Mouse::Left,this->_data->window)){
						this->_data->machine.AddState(StateRef(new pvp(_data)),true);
					}
			}else{
				if(this->_data->input.IsSpriteClicked(this->_pauseButton,sf::Mouse::Left,this->_data->window)){
                	this->_data->machine.AddState(StateRef(new PauseState(_data)),false);
            	}
				else if(this->_data->input.IsSpriteClicked(this->gridSprite,sf::Mouse::Left,this->_data->window)){
					if(STATE_PLAYING == gamestate)
					{
						this->checkAndPlacePiece();
					}
				}
			}
		}
	}
	void pvp::checkAndPlacePiece(){
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = gridSprite.getGlobalBounds();
		sf::Vector2f gapOutSideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width)/2,(SCREEN_HEIGHT - gridSize.height) / 2 );
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutSideOfGrid.x,touchPoint.y - gapOutSideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width/3,gridSize.height/3);
		int column , row;
		if(gridLocalTouchPos.x < gridSectionSize.x){
			column = 1;
		}else if(gridLocalTouchPos.x < gridSectionSize.x * 2){
			column = 2;
		}else if(gridLocalTouchPos.x < gridSize.width){
			column = 3;
		}
		if(gridLocalTouchPos.y < gridSectionSize.y){
			row = 1;
		}else if(gridLocalTouchPos.y < gridSectionSize.y * 2){
			row = 2;
		}else if(gridLocalTouchPos.y < gridSize.height ){
			row = 3;
		}
		if( gridArray[column - 1][row -1] == Empty_piece_number){
			gridArray[column - 1][row - 1] = turn;
			if(PLAYER_PIECE == turn){
				gridPieces[column -1][row-1].setTexture(this->_data->assets.GetTexture("X Piece"));
				this->checkPlayerHasWon(turn);
				turn = AI_piece;
			}else if(AI_piece == turn){
				gridPieces[column -1][row-1].setTexture(this->_data->assets.GetTexture("O Piece"));
				this->checkPlayerHasWon(turn);
				turn = PLAYER_PIECE;	
			}
			gridPieces[column - 1][row-1].setColor(sf::Color(255,255,255,255));
		}
	}
	void pvp::Update(float dt)
	{
		if(gamestate == state_delay){
			
			if(timer.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER){
				gamestate = temp;
			}
			
		}
		if(gamestate == STATE_PLAYING){
			if(turn == PLAYER_PIECE){
				this->showCurrentPlayer.setTexture(this->_data->assets.GetTexture("X Piece"));
				this->showCurrentPlayer.setPosition(25,800);
				this->turnText.setPosition(this->showCurrentPlayer.getPosition().x + 75 ,this->showCurrentPlayer.getPosition().y - 10);
			}else{
				this->showCurrentPlayer.setTexture(this->_data->assets.GetTexture("O Piece"));
				this->showCurrentPlayer.setPosition(300,800);
				this->turnText.setPosition(this->showCurrentPlayer.getPosition().x + 75 ,this->showCurrentPlayer.getPosition().y - 10);
			}
		}else if(gamestate == state_delay){
			if(temp == State_won){
				this->showCurrentPlayer.setTexture(this->_data->assets.GetTexture("X Piece"));
			}else if(temp == State_lose){
				this->showCurrentPlayer.setTexture(this->_data->assets.GetTexture("O Piece"));
			}else{
				this->showCurrentPlayer.setColor(sf::Color(0,0,0,0));
			}
			if(temp != State_Draw){
				this->turnText.setString(" - WON");
			}else{
				this->turnText.setString("DRAW");
			}
			this->showCurrentPlayer.setPosition(150,100);
			this->turnText.setPosition(this->showCurrentPlayer.getPosition().x + 75, this->showCurrentPlayer.getPosition().y - 10);
		}
	}
	void pvp::Draw(float dt)
	{
		if(gamestate != STATE_PLAYING && gamestate != state_delay)
		{
			if(gamestate == State_won){
				if(this->_data->isdefaultTheme){
					this->_data->window.clear(sf::Color(this->_data->themeDefault->getXR(),this->_data->themeDefault->getXG(),this->_data->themeDefault->getXB()));
				}else{
					this->_data->window.clear(sf::Color(this->_data->themeNew->getXR(),this->_data->themeNew->getXG(),this->_data->themeNew->getXB()));
				}
			}
			else if(gamestate == State_lose)
			{
				if(this->_data->isdefaultTheme){
					this->_data->window.clear(sf::Color(this->_data->themeDefault->getOR(),this->_data->themeDefault->getOG(),this->_data->themeDefault->getOB()));
				}else{
					this->_data->window.clear(sf::Color(this->_data->themeNew->getOR(),this->_data->themeNew->getOG(),this->_data->themeNew->getOB()));
				}
			}
			else{
				this->_data->window.clear(sf::Color( 33, 176, 164));
			}
			this->_data->window.draw(this->_retryButton);
			this->_data->window.draw(this->_homeButton);
		}else{
			if(turn == PLAYER_PIECE)
			{
				if(this->_data->isdefaultTheme){
					this->_data->window.clear(sf::Color(this->_data->themeDefault->getXR(),this->_data->themeDefault->getXG(),this->_data->themeDefault->getXB()));
				}else{
					this->_data->window.clear(sf::Color(this->_data->themeNew->getXR(),this->_data->themeNew->getXG(),this->_data->themeNew->getXB()));
				}
			}
			else{
				if(this->_data->isdefaultTheme){
					this->_data->window.clear(sf::Color(this->_data->themeDefault->getOR(),this->_data->themeDefault->getOG(),this->_data->themeDefault->getOB()));
				}else{
					this->_data->window.clear(sf::Color(this->_data->themeNew->getOR(),this->_data->themeNew->getOG(),this->_data->themeNew->getOB()));
				}
			}
			this->_data->window.draw(this->_pauseButton);
        	this->_data->window.draw(this->gridSprite);
			for(int x =0;x<3;x++){
				for(int y=0;y<3;y++){
					this->_data->window.draw(this->gridPieces[x][y]);
				}
			}
		}
		this->_data->window.draw(this->showCurrentPlayer);
		this->_data->window.draw(this->turnText);
		
		this->_data->window.display();
	}
	void pvp::InitGridPieces(){
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();
		for(int x =0;x<3;x++){
			for(int y=0;y<3;y++){
				gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				gridPieces[x][y].setPosition(gridSprite.getPosition().x+(tempSpriteSize.x * x)-7,gridSprite.getPosition().y+(tempSpriteSize.y * y) - 7);
				gridPieces[x][y].setColor(sf::Color(255,255,255,0));
			}
		}
	}
	void pvp::checkPlayerHasWon(int player){
		Check3PiecesForMatch(0,0,1,0,2,0,player);
		Check3PiecesForMatch(0,1,1,1,2,1,player);
		Check3PiecesForMatch(0,2,1,2,2,2,player);
		Check3PiecesForMatch(0,0,0,1,0,2,player);
		Check3PiecesForMatch(1,0,1,1,1,2,player);
		Check3PiecesForMatch(2,0,2,1,2,2,player);
		Check3PiecesForMatch(0,0,1,1,2,2,player);
		Check3PiecesForMatch(0,2,1,1,2,0,player);
		int emptyNum = 9;
		for(int x = 0 ; x<3 ; x++){
			for(int y=0;y<3;y++){
				if(Empty_piece_number != gridArray[x][y]){
					emptyNum--;
				}
			}
		}
		if((0 == emptyNum) && (state_delay != gamestate)){
			gamestate = state_delay;
			this->temp = State_Draw;
		}
		if (gamestate == state_delay)
		{
			// show game over
			this->timer.restart( );
		}
	}
	void pvp::Check3PiecesForMatch(int x1, int y1 , int x2, int y2 ,int x3, int y3 ,int pieceToCheck){
		if( pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]){
			std::string winningPieceStr;
			if( O_piece_number == pieceToCheck){
				winningPieceStr = "O Win";
			}else{
				winningPieceStr = "X Win";
			}
			gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			if(PLAYER_PIECE == pieceToCheck){
				gamestate = state_delay;
				this->temp = State_won;
			}else{
				gamestate = state_delay;
				this->temp = State_lose;
			}
		}
	}
}
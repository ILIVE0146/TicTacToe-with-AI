#include "unbeatableAi.hpp"
#include "DEFINITIONS.hpp"
#include <algorithm>
#include <iostream>
namespace GameEngine{
    thinker::thinker(int playerPiece,GameDataRef data){
        std::cout<<"till here 2";
        this->_data = data;
        if (O_piece_number == playerPiece)
		{
			this->maxPlayer = X_piece_number;
            this->minPlayer = playerPiece;

		}
		else
		{
			this->maxPlayer = O_piece_number;
            this->minPlayer = playerPiece;
		}
    }
    void thinker::checkForOptimalSolutionToPlace(int(*gridArray)[3][3], sf::Sprite (*gridPieces)[3][3] , int *gameState){
        
        int board[3][3];
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                
                board[i][j] = (*gridArray)[i][j];
            }
        }
        int bestVal = -1000;
        int row = 0;
        int col = 0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == Empty_piece_number){
                    board[i][j] = maxPlayer;
                    int moveVal = minMax(board,0,false);
                    board[i][j] = Empty_piece_number;
                    if(moveVal > bestVal){
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        //here now best move is row,col
        (*gridArray)[row][col] = AI_piece;
        (*gridPieces)[row][col].setTexture(this->_data->assets.GetTexture("O Piece"));
        (*gridPieces)[row][col].setColor(sf::Color(255, 255, 255, 255));
        *gameState = STATE_PLAYING;
    }
    int thinker::minMax(int board[3][3], int depth, bool isMax){
        int score = evaluate(board);
        if(score == 10){
            return score;
        }
        if(score == -10){
            return score;
        }
        if(isMovesLeft(board) == false){
            return 0;
        }
        if(isMax){
            int best = -1000;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(board[i][j] == Empty_piece_number){
                        board[i][j] = maxPlayer;
                        best = std::max(best,minMax(board,depth+1,!isMax));
                    }
                    board[i][j] = Empty_piece_number;
                }
            }
            return best;
        }
        else{
            int best = 1000;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(board[i][j] == Empty_piece_number){
                        board[i][j] = minPlayer;
                        best = std::min(best, minMax(board, depth+1, !isMax));
                        board[i][j] = Empty_piece_number;
                    }
                }
            }
            return best;
        }
    }
    int thinker::evaluate(int b[3][3]){
        for(int row=0;row<3;row++)
        {
            if((b[row][0] == b[row][1]) && (b[row][1] == b[row][2]))
            {
                if(b[row][0] == maxPlayer)
                {
                    return +10;
                }else if(b[row][0] == minPlayer)
                {
                    return -10;
                }
            }
        }
        for(int col = 0; col<3 ; col++){
            if(b[0][col] == b[1][col] && b[1][col] == b[2][col]){
                if (b[0][col] == maxPlayer){
                    return +10;
                }else if(b[0][col] == minPlayer){
                    return -10;
                }
            }
        }
        if(b[0][0] == b[1][1] && b[1][1] == b[2][2]){
            if (b[0][0] == maxPlayer)
            {
                return +10;
            }
            else if (b[0][0] == minPlayer){
                {
                    return -10;
                }
            }
        }
        if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
        {
            if (b[0][2] == maxPlayer){
                return +10;
            }
            else if (b[0][2] == minPlayer){
                return -10;
            }
        }
        return 0;
    }
    bool thinker::isMovesLeft(int board[3][3]){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == Empty_piece_number){
                    return true;
                }
            }
        }
        return false;
    }
}
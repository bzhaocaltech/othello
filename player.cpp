#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     
    board = Board();
    this->side = side;
    
    if (side == BLACK)
    {
        opponentSide = WHITE;
    }
    else
    {
        opponentSide = BLACK;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // Update board
    if (opponentsMove != NULL)
    {
        board.doMove(opponentsMove, opponentSide);
    }
    
    // Find valid moves
    Move** valids = validMove();
    
    // Choose first move
    Move* move = valids[0];
    
    // Free valids
    for (int i = 0; i < 64; i++)
    {
       //delete(valids + i);
    }
    
    // If the move was a valid move, update board and return it
    if (move->x >= 0)
    {
        board.doMove(move, side);
        return move;
    }
    // Otherwise return NULL (there are no valid moves)
    return NULL;
}

/**
 * @brief Returns the set of valid moves that can be made on the board
 * 
 * @return The size of the set of valid moves will be sixty-four in size
 * The last move is followed by an invalid move (-1, -1).
 */
Move **Player::validMove(){
	
	Move ** valid_moves = new Move*[64];
	int counter = 0;
	
	//Adds valid moves to array valid_moves
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Move* newMove = new Move(i, j);
			if (board.checkMove(newMove, side))
			{
				valid_moves[counter] = newMove;
				counter++;
			}
			else
			{
				//Move is not valid. Move is thus not needed and is
				// deleted.
				//delete(newMove);
			}
		}
	}
	valid_moves[counter] = new Move(-1, -1);
	
    return valid_moves;
}

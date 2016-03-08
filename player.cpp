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
    
    opponentSide = (side == BLACK) ? WHITE : BLACK;
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
    Move** valids = board.validMove(side);
    
    int highest_score = -9999; 
    int counter = 0;
    Move *best_move = valids[0];
    
    while (valids[counter]->x != -1)
    {
		if(highest_score < board.score(valids[counter], side))
		{
			highest_score = board.score(valids[counter], side);
			best_move = valids[counter];
		}
		counter++;
	}
    
    // Free valids
    int i = 0;
    while (valids[i] != NULL)
    {
        if(valids[i] != best_move)
        {
            delete(valids[i]);
        }
        i++;
    }
    
    // If the move was a valid move, update board and return it
    if (best_move->x >= 0)
    {
        board.doMove(best_move, side);
        return best_move;
    }
    // Otherwise return NULL (there are no valid moves)
    return NULL;
}

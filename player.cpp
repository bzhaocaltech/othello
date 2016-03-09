#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     
    board = new Board();
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
        board->doMove(opponentsMove, opponentSide);
    }
    
    // Create the head node (represents the current board)
    Node* head = new Node(board, side);
    // Create children node for the head node (represent each possible
    // move we have)
    head->makeChildren(side, side);
    // For each of the children node, have it analyze all moves opponent 
    // can make
    for (int i = 0 ; i < head->numOfChildren; i++)
    {
		head->children[i]->makeChildren(opponentSide, side);
		head->children[i]->worstChild();
	}
	int score = -9999;
	Move* move = NULL;
	// Find the child node with the best score. Make move that child's
	// move
	for (int i = 0 ; i < head->numOfChildren; i++)
	{
		if (head->children[i]->score > score)
		{
			score = head->children[i]->score;
			move = head->children[i]->move;
		}
	}
	
	if (move != NULL)
	{
		board->doMove(move, side);
		return move;
	}
	
	return NULL;
}

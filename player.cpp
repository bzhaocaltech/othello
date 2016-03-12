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
    return NULL;
}

// Creates a new node object.
Node::Node(Board* board, Side side)
{
	// Set up the board
    this->board = board;
    score = board->score(side);
    
    move = NULL;
    this->side = side;
    this->nextSide = side;
    
    // Set up children
    children = new Node*[32];
    numOfChildren = 0;
}

// Makes a new node. The board stored in this new node is the board
// passed to it after a given move has been preformed.
Node::Node(Board* board, Move* move, Side moveSide, Side scoreSide)
{
	// Update board and score it
    this->board = board->newBoardMove(move, moveSide);
    score = (this->board)->score(scoreSide);
    
    // Update sides
    this->side = scoreSide;
    // The side that did not move this time, moves next time
    this->nextSide = (moveSide == BLACK) ? WHITE : BLACK;
    
    this->move = move;
    
    // Set up children
    children = new Node*[32];
    numOfChildren = 0;
}

// Destructor for a single node.
Node::~Node()
{
    delete(board);
    delete(move);
}

// Alternative destructor. Deletes all child nodes in addition to the
// current node.
void Node::deleteAll()
{
    for (int i = 0 ; i < numOfChildren; i++)
	{
		children[i]->deleteAll();
	}
    delete(this);
}

// Makes the children of this node to a certain depth
void Node::makeChildren(int depth)
{
    if (depth != 0)
    {
        Move** valids = board->validMove(nextSide);
        int counter = 0;
    
        // Create a new child node for each valid move
        while (valids[counter] != NULL)
        {
            children[counter] = new Node(board, valids[counter], nextSide , side);
        
            // Recursively get each of the child nodes to create there own children
            children[counter]->makeChildren(depth - 1);
        
            // Update counter to continue iterating through the loop
            counter++;
        }
    }
}

// Returns the score of this node
int Node::getScore()
{
	return score;
}

// Replaces the score of this node with the score of its worst child 
// (or grandchild)
void Node::worstChild()
{
    if (numOfChildren > 0)
    {
        int worstScore = 9999;
        // Call worst child on each of the children nodes
        for (int i = 0 ; i < numOfChildren; i++)
        {
            children[i]->worstChild();
            
            // Simultaneously look for the worst score
            if (children[i]->getScore() < worstScore)
            {
                worstScore = children[i]->getScore();
            }
        }
        // Finally, update this node's score to the worst score
        score = worstScore;
    }
}

// Returns the index of the best possible move from minmaxing
int Node::bestMove()
{
    int bestScore = -9999;
    int index = -1;
    for (int i = 0; i < numOfChildren; i++)
    {
        if (bestScore < children[i]->getScore())
        {
            bestScore = children[i]->getScore();
            index = i;
        }
    }
    return index;
}

// Extends the current tree by an additional level
void Node::extend()
{
    // If there are no children for this node, extend it
    if (numOfChildren == 0)
    {
        makeChildren(1);
    }
    // If you are not at the bottom of the tree, keep going until you
    // are
    else
    {
        for (int i = 0; i < numOfChildren; i++)
        {
            children[i]->extend();
        }
    }
}

// Returns the move of this node
Move* Node::getMove()
{
    return move;
}

// (Use this version of advance only when player is about to move)
// Finds the node that contains the best move. Then deletes all other
// branches of the tree and returns that node (which becomes the new head)
Node* Node::advance()
{
    int index = bestMove();
    for (int i = 0; i < numOfChildren; i++)
    {
        // Delete all other branches
        if (i != index)
        {
            children[i]->deleteAll();
        }
    }
    // Extend the current tree by one
    this->extend();
    return(children[index]);
}

// (Use this version of advance only when opponent is about to move)
// Advances the tree base on which move the opponent made
Node* Node::advance(Move* opponentsMove)
{
    int done = 0;
    int counter = 0;
    while(!done)
    {
        Move* move = children[counter]->getMove();
        // Found the move. Counter now contains the index of the nextChild
        if (move->x == opponentsMove->x && move->y == opponentsMove->y)
        {
            done = 1;
        }
        counter++;
    }
    
    for (int i = 0; i < numOfChildren; i++)
    {
        // Delete all other branches
        if (i != counter)
        {
            children[i]->deleteAll();
        }
    }
    // Extend the current tree by one
    this->extend();
    return(children[counter]);
}

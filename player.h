#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

private:
    Board board;
    Side side;
    Side opponentSide;
public:
    Player(Side side);
    ~Player();    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

class Node { 
public:
    Node** children;
    int numOfChildren;
    int score;
    Board* board;
    Move* move;
    // Makes a new node.
    Node(Board* board, Side side)
    {
        this->board = board;
        score = board->score(side);
        move = NULL;
        children = new Node*[64];
        numOfChildren = 0;
    }
    // Makes a new node. The board stored in this new node is the board
    // passed to it after a given move has been preformed.
    Node(Board* board, Move* move, Side side)
    {
        this->board = board->newBoardMove(move, side);
        score = (this->board)->score(side);
        this->move = move;
        numOfChildren = 0;
    }
    ~Node()
    {
        delete(board);
        delete(move);
    }
    // Makes the children of this node. Side here represents the side
    // that was not used to create this node
    void makeChildren(Side side)
    {
        // Find valid moves
        Move** valids = board->validMove(side);
        int counter = 0;
        // Create a new node for each valid move
        while (valids[counter]->x != -1)
        {
            children[numOfChildren] = new Node(board, valids[counter], side);
            numOfChildren++;
            counter++;
        }
    }
    // Returns the score of the worst child.
    int worstChild()
    {
        int worstChildScore = children[0]->score;
        for (int i = 1; i < numOfChildren; i++)
        {
            if (children[i]->score <= worstChildScore)
            {
                worstChildScore = children[i]->score;
            }
        }
        return worstChildScore;
    }
};

#endif

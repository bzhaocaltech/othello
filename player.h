#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

private:
    Board* board;
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
    Node(Board* board, Move* move, Side moveSide, Side scoreSide)
    {
        this->board = board->newBoardMove(move, moveSide);
        score = (this->board)->score(scoreSide);
        this->move = move;
        children = new Node*[64];
        numOfChildren = 0;
    }
    ~Node()
    {
        delete(board);
        delete(move);
    }
    // Makes the children of this node.
    void makeChildren(Side moveSide, Side scoreSide)
    {
        // Find valid moves
        Move** valids = board->validMove(moveSide);
        int counter = 0;
        // Create a new node for each valid move
        while (valids[counter]->x != -1)
        {
            children[numOfChildren] = new Node(board, valids[counter], moveSide, scoreSide);
            numOfChildren++;
            counter++;
        }
    }
    // Replaces the score of this node with the score of its worst child
    void worstChild()
    {
        if (numOfChildren == 0)
        {
            // Do nothing
        }
        else
        {
            int worstChildScore = -999;
            for (int i = 0; i < numOfChildren; i++)
            {
                if (children[i]->score <= worstChildScore)
                {
                    worstChildScore = children[i]->score;
                }
            }
            score = worstChildScore;
        }
    }
};

#endif

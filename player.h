#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Node { 
private:
    // The score of the board in this node
    int score;
    
    // The side from which score is calculated from
    Side side;
    // The side that should move next
    Side nextSide;

    // The board that this node represents
    Board* board;
    // The move that was made to get to this board
    Move* move;
public:
    
    // Contains all the children of the node
    Node** children;
    
    // The number of nodes contained in children
    int numOfChildren;
    
    Node(Board* board, Side side, Side moveSide);
    Node(Board* board, Move* move, Side moveSide, Side scoreSide);
    ~Node();
    void deleteAll();
    void makeChildren(int depth);
    void worstChild();
    int getScore();
    Move* getMove();
    int bestMove();
    Node* advance();
    Node* advance(Move* opponentsMove);
    void extend();
};

class Player {

private:
    Side side;
    Side opponentSide;
    Node* head;
public:
    Player(Side side);
    ~Player();    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};



#endif

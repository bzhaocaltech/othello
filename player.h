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
    Node(Board* board, Side side);
    Node(Board* board, Move* move, Side moveSide, Side scoreSide);
    ~Node();
    void makeChildren(Side moveSide, Side scoreSide);
    void worstChild();
};

#endif

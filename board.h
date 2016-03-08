#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;

#define CORNER  3
#define ADJCORNER   0.5
#define EDGE    2

class Board {
   
private:
    bitset<64> black;
    bitset<64> taken;    
       
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
      
public:
    Board();
    ~Board();
    Board *copy();
    int score();
    Move** validMove(Side side);
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();

    void setBoard(char data[]);
};

#endif

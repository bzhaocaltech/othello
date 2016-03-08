#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;

#define CORNER      4
#define ADJCORNER   0.5
#define DIACORNER   0.25
#define EDGE        2
#define isEdge(x, y)        true
#define isCorner(x, y)      true
#define isAdjCorner(x, y)   true 
#define isDiaCorner(x, y)   true

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
    int score(Move* move, Side side);
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

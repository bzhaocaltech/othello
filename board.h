#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;

#define CORNER      1
#define ADJCORNER   1
#define DIACORNER   1
#define EDGE        1
#define isEdge(x, y)        (x == 0 || y == 0 || x == 7 || y == 7)
#define isCorner(x, y)      ((x == 0 && (y == 0 || y == 7)) || \
                            (x == 7 && (y == 0 || y == 7)))
#define isAdjCorner(x, y)   ((x == 1 && (y == 0 || y == 7)) || \
                            (x == 0 && (y == 1 || y == 6)) || \
                            (x == 6 && (y == 0 || y == 7)) || \
                            (x == 7 && (y == 1 || y == 6)))
#define isDiaCorner(x, y)   ((x == 1 && (y == 1 || y == 6)) || \
                            (x == 6 && (y == 1 || y == 6)))

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
    Board* newBoardMove(Move* move, Side side);
    int score(Move* move, Side side);
    int score(Side side);
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

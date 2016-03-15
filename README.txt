Benjamin Zhao created the node class and the methods contained within it.
The node class encapsulates each board for the minmax tree.  Additionally,
he wrote the doMove() methods and several minor methods in the board class.

Ishan Mazumdar updated several methods to improve heuristics. Among these
methods are the score() method and the worstChild() method of the node
subclass. Ishan also helped with debugging the code.

We continually changed the heuristic numbers such as the values of corner/edge
squares and the importance of mobility until we had a relatively high
win rate against ConstantTimePlayer and would (on occasion) beat BetterPlayer.
We made our tree to a depth of four, which was the highest depth we
could make our tree without it running out of availble memory.

#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

class Scaffold;

const int VACANT = -1;
const int RED = 0;
const int BLACK = 1;
const int TIE_GAME = -1;
const int SEARCH_DEPTH = 9; // set the limit of recursive depth for bestMove

// Checks for N in a row on Scaffold s
// If a player has won or the game is tied, winner is set to RED, BLACK, or TIE_GAME and returns true
// If the game is not completed, winner is unchanged and returns false
bool isCompleted(const Scaffold& s, int N, int& winner);

#endif // SUPPORT_INCLUDED

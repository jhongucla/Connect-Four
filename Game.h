#ifndef Game_h
#define Game_h

#include "support.h"
#include "Player.h"
#include "Scaffold.h"

class Game
{
public:
    Game(int nColumns, int nLevels, int N, Player* red, Player* black);
    ~Game();
    bool completed(int& winner) const;
    bool takeTurn();
    bool play();
    int checkerAt(int c, int r) const;
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
private:
    Scaffold* m_scaffold; // pointer to the game's scaffold
    Player* m_red; // pointer to the red player
    Player* m_black; // pointer to the black player
    Player* m_currPlayer; // pointer to the player whose turn it is
    int m_nColumns;
    int m_nLevels;
    int m_n;
    int m_winner; // set to the winner if the game is won
};

#endif /* Game_h */

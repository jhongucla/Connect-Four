// Game.cpp

#include "Game.h"
#include "Player.h"
#include "Scaffold.h"
#include "support.h"
#include <iostream>
using namespace std;

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
: m_red(red), m_black(black), m_currPlayer(m_red), m_nColumns(nColumns), m_nLevels(nLevels), m_n(N), m_winner(-2)
{
    m_scaffold = new Scaffold(nColumns, nLevels); // dynamically allocate a new scaffold
}

Game::~Game()
{
    delete m_scaffold; // delete the scaffold when the game ends
}

bool Game::completed(int& winner) const
{
    return isCompleted(*m_scaffold, m_n, winner); // calls helper function isCompleted
}

bool Game::takeTurn()
{
    if (completed(m_winner)) // don't take a turn if the game is won
        return false;
    int currColor = (m_currPlayer == m_red) ? RED : BLACK; // initialize the current player's color
    cout << endl;
    m_scaffold->display();
    if (m_currPlayer->isInteractive()) // prompt a human player for a move
        cout << endl << m_currPlayer->name() << ", ";
    int columnToMove = m_currPlayer->chooseMove(*m_scaffold, m_n, currColor);
    m_scaffold->makeMove(columnToMove, currColor);
    cout << endl << m_currPlayer->name() << " has moved." << endl;
    m_currPlayer = (m_currPlayer == m_red) ? m_black : m_red; // set current player to the other player
    return true;
}

bool Game::play()
{
    while (takeTurn()) {} // keep taking turns until the game is won or tied
    cout << endl;
    m_scaffold->display();
    if (m_winner == RED)
        cout << endl << m_red->name() << " has won!" << endl;
    else if (m_winner == BLACK)
        cout << endl << m_black->name() << " has won!" << endl;
    else
        cout << endl << "Tie Game!" << endl;
    if (m_winner == RED)
        return false;
    return true;
}

int Game::checkerAt(int c, int r) const
{
    return m_scaffold->checkerAt(c, r);
}

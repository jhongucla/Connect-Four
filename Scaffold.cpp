// Scaffold.cpp

#include "support.h"
#include "Scaffold.h"
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

Scaffold::Scaffold(int nColumns, int nLevels)
: m_nColumns(nColumns), m_nLevels(nLevels)
{
    if (nColumns <= 0 || nLevels <= 0) // check that columns and levels are positive
    {
        cerr << "Columns and levels need to be positive." << endl;
        exit(1);
    }
    m_scaffold.resize(m_nLevels);
    for (int i = 0; i < m_nLevels; i++)
        m_scaffold[i].resize(m_nColumns);
    for (int i = 0; i < m_nLevels; i++) // make every position on the scaffold vacant
        for (int j = 0; j < m_nColumns; j++)
            m_scaffold[i][j] = VACANT;
}

Scaffold::~Scaffold() {}

Scaffold::Scaffold(const Scaffold& other)
{
    m_nColumns = other.m_nColumns;
    m_nLevels = other.m_nLevels;
    m_scaffold = other.m_scaffold;
    m_history = other.m_history;
}

Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_nColumns, temp.m_nColumns);
        swap(m_nLevels, temp.m_nLevels);
        swap(m_scaffold, temp.m_scaffold);
        swap(m_history, temp.m_history);
    }
    return *this;
}

int Scaffold::cols() const
{
    return m_nColumns;
}

int Scaffold::levels() const
{
    return m_nLevels;
}

int Scaffold::numberEmpty() const
{
    return (int)(m_nColumns*m_nLevels-m_history.size()); // total number of positions minus number of checkers on scaffold
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_scaffold[level-1][column-1];
}

void Scaffold::display() const
{
    for (int i = m_nLevels-1; i >= 0; i--)
    {
        cout << '|';
        for (int j = 0; j < m_nColumns; j++)
        {
            char checker;
            switch(m_scaffold[i][j]) // display the correct character depending on value in scaffold
            {
                case RED:
                    checker = 'X';
                    break;
                case BLACK:
                    checker = 'O';
                    break;
                default:
                    checker = ' ';
            }
            cout << checker << '|';
        }
        cout << endl;
    }
    cout << '+';
    for (int k = 0; k < m_nColumns; k++)
        cout << '-' << '+';
    cout << endl;
}

bool Scaffold::makeMove(int column, int color)
{
    if (column < 1 || column > m_nColumns || (color != RED && color != BLACK))
        return false;
    for (int i = 0; i < m_nLevels; i++)
    {
        if (m_scaffold[i][column-1] == VACANT) // find the first empty spot in a column
        {
            m_scaffold[i][column-1] = color;
            m_history.push(column); // record the move in the history member
            return true;
        }
    }
    return false;
}

int Scaffold::undoMove()
{
    if (m_history.empty()) // if there is no history, then the scaffold is empty
        return 0;
    int lastCol = m_history.top();
    m_history.pop();
    for (int i = m_nLevels-1; i >= 0; i--)
    {
        if (m_scaffold[i][lastCol-1] != VACANT) // find the highest level in the column that has a checker 
        {
            m_scaffold[i][lastCol-1] = VACANT;
            break;
        }
    }
    return lastCol;
}

int Scaffold::lastMove() const
{
    if (m_history.empty())
        return -1;
    return m_history.top();
}

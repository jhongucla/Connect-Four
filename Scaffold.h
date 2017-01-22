#ifndef Scaffold_h
#define Scaffold_h

#include "support.h"
#include <vector>
#include <stack>
using namespace std;

class Scaffold
{
public:
    Scaffold(int nColumns, int nLevels);
    ~Scaffold();
    Scaffold(const Scaffold& other);
    Scaffold& operator=(const Scaffold& rhs);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    int lastMove() const;
private:
    int m_nColumns;
    int m_nLevels;
    vector<vector<int>> m_scaffold;
    stack<int> m_history; // store a history of moves on the scaffold
};

#endif /* Scaffold_h */

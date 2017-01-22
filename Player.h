#ifndef Player_h
#define Player_h

#include "support.h"
#include "Scaffold.h"
#include <vector>
#include <string>

// Used to store the two values that bestMove returns, as well as provide functions to access the values
class Result
{
public:
    Result(int rating, int moveCol) : m_rating(rating), m_moveCol(moveCol) {}
    int rating() const { return m_rating; } // return the rating for a move
    int moveCol() const { return m_moveCol; } // return the column on which a move is made
private:
    int m_rating;
    int m_moveCol;
};

class Player
{
public:
    Player(std::string nm) : m_name(nm) {}
    virtual ~Player() {}
    std::string name() const { return m_name; };
    virtual bool isInteractive() const { return false; }
    virtual int chooseMove(const Scaffold& s, int N, int color) = 0;
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;
private:
    std::string m_name;
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string nm);
    virtual ~HumanPlayer();
    virtual bool isInteractive() const { return true; }
    virtual int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string nm);
    virtual ~SmartPlayer();
    virtual int chooseMove(const Scaffold& s, int N, int color);
private:
    Result bestMove(Scaffold& toRate, int N, int color, int computerColor, int currDepth, const vector<int>& cols);
    int rateScaffold(Scaffold& s, int N, int computerColor, int currDepth, bool& completed);
};

#endif /* Player_h */

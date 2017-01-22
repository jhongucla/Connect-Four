// Player.cpp

#include "Scaffold.h"
#include "support.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

HumanPlayer::HumanPlayer(string nm)
: Player(nm) {}

HumanPlayer::~HumanPlayer() {}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    (void)N;
    if (s.numberEmpty() == 0) // if the scaffold is full, then can't make a move
        return -1;
    int colToMove = -1;
    cout << "choose a column to move on: ";
    cin >> colToMove;
    Scaffold checkMove = s; // create a copy of the scaffold to check the move on
    while (colToMove < 1 || colToMove > s.cols() || !checkMove.makeMove(colToMove, color))
    {
        cout << endl << "Please choose a valid column: "; // if the column chosen is invalid, reprompt for another column
        cin >> colToMove;
    }
    return colToMove;
}

SmartPlayer::SmartPlayer(string nm)
: Player(nm) {}

SmartPlayer::~SmartPlayer() {}

// bestMove finds the best move for the computer or the opponent depending on the color and computerColor parameters passed in
// It returns a Result that consists of the rating for the best move and the column on which the move is made
Result SmartPlayer::bestMove(Scaffold& toRate, int N, int color, int computerColor, int currDepth, const vector<int>& cols)
{
    int otherColor = (color == RED) ? BLACK : RED; // intialize otherColor to the other player's color
    vector<Result> results; // create a vector to store the rating and column for each move
    size_t cols_size = cols.size();
    for (size_t i = 0; i < cols_size; i++)
    {
        if (toRate.makeMove(cols[i], color)) // check each move that can be made
        {
            bool completed;
            int rating = rateScaffold(toRate, N, computerColor, currDepth, completed); // rate the scaffold
            if (completed) // if the game is completed, insert the rating and column into results
                results.push_back(Result(rating, cols[i]));
            else if (currDepth+1 < SEARCH_DEPTH) // if recursive depth is less than the limit, call bestMove for the other player
                results.push_back(Result(bestMove(toRate, N, otherColor, computerColor, currDepth+1, cols).rating(), cols[i]));
            else // if recursive depth is at limit, assume any uncompleted game is a tie and insert rating and column into results
            {
                results.push_back(Result(0, cols[i]));
                toRate.undoMove();
                break;
            }
            toRate.undoMove(); // undo the move made
        }
    }
    size_t indexOfResult = 0;
    size_t results_size = results.size();
    if (color == computerColor) // if determining best move for computer, find the result with the most positive rating
    {
        for (size_t i = 0; i < results_size; i++)
            if (results[i].rating() > results[indexOfResult].rating())
                indexOfResult = i;
    }
    else // if determining best move for the other player, find the result with the most negative rating
    {
        for (size_t i = 0; i < results_size; i++)
            if (results[i].rating() < results[indexOfResult].rating())
                indexOfResult = i;
    }
    return results[indexOfResult];
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0) // if the scaffold is full, then can't make a move
        return -1;
    Scaffold findMove = s; // make a copy of the scaffold so it can be modified
    int scols = findMove.cols();
    vector<int> cols; // create a vector to store the order in which columns are to be checked by bestMove
    for (int i = 0; i <= scols/2; i++) // fill the vector with columns numbers starting from the middle to the sides
    {
        cols.push_back(scols/2+1-i);
        if (i > 0 && scols/2+1+i <= scols)
            cols.push_back(scols/2+1+i);
    }
    return bestMove(findMove, N, color, color, 0, cols).moveCol(); // returns the column that bestMove chooses
}

// Gives a rating for each scaffold that has a game that has been won or a tie game
// Returns a rating that depends on the current recursive depth and sets completed depending on whether a game is completed
int SmartPlayer::rateScaffold(Scaffold& s, int N, int computerColor, int currDepth, bool& completed)
{
    int winner;
    if (isCompleted(s, N, winner)) // calls isCompleted to check if a game is completed
    {
        completed = true;
        if (winner == TIE_GAME)
            return 0;
        else if (winner == computerColor)
            return 1000 - currDepth; // returns a positive number minus recursive depth if winner is the computer
        else
            return -1000 + currDepth; // returns a negative number plus the recurve depth if other player is the winner
    }
    completed = false; // if the game is not completed
    return 0; // returns an arbitary value that isn't checked
}

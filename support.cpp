#include "support.h"
#include "Scaffold.h"

bool isCompleted(const Scaffold& s, int N, int& winner)
{
    int lastCol = s.lastMove();
    if (lastCol == -1)
        return false;
    int lastLevel = 0;
    int levels = s.levels();
    int cols = s.cols();
    for (int i = levels; i > 0; i--) // checks which level the last move is on
    {
        if (s.checkerAt(lastCol, i) != VACANT)
        {
            lastLevel = i;
            break;
        }
    }
    int curr = s.checkerAt(lastCol, lastLevel);
    if (lastLevel >= N) // checks for a vertical win
    {
        bool vertWon = true;
        for (int k = 1; k < N; k++)
        {
            if (curr != s.checkerAt(lastCol, lastLevel-k))
            {
                vertWon = false; // if any position in the row is not the same as the first
                break;
            }
        }
        if (vertWon) // if there are N in a row in any direction, the game is won
        {
            winner = curr;
            return true;
        }
    }
    int leftShift = (lastCol-1) > (N-1) ? N-1 : lastCol-1;
    int rightShift = (cols-lastCol) > (N-1) ? N-1 : cols-lastCol;
    int downShift = (lastLevel-1) > (N-1) ? N-1 : lastLevel-1;
    int upShift = (levels-lastLevel) > (N-1) ? N-1: levels-lastLevel;
    for (int i = 0; i <= leftShift; i++) // checks for a horizontal win
    {
        int checked = s.checkerAt(lastCol-leftShift+i, lastLevel);
        if (checked == curr && lastCol-leftShift+i+N-1 <= cols)
        {
            bool horzWon = true;
            for (int k = 1; k < N; k++)
            {
                if (checked != s.checkerAt(lastCol-leftShift+i+k, lastLevel))
                {
                    horzWon = false;
                    break;
                }
            }
            if (horzWon)
            {
                winner = curr;
                return true;
            }
        }
    }
    int leftDiagDown = leftShift > downShift ? downShift : leftShift;
    int rightDiagUp = rightShift > upShift ? upShift : rightShift;
    for (int i = 0; i <= leftDiagDown; i++) // checks for a diagonal win
    {
        int checked = s.checkerAt(lastCol-leftDiagDown+i, lastLevel-leftDiagDown+i);
        if (checked == curr && -leftDiagDown+i+N-1 <= rightDiagUp)
        {
            bool leftDiagWon = true;
            for (int k = 1; k < N; k++)
            {
                if (checked != s.checkerAt(lastCol-leftDiagDown+i+k, lastLevel-leftDiagDown+i+k))
                {
                    leftDiagWon = false;
                    break;
                }
            }
            if (leftDiagWon)
            {
                winner = curr;
                return true;
            }
        }
    }
    int rightDiagDown = rightShift > downShift ? downShift : rightShift;
    int leftDiagUp = leftShift > upShift ? upShift : leftShift;
    for (int i = 0; i <= rightDiagDown; i++) // checks for a diagonal win
    {
        int checked = s.checkerAt(lastCol+rightDiagDown-i, lastLevel-rightDiagDown+i);
        if (checked == curr && -rightDiagDown+i+N-1 <= leftDiagUp)
        {
            bool rightDiagWon = true;
            for (int k = 1; k < N; k++)
            {
                if (checked != s.checkerAt(lastCol+rightDiagDown-i-k, lastLevel-rightDiagDown+i+k))
                {
                    rightDiagWon = false;
                    break;
                }
            }
            if (rightDiagWon)
            {
                winner = curr;
                return true;
            }
        }
    }
    if (s.numberEmpty() == 0) // if there aren't N in a row in any direction and the scaffold is full, then game is a tie
    {
        winner = TIE_GAME;
        return true;
    }
    return false; // if the game isn't a tie then it's not completed
}

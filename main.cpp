#if defined(_MSC_VER)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

#include "support.h"
#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    cout << "Please enter your name: ";
    getline(cin, name);
    HumanPlayer hp(name);
    SmartPlayer sp("Computer");
    Game g(7, 6, 4, &hp, &sp);
    g.play();
}

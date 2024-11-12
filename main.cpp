#include "Header.hpp"
int main()
{
	system("mode con lines=35 cols=100");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	vector<Pocemon> pockemons = read_and_init(6);

	fight(pockemons);

// a lot of getch if you like push buttoms
	_getch();
	_getch();
	_getch();
	_getch();
	_getch();
	return 0;
}
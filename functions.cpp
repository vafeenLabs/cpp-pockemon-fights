#include "Header.hpp"
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void Pocemon::read_pocemon(ifstream &filer)
{
	string garbage;
	short index;
	filer >> garbage; // name
	filer >> id;
	filer >> name_of_pocemon;
	filer >> index;
	type = type_of_pocemon(index);
	filer >> index;
	pockemon_energy = index;
	filer >> garbage; // attacks
	for2(i, 0, 3)
	{
		type_of_attack attack;
		filer >> attack.name;
		filer >> attack.damage;
		filer >> attack.energy;
		attacks.push_back(attack);
	}
	filer >> garbage; // weaknesses
	for (short i = 0; i < 2; i++)
	{
		filer >> index;
		weaknesses.push_back(type_of_pocemon(index));
	}
	filer >> garbage;
	filer >> char_of_pocemon.lives;
	filer >> garbage;
	filer >> char_of_pocemon.speed;
	filer >> garbage;
	filer >> char_of_pocemon.regen;
}
vector<Pocemon> read_and_init(const short &number)
{
	vector<Pocemon> pockemons;
	ifstream filer;
	filer.open("pockemons.txt");
	for (short i = 0; i < number; i++)
	{
		Pocemon yarik;
		yarik.attacker = STAY;
		yarik.read_pocemon(filer);
		pockemons.push_back(yarik);
	}
	filer.close();
	return pockemons;
}
int Pocemon::number_attack()
{
	cout << "\nУдар " << name_of_pocemon << "'a\n";

	for (short i = 0; i < attacks.size(); i++)
	{
		string x = "";
		for (short j = 0; j < 25 - attacks[i].name.size(); j++)
			x += ' ';
		cout << "\n"
			 << i + 1 << " attack - " << attacks[i].name << x << "damage = " << attacks[i].damage << "\tenegry = " << attacks[i].energy;
	}
	int number;

	while (true)
	{
		number = mygetch("\nenter the attack\n->", 1, attacks.size()) - 1;
		if (pockemon_energy >= attacks[number].energy)
		{
			break;
		}
		else
		{
			cout << "Не хватает энергии! Нужно выбрать другую аттаку!\n";
		}
	}
	return number;
}

void choose_pockemon(vector<Pocemon> &pockemons, const fs &command, short &index, bool fighter, const short &round)
{
	vector<short> keys = {};

	if (command == FIRST)
	{
		for (short i = 0; i < 3; i++)
			if (pockemons[i].char_of_pocemon.lives > 0)
				keys.push_back(i + 1);
		index = mygetch("\nВыберите покемона!\nClick-> ", keys) - 1;
	}
	else if (command == SECOND)
	{
		for (short i = 3; i < 6; i++)
			if (pockemons[i].char_of_pocemon.lives > 0)
				keys.push_back(i - 2);
		index = mygetch("\nВыберите покемона!\nClick-> ", keys) + 2;
	}

	if (fighter)
		pockemons[index].attacker = ATTACK;
	else
		pockemons[index].attacker = BLOCK;
}
void restart(vector<Pocemon> &pockemons)
{
	for (short i = 0; i < pockemons.size(); i++)
	{
		pockemons[i].attacker = STAY;
		pockemons[i].pockemon_energy += pockemons[i].char_of_pocemon.regen;
	}
}
void continue_play(vector<Pocemon> &pockemons, bool &play)
{
	bool command1 = false, command2 = false;
	short lose;
	for (short i = 0; i < 3; i++)
		if (pockemons[i].char_of_pocemon.lives > 0)
			command1 = true;

	for (short i = 3; i < 6; i++)
		if (pockemons[i].char_of_pocemon.lives > 0)
			command2 = true;
	if (!command1)
		lose = 1;
	if (!command2)
		lose = 2;
	if (!(command1 && command2))
	{
		play = false;
		cout << "Игра окончена!\nКоманда " << lose << " проиграла!";
	}
}
void fight(vector<Pocemon> &pockemons)
{
	short round = 1;
	short fight, block;
	fs fir = FIRST, sec = SECOND;
	bool play = true;

	while (play)
	{
		print_pockemons(pockemons);
		choose_pockemon(pockemons, fir, fight, true, round);
		print_pockemons(pockemons);
		choose_pockemon(pockemons, sec, block, false, round);
		print_pockemons(pockemons);
		swap(fir, sec);
		one_attack(pockemons, fight, block);
		round += 1;
		restart(pockemons);
		continue_play(pockemons, play);
	}
}

void one_attack(vector<Pocemon> &pockemons, const short &fight, const short &block)
{
	short number_of_attack = pockemons[fight].number_attack();
	short boost = 1;
	if (find_weakness(pockemons[block], pockemons[fight]))
	{
		boost *= 2;
	}
	if (pockemons[fight].attacks[number_of_attack].damage * boost > pockemons[block].protect)
	{
		pockemons[block].char_of_pocemon.lives = pockemons[block].char_of_pocemon.lives - pockemons[fight].attacks[number_of_attack].damage * boost + pockemons[block].protect;
	}
	if (pockemons[block].char_of_pocemon.lives < 0)
		pockemons[block].char_of_pocemon.lives = 0;
	system("cls");
	short damage = pockemons[fight].attacks[number_of_attack].damage * boost - pockemons[block].protect;
	if (damage < 0)
		damage = 0;
	cout << "Покемон " << pockemons[fight].name_of_pocemon << " наносит удар покемону " << pockemons[block].name_of_pocemon
		 << "\n damage = " << damage << "\n\n";
	pockemons[fight].pockemon_energy -= pockemons[fight].attacks[number_of_attack].energy;
	pockemons[block].pockemon_energy += pockemons[block].char_of_pocemon.regen;
}

bool find_weakness(const Pocemon &whose, const Pocemon &who)
{
	for (size_t i = 0; i < whose.weaknesses.size(); i++)
		if (who.type == whose.weaknesses[i])
			return true;
	return false;
}

short find_color(Pocemon pocemon)
{
	switch (pocemon.attacker)
	{
	case STAY:
		return WHITE;
	case ATTACK:
		return RED;
	case BLOCK:
		return GREEN;
	}
}

void print2pockemons(Pocemon pocemon1, Pocemon pocemon2)
{
	short color1 = find_color(pocemon1), color2 = find_color(pocemon2);
	if (pocemon1.char_of_pocemon.lives <= 0)
		color1 = BLACK;
	if (pocemon2.char_of_pocemon.lives <= 0)
		color2 = BLACK;
	SetConsoleTextAttribute(handle, color1);
	cout << '\n'
		 << pocemon1.name_of_pocemon << "\t\t\t\t";
	SetConsoleTextAttribute(handle, color2);
	cout << pocemon2.name_of_pocemon << " ";
	SetConsoleTextAttribute(handle, color1);
	cout << "\n[lives: " << pocemon1.char_of_pocemon.lives << "]\t\t\t";
	SetConsoleTextAttribute(handle, color2);
	cout << "[lives: " << pocemon2.char_of_pocemon.lives << "]";
	SetConsoleTextAttribute(handle, color1);
	cout << "\n[regen: " << pocemon1.char_of_pocemon.regen << "]\t\t\t";
	SetConsoleTextAttribute(handle, color2);
	cout << "[regen: " << pocemon2.char_of_pocemon.regen << "]";
	SetConsoleTextAttribute(handle, color1);
	cout << "\n[protect: " << pocemon1.protect << "]\t\t\t";
	SetConsoleTextAttribute(handle, color2);
	cout << "[protect: " << pocemon2.protect << "]";
	SetConsoleTextAttribute(handle, color1);
	cout << "\n[enegry: " << pocemon1.pockemon_energy << "]\t\t\t";
	SetConsoleTextAttribute(handle, color2);
	cout << "[enegry: " << pocemon2.pockemon_energy << "]\n";
	SetConsoleTextAttribute(handle, WHITE);
	/*cout << "[regen :%s]  |  [ regen: %s]\n" << pocemon1.char_of_pocemon.regen << pocemon2.char_of_pocemon.regen;
	cout << "[protect:%s]  |  [protect:%s]\n" << pocemon1.protect << pocemon2.protect;
	cout << "[energy:%s]  |  [energy: %s]\n" << pocemon1.pockemon_energy << pocemon2.pockemon_energy;*/
}

void print_pockemons(vector<Pocemon> pocemons)
{
	system("cls");
	short damage1 = 1, damage2 = 1;
	cout << "\nкоманда 1\t\t\t"
		 << "команда 2";
	short index = pocemons.size() / 2;
	for (short i = 0; i < index; i++)
	{
		print2pockemons(pocemons[i], pocemons[i + index]);
	}
	// find weaknesses
}

short mygetch(const string &message, short i1, short i2)
{
	cout << message;
	while (true)
	{
		char symbol = _getch();
		if (symbol == CTRL(c))
			exit(0);
		if (symbol == 0 || symbol == 224)
		{
			symbol = _getch();
			return char(256 + symbol);
		}
		short symbol1 = symbol - '0';
		if (i1 <= symbol1 && symbol1 <= i2)
		{
			cout << symbol1 << '\n';
			return symbol1;
		}
	}
}
short mygetch(const string &message, vector<short> keys)
{
	cout << message;
	while (true)
	{
		char symbol = _getch();
		if (symbol == CTRL(c))
			exit(0);
		if (symbol == 0 || symbol == 224)
		{
			symbol = _getch();
			return char(256 + symbol);
		}
		short symbol1 = symbol - '0';
		for (short i = 0; i < keys.size(); i++)
			if (keys[i] == symbol1)
			{
				return symbol1;
			}
	}
}
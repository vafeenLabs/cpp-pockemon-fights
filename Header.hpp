#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#define us using std::
#define for2(i, start, finish) for (int i = start; i < finish; i++)
const short KEY_0 = 48, KEY_1 = 49, KEY_2 = 50;
#define CTRL(x) (#x[0] - 'a' + 1)
us string;
us vector;
us cout;
us cin;
us ifstream;
us ofstream;
us to_string;
us swap;

#define CONSSIZE 100
#define BLUE FOREGROUND_BLUE
#define GREEN FOREGROUND_GREEN
#define GRAY FOREGROUND_INTENSITY
#define RED FOREGROUND_RED
#define WHITE 15
#define BLACK 0
enum type_of_attacker
{
	STAY,
	ATTACK,
	BLOCK
};
enum fs
{
	FIRST,
	SECOND
};

enum type_of_pocemon
{
	Normal,
	Insects,
	Poisonous,
	Herbal,
	Water,
	Fiery,
	Earthy,
	Combat,
	Stone,
	Magic,
	Electric,
	Psychic,
	Ghostly,
	Draconic,
	Ice,
	Flying,
	Dark,
	Steel
};
struct type_of_attack
{
	string name;
	int damage = 0;
	int energy = 0;
};
struct Character
{
	int lives = 0;
	int speed = 0;
	int regen = 0;
};
class Pocemon
{
public:
	type_of_attacker attacker;
	short id;
	string name_of_pocemon;
	type_of_pocemon type;
	Character char_of_pocemon;
	vector<type_of_attack> attacks;
	int pockemon_energy = 0;
	int protect = 5;
	vector<type_of_pocemon> weaknesses;
	void read_pocemon(ifstream &filer);
	int number_attack();
};
vector<Pocemon> read_and_init(const short &number);
void fight(vector<Pocemon> &pockemons);
void one_attack(vector<Pocemon> &pockemons, const short &fight, const short &block);
bool find_weakness(const Pocemon &whose, const Pocemon &who);
void print_pockemons(vector<Pocemon> pocemons);
short mygetch(const string &message, short i1, short i2);
void choose_pockemon(vector<Pocemon> &pockemons, const fs &command, short &index, bool fighter, const short &round);
void restart(vector<Pocemon> &pockemons);
void continue_play(vector<Pocemon> &pockemons, bool &play);
short mygetch(const string &message, vector<short> keys);
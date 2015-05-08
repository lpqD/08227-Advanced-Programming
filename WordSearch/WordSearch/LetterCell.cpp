#include "LetterCell.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

using namespace std;

char DiagUpLeft;
char DiagUpRight;
char DiagDownLeft;
char DiagDownRight;
char Up;
char Down;
char Left;
char Right;


LetterCell::LetterCell(char UL, char UR, char DL, char DR, char U, char D, char L, char R)
{
	cout << "LetterCell constructed." << endl;
	
}

LetterCell::~LetterCell()
{

}

void LetterCell::setCells(char UL, char UR, char DL, char DR, char U, char D, char L, char R)
{
	DiagUpLeft = UL;
	DiagUpRight = UR;
	DiagDownLeft = DL;
	DiagDownRight = DR;
	Up = U;
	Down = D;
	Left = L; 
	Right = R;
}


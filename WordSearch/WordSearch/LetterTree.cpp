#include "LetterTree.h"


LetterTree::LetterTree()
{
	char Character = 0;
	for (int i = 0; i < 26; i++)
	{
		LetterPointers[i] = 0;
	}
	isLast = false;

}


LetterTree::~LetterTree()
{

}

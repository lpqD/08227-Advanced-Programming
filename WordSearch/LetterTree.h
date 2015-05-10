#pragma once
class LetterTree
{
public:

	char Character;
	bool isLast = false;

	LetterTree* LetterPointers[26];

	LetterTree();
	~LetterTree();
};


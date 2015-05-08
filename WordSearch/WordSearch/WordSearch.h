#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class WordSearch
{
public:
	WordSearch();
	~WordSearch();

	bool ReadSimplePuzzle();
	bool ReadSimpleDictionary();
	bool ReadAdvancedPuzzle();
	bool ReadAdvancedDictionary();

	string ConvertCharToString(char);

	bool SolveSimplePuzzleWithSimpleDictionary();
	bool SolveSimplePuzzleWithAdvancedDictionary();
	bool SolveAdvancedPuzzleWithSimpleDictionary();
	bool SolveAdvancedPuzzleWithAdvancedDictionary();

	void WriteResults(string fileName);

private:
	LARGE_INTEGER start, end, frequency;
	const int NUMBER_OF_RUNS;
	const string PUZZLE_NAME;
	const string DICTIONARY_NAME;
};


#include "WordSearch.h"
#include "LetterCell.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
WordSearch::WordSearch() : NUMBER_OF_RUNS(1), PUZZLE_NAME("wordsearch_grid.txt"), DICTIONARY_NAME("dictionary.txt")
{

}
WordSearch::~WordSearch()
{

}

char grid[9][9];

string* DictList;
int DictLength;

bool WordSearch::ReadAdvancedPuzzle()//Will read the file of the Advanced puzzle into the data structure
{
	cout << endl << "ReadAdvancedPuzzle() has NOT been implemented" << endl;
	return true;
}

bool WordSearch::ReadSimplePuzzle()//reads the file of the simple puzzle into the grid
{
	//creates an array

	fstream inputFile;//creates the input filestream

	inputFile.open(PUZZLE_NAME);
	string input, results;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile >> input;
			results += input;
		}
	}

	for (int x = 0; x <= 8; x++)
	{
		for (int y = 0; y <= 8; y++)
		{
			char addition;
			addition = results.at(0);
			grid[x][y] = addition;
			cout << grid[x][y];
			if (results.length() >= 1)
			results.erase(0, 1);
		}
	}
	cout << endl; //<< "ReadSimplePuzzle() has NOT been implemented" << endl;
	return true;
}

bool WordSearch::ReadAdvancedDictionary()
{
	cout << endl << "ReadAdvancedDictionary() has NOT been implemented" << endl;
	return true;
}

bool WordSearch::ReadSimpleDictionary()
{
	fstream inputFile;//creates the input filestream

	inputFile.open(DICTIONARY_NAME);
	string input, results;
	int length = 0;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile >> input;
			results += ("\n" + input);
			length++;
		}
		results.erase(0, 1);
	}
	DictLength = length;
	DictList = new string[length];


	istringstream stream(results);
	string temp;
	for (int i = 0; i < length; i++)
	{
		std::getline(stream, temp);
		DictList[i] = temp;
		cout << DictList[i] << endl;
	}

	//cout << endl << "ReadSimpleDictionary() has NOT been implemented" << endl;

	return true;
}

string WordSearch::ConvertCharToString(char c)
{
	stringstream stream;
	string temp;
	char temp2 = grid[0][0];
	stream << temp2;
	stream >> temp;
	return temp;
}

bool WordSearch::SolveSimplePuzzleWithSimpleDictionary() 
{
	cout << endl << "SolveSimplePuzzleWithSimpleDictionary() IS BEING been implemented" << endl;
	double timeTakenInSeconds;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	for (int n = 0; n < NUMBER_OF_RUNS; ++n) 
	{
		string temp = "";
		string result = "";

		//begin with checking left to right on each row
		for (int x = 0; x <= 8; x++)
		{
			for (int y = 0; y <= 8; y++)
			{
			
				temp += grid[x][y];
			}
			cout << temp << endl;

			for (int i = 0; i < DictLength; i++)
			{
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
					cout << DictList[i] << "found at: " << found << endl;
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
					cout << DictList[i] << "found at: " << found << endl;
			}
			temp = "";
		}

		for (int y = 0; y <= 8; y++)
		{
			for (int x = 0; x <= 8; x++)
			{

				temp += grid[x][y];
			}
			cout << temp << endl;

			for (int i = 0; i < DictLength; i++)
			{
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
					cout << DictList[i] << "found at: " << found << endl;
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
					cout << DictList[i] << "found at: " << found << endl;
			}
			temp = "";
		}







		// Add your solving code here!
	}

	QueryPerformanceCounter(&end);
	timeTakenInSeconds = (end.QuadPart - start.QuadPart) / (double)(frequency.QuadPart*NUMBER_OF_RUNS);

	////////////////////////////////////////////////
	// This output should be to your results file //
	////////////////////////////////////////////////
	cout << fixed << setprecision(10) << "SolveSimplePuzzleWithSimpleDictionary() - " << timeTakenInSeconds << " seconds" << endl;
	return false;
}

bool WordSearch::SolveSimplePuzzleWithAdvancedDictionary() 
{
	cout << endl << "SolveSimplePuzzleWithAdvancedDictionary() has NOT been implemented" << endl;
	return false;
}

bool WordSearch::SolveAdvancedPuzzleWithSimpleDictionary() 
{
	cout << endl << "SolveAdvancedPuzzleWithSimpleDictionary() has NOT been implemented" << endl;
	return false;
}

bool WordSearch::SolveAdvancedPuzzleWithAdvancedDictionary() 
{
	cout << endl << "SolveAdvancedPuzzleWithAdvancedDictionary() has NOT been implemented" << endl;
	return false;
}

void WordSearch::WriteResults(string fileName) 
{
	cout << "WriteResults() has NOT been implemented" << endl;
}


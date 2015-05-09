#include "WordSearch.h"
#include "LetterCell.h"
#include "LetterTree.h"
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
LetterCell advancedGrid[9][9];
LetterTree rootTree;

string* DictList;
int DictLength;

bool WordSearch::ReadAdvancedPuzzle()//Will read the file of the Advanced puzzle into the data structure
{
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

			advancedGrid[x][y].Letter = addition;
			
			int i = 0;
			for (int deltaX = -1; deltaX <= 1; deltaX++)
			{
				
				for (int deltaY = -1; deltaY <= 1; deltaY++)
				{
					
					if (deltaX == 0 && deltaY == 0)
					{
						deltaY += 1;
					}
					cout << "X delta = " << deltaX << "    Y delta = " << deltaY << endl;

					if (x + deltaX >= 0 && y + deltaY >= 0 && x + deltaX < 9 && y + deltaY < 9)
					{
						int pointX = x + deltaX;
						int pointY = y + deltaY; 
						advancedGrid[x][y].Pointers[i] = &advancedGrid[pointX][pointY];
							
					}
					i++;
				}
			}
			if (results.length() >= 1)
				results.erase(0, 1);
		}
	}

	//cout << endl << "ReadAdvancedPuzzle() IS BEING been implemented" << endl;
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
	LetterTree* pointer;

	fstream inputFile;//creates the input filestream

	inputFile.open(DICTIONARY_NAME);
	string input;
	int length = 0;
	
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile >> input;
			int stringLength = input.length();
			pointer = &rootTree;
			for (int i = 0; i < stringLength; i++)
			{
				int index = input[i] - 'A';


				if (pointer->LetterPointers[index])
				{
					pointer = pointer->LetterPointers[index];
				}
				else
				{
					pointer->LetterPointers[index] = new LetterTree;
					pointer->LetterPointers[index]->Character = input[i];
					pointer = pointer->LetterPointers[index];
				}

				
			}
			pointer->isLast = true;
			length++;
		}
	}

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
#pragma region HorizontalSearch
		//begin with checking left to right on each row
		for (int x = 0; x <= 8; x++)
		{
			int y = 0;
			for (y; y <= 8; y++)
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
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
			}
			temp = "";
		}
#pragma endregion HorizontalSearch
#pragma region VerticalSearch
		for (int y = 0; y <= 8; y++)
		{//identical to checking rows, but with X and Y loops swapped to make for vertical checking
			int x = 0;
			for (x; x <= 8; x++)
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
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
			}
			temp = "";
		}
#pragma endregion VerticalSearch
#pragma region DiagonalSearch
		//diagonal loops!
		int offsetX = 8;
		int offsetY = 0;
		int condition = 0;
		for (int y = 8; y >= 0;)
		{
			int x = 8;
			y = 8 + offsetY;
			x = x - offsetX;
			
			for (x; x >= condition; x--)
			{
				temp += grid[y][x];
				y--;
			}
			if (y < 0)
			{
				offsetY = offsetY - 1;
				condition++;
			}
			else if (x < 0)
				offsetX = offsetX - 1;

			
			for (int i = 0; i < DictLength; i++)
			{
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
			}
			
			
			if (offsetX == 0)
			{
				y = 8;
			}
			if (offsetY == -9)
			{
				break;
			}
			temp = "";
		}
#pragma endregion 
#pragma region DiagonalSearch_OtherDirection
		 offsetX = 8;
		 offsetY = 0;
		 condition = 0;
		 temp = "";
		for (int y = 0; y <= 8;)
		{
			int x = 8;
			y = 0 + offsetY;
			x = x - offsetX;

			for (x; x >= condition; x--)
			{
				temp += grid[y][x];
				y++;
			}
			if (y > 8)
			{
				offsetY = offsetY + 1;
				condition++;
			}
			
			else if (x < 0)
				offsetX = offsetX - 1;


			for (int i = 0; i < DictLength; i++)
			{
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
					cout << endl << DictList[i] << "found at: " << x << ", " << y << endl << endl;
			}


			if (offsetX <= 0)
			{
				y = 0;
			}
			if (offsetY == 9)
			{
				break;
			}
			temp = "";
		}
#pragma endregion 
		temp = "";
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

string WordSearch::RecursiveAdvancedSearch(int x, int y, int deltaX, int deltaY, LetterTree* pointer, string word)
{
	if (x > 9 || x < 0 || y > 9 || y < 0)
	{
		return "";
	}

	char c = grid[x][y];

	if (pointer->LetterPointers[c - 'A'])
	{
		if (pointer->LetterPointers[c - 'A']->isLast)
		{
			return word + c;
		}
		
		return RecursiveAdvancedSearch(x + deltaX, y + deltaY, deltaX, deltaY, pointer->LetterPointers[c - 'A'], word + c);
	}
	return "";
}


bool WordSearch::SolveSimplePuzzleWithAdvancedDictionary() 
{

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			for (int deltaX = -1; deltaX <= 1; deltaX++)
			{
				for (int deltaY = -1; deltaY <= 1; deltaY++)
				{
					if (deltaX == 0 && deltaY == 0)
					{
						continue;
					}
					
					string word = RecursiveAdvancedSearch(x, y, deltaX, deltaY, &rootTree, "");
					if (word != "")
						cout << word << " found at " << x << ", " << y << endl;
				}
			}
		}
	}
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


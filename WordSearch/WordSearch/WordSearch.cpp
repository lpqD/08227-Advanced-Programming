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
WordSearch::WordSearch() : NUMBER_OF_RUNS(25), PUZZLE_NAME("wordsearch_grid.txt"), DICTIONARY_NAME("dictionary.txt")
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
int wordsFound = 0;

double timeTaken;
double timeTakenToRead;
int cellsVisited = 0;
int wordsVisited = 0;

bool WordSearch::ReadAdvancedPuzzle()//Will read the file of the Advanced puzzle into the data structure
{

	double timeTakenInSeconds;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

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
					//cout << "X delta = " << deltaX << "    Y delta = " << deltaY << endl;

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
	QueryPerformanceCounter(&end);
	timeTakenInSeconds = (end.QuadPart - start.QuadPart) / (double)(frequency.QuadPart*NUMBER_OF_RUNS);

	std::cout << fixed << setprecision(10) << "ReadAdvancedPuzzle() - " << timeTakenInSeconds << " seconds" << endl;
	timeTakenToRead = timeTakenInSeconds;
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
			//cout << grid[x][y];
			if (results.length() >= 1)
			results.erase(0, 1);
		}
	}
	std::cout << endl; //<< "ReadSimplePuzzle() has NOT been implemented" << endl;
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

	//cout << endl << "ReadAdvancedDictionary() has NOT been implemented" << endl;
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
		//cout << DictList[i] << endl;
	}

	//cout << endl << "ReadSimpleDictionary() has NOT been implemented" << endl;

	return true;
}


bool WordSearch::SolveSimplePuzzleWithSimpleDictionary() 
{
	//cout << endl << "SolveSimplePuzzleWithSimpleDictionary() IS BEING been implemented" << endl;
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
				cellsVisited++;
			}
			//cout << temp << endl;

			for (int i = 0; i < DictLength; i++)
			{
				wordsVisited++;
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << found << ", " << x << endl << endl;
					wordsFound++;
				}
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				//cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << 8-found << ", " << x << endl << endl;
					wordsFound++;
				}
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
				cellsVisited++;
			}
			//cout << temp << endl;

			for (int i = 0; i < DictLength; i++)
			{
				wordsVisited++;
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << found << ", " << y << endl << endl;
					wordsFound++;
				}
					
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				//cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << 8 - found << ", " << y << endl << endl;
					wordsFound++;
				}
					
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
				cellsVisited++;
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
				wordsVisited++;
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << 8 - found << ", " << 8 - found << endl << endl;
					wordsFound++;
				}
					
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << 8 - found << ", " << 8 - found << endl << endl;
					wordsFound++;
				}
					
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
				cellsVisited++;
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
				wordsVisited++;
				string wordToFind = DictList[i];
				temp.find(wordToFind);

				size_t found = temp.find(wordToFind);

				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << x << ", " << y << endl << endl;
					wordsFound++;
				}
				//then reverse and check right to left, then move to the next row
				reverse(temp.begin(), temp.end());
				//cout << temp << endl;

				temp.find(wordToFind);
				found = temp.find(wordToFind);
				if (found != string::npos)
				{
					std::cout << endl << DictList[i] << " found at: " << x << ", " << y << endl << endl;
					wordsFound++;
				}
					
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
	std::cout << fixed << setprecision(10) << "SolveSimplePuzzleWithSimpleDictionary() - " << timeTakenInSeconds << " seconds" << endl;
	timeTaken = timeTakenInSeconds;
	return true;
}

string WordSearch::RecursiveAdvancedSearch(int x, int y, int deltaX, int deltaY, LetterTree* pointer, string word)
{
	if (x >= 9 || x < 0 || y >= 9 || y < 0)
	{
		return "";
	}

	char c = grid[x][y];
	cellsVisited++;
	if (pointer->LetterPointers[c - 'A'])
	{
		wordsVisited++;
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
	double timeTakenInSeconds;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	for (int n = 0; n < NUMBER_OF_RUNS; ++n)
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
						cellsVisited++;
						string word = RecursiveAdvancedSearch(x, y, deltaX, deltaY, &rootTree, "");
						if (word != "")
						{
							std::cout << word << " found at " << y << ", " << x << endl << endl;

							wordsFound++;
						}
					}
				}
			}
		}
	}

	QueryPerformanceCounter(&end);
	timeTakenInSeconds = (end.QuadPart - start.QuadPart) / (double)(frequency.QuadPart*NUMBER_OF_RUNS);

	
	std::cout << fixed << setprecision(10) << "SolveSimplePuzzleWithAdvancedDictionary() - " << timeTakenInSeconds << " seconds" << endl;
	timeTaken = timeTakenInSeconds;
	return true;
}

void WordSearch::DictionarySearch(string temp, int x, int y)
{
	for (int i = 0; i < DictLength; i++)
	{
		wordsVisited++;
		string wordToFind = DictList[i];
		temp.find(wordToFind);

		size_t found = temp.find(wordToFind);

		if (found != string::npos)
		{
			std::cout << endl << DictList[i] << " found at: " << x << ", " << y << endl << endl;
			wordsFound++;
		}

		//then reverse and check right to left, then move to the next row
		reverse(temp.begin(), temp.end());
		//cout << temp << endl;

		temp.find(wordToFind);
		found = temp.find(wordToFind);
		if (found != string::npos)
		{
			std::cout << endl << DictList[i] << " found at: " << 8- found << ", " << x << endl << endl;
			wordsFound++;
		}

	}
	temp = "";
}

bool WordSearch::SolveAdvancedPuzzleWithSimpleDictionary() 
{
	//UNCOMPLETE
	double timeTakenInSeconds;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	for (int n = 0; n < NUMBER_OF_RUNS; ++n)
	{
		int x = 0;
		int y = 0;

		for (LetterCell* l = &advancedGrid[0][0]; l != nullptr; l=l->Pointers[LetterCell::EAST])
		{
			string d = "";
			for (LetterCell* k = l; k != nullptr; k = k->Pointers[LetterCell::SOUTHEAST])
			{
				d += k->Letter;
				cellsVisited++;
				y++;
				x++;
			}
			DictionarySearch(d, x, y);
			x++;
			y = 0;
		}
		x = 1;
		y = 0;
		for (LetterCell* l = &advancedGrid[1][0]; l != nullptr; l = l->Pointers[LetterCell::SOUTH])
		{
			string d = "";
			for (LetterCell* k = l; k != nullptr; k = k->Pointers[LetterCell::SOUTHEAST])
			{
				d += k->Letter;
				cellsVisited++;
				x++;
				y++;
			}
			DictionarySearch(d, x, y);
			y++;
			x = 0;
		}
		x = 0;
		y = 8;
		for (LetterCell* l = &advancedGrid[0][8]; l != nullptr; l = l->Pointers[LetterCell::SOUTH])
		{
			string d = "";
			for (LetterCell* k = l; k != nullptr; k = k->Pointers[LetterCell::SOUTHWEST])
			{
				d += k->Letter;
				cellsVisited++;
				x--;
				y++;
			}
			DictionarySearch(d, x, y);
			y++;
			x = 0;
		}
		x = 0;
		y = 7;
		for (LetterCell* l = &advancedGrid[0][7]; l != nullptr; l = l->Pointers[LetterCell::WEST])
		{
			string d = "";
			for (LetterCell* k = l; k != nullptr; k = k->Pointers[LetterCell::SOUTHWEST])
			{
				d += k->Letter; 
				cellsVisited++;
				x--;
				y++;
			}
			DictionarySearch(d, x, y);
			y = 0;
			x--;

		}
		x = 0;
		y = 0;
		for (LetterCell* l = &advancedGrid[0][0]; l != nullptr; l = l->Pointers[LetterCell::EAST])
		{
			string d = "";
			for (LetterCell* k = l; k != nullptr; k = k->Pointers[LetterCell::SOUTH])
			{
				d += k->Letter;
				cellsVisited++;
				y++;
			}
			DictionarySearch(d, x, y);
			x++;
			y = 0;
		}
		x = 0;
		y = 0;
		for (LetterCell* l = &advancedGrid[0][0]; l != nullptr; l = l->Pointers[LetterCell::SOUTH])
		{
			string d = "";
			for (LetterCell* k = l; k != nullptr; k = k->Pointers[LetterCell::EAST])
			{
				d += k->Letter;
				cellsVisited++;
				x++;
			}
			DictionarySearch(d, x, y);
			y++;
			x = 0;
		}
	
		
	}

	QueryPerformanceCounter(&end);
	timeTakenInSeconds = (end.QuadPart - start.QuadPart) / (double)(frequency.QuadPart*NUMBER_OF_RUNS);

	std::cout << fixed << setprecision(10) << "SolveAdvancedPuzzleWithSimpleDictionary() - " << timeTakenInSeconds << " seconds" << endl;
	timeTaken = timeTakenInSeconds;
	return true;
}

string WordSearch::RecursiveAdvancedAdvancedSearch(LetterCell* letter, LetterCell::DIRECTIONS d, LetterTree* pointer, string word)
{
	if (!letter)
	{
		return "";
	}
	
		char c = letter->Letter;
		cellsVisited++;

		if (pointer->LetterPointers[c - 'A'])
		{
			wordsVisited++;
			if (pointer->LetterPointers[c - 'A']->isLast)
			{
				return word + c;
			}

			return RecursiveAdvancedAdvancedSearch(letter->Pointers[d], d, pointer->LetterPointers[c - 'A'], word + c);
		}
	return "";
}

bool WordSearch::SolveAdvancedPuzzleWithAdvancedDictionary() 
{
	//UNCOMPLETE
	double timeTakenInSeconds;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	for (int n = 0; n < NUMBER_OF_RUNS; ++n)
	{
		//advancedGrid
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				for (int i = 0; i < 8; i++)
				{
					string word = RecursiveAdvancedAdvancedSearch(&advancedGrid[x][y], (LetterCell::DIRECTIONS)i, &rootTree, "");
					if (word != "")
					{
						std::cout << word << " found at " << y << ", " << x << endl << endl;
						wordsFound++;
					}
				}
			}
		}
	}

	QueryPerformanceCounter(&end);
	timeTakenInSeconds = (end.QuadPart - start.QuadPart) / (double)(frequency.QuadPart*NUMBER_OF_RUNS);




	std::cout << fixed << setprecision(10) << "SolveAdvancedPuzzleWithAdvancedDictionary() - " << timeTakenInSeconds << " seconds" << endl;
	timeTaken = timeTakenInSeconds;
	return true;
}

void WordSearch::WriteResults(string fileName) 
{
	ofstream myfile;
	myfile.open(fileName);
	myfile << "NUMBER_OF_WORDS_MATCHED " << wordsFound << endl << endl;
	wordsFound = 0;

	myfile << "WORDS_MATCHED_IN_GRID " << "placeholder" << endl << endl;

	myfile << "NUMBER_OF_GRID_CELLS_VISITED " << cellsVisited << endl << endl;
	cellsVisited = 0;
	myfile << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << wordsVisited << endl << endl;
	wordsVisited = 0;
	myfile << "TIME_TO_POPULATE_GRID_STRUCTURE " << timeTakenToRead << endl << endl;
	myfile << "TIME_TO_SOLVE_PUZZLE " << timeTaken << endl << endl;

	myfile.close();

	std::cout << "Writing to file: " << fileName << endl;
}


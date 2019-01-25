// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

#include "AVL.h"
#include "BinaryNode.h"

#pragma comment(linker, "/STACK:256000000") // 256 MB
#pragma comment(linker, "/HEAP:256000000") // 256 MB

using namespace std;

void displayMenu();
bool loadDictionary(string fileName, AVL* dict);
void spellCheckWord(AVL* dict);
void printWordsWithLetter(AVL* dict);

int main()
{
	AVL *dictionary = new AVL(); 
	
	if (!loadDictionary("data/RandomWords1000.txt", dictionary))
	{
		cout << "Error: Could not load dictionary!" << endl;
		return 1;
	}

	int option = 1;

	while (option != 0)
	{
		displayMenu();
		cout << "\nPlease enter an option : ";
		cin >> option;
		if (option == 1)
			spellCheckWord(dictionary);
		else if (option == 2)
		{

		}
		else if (option == 3)
			printWordsWithLetter(dictionary);
		else if (option == 4)
		{
		
		}	
		else if (option == 5)
		{
		
		}	
		else if (option == 0)
		{
			cout << "\nGoodbye!\n" << endl;
			return 0;
		}
		else
			cout << "\nSorry. You have entered an invalid option.\n"<< endl;
	}
	return 0;
}

void displayMenu()
{
	cout << "Welcome to Spell Checker!" << endl;
	cout << endl;
	cout << "[1] Spell check a word" << endl;
	cout << "[2] Spell check a file" << endl;
	cout << "[3] Add a new word to the dictionary" << endl;
	cout << "[4] Save the dictionary" << endl;
	cout << "[5] Display words that start with the letter..." << endl;
	cout << "[0] Exit " << endl;
}

bool loadDictionary(string fileName, AVL* dict)
{
	string line;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			dict->insert(line);
		myfile.close();
		return true;
	}
	else
		return false;
}

void spellCheckWord(AVL* dict) 
{
	cout << "\nEnter word to spell check : ";
	string word;
	cin >> word;
	if(dict->search(word) != NULL)
		cout << "The word is spelled correctly.\n" << endl;
	else
		cout << "The word is spelled wrongly.\n" << endl;
}

void printWordsWithLetter(AVL* dict)
{
	cout << "Please enter the first letter : ";
	char firstLetter;
	cin >> firstLetter;

	cout << "\nWords that start with the letter '" << firstLetter <<"'" << endl;

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Dominic Ng Jun Yao, S10177858H
//Kevin Toh Zheng Ying, S10179142B

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

#include "AVL.h"
#include "BinaryNode.h"
#include "Queue.h"

using namespace std;

#pragma comment(linker, "/STACK:256000000") // 256 MB
#pragma comment(linker, "/HEAP:256000000") // 256 MB

void displayMenu();
bool loadDictionary(string fileName);
bool spellCheckWord(string word);
void printWordsWithLetters(string prefix);
void convertToLower(string& word);
void removeSpecialChar(string &word);
void swap(char *x, char *y);
void permute(char *a, int l, int r);

AVL *dictionary = new AVL();
Queue wordsQueue;

int main()
{
	cout << "Loading Dictionary..." << endl;
	if (!loadDictionary("data/RandomWords3000plus.txt"))
	{
		cout << "Error: Could not load dictionary!" << endl;
		return 1;
	}
	system("CLS");

	int option = 1;

	while (option != 0)
	{
		displayMenu();
		cout << "\nPlease enter an option : ";
		cin >> option;
		if (option == 1)
		{
			cout << "\nEnter word to spell check : ";
			string word;
			cin >> word;
			convertToLower(word);
			removeSpecialChar(word);
			if (spellCheckWord(word))
				cout << "The word is spelled correctly.\n" << endl;
			else
				cout << "The word is spelled wrongly.\n" << endl;
		}
		else if (option == 2)
		{
			string fileName;
			string word;
			cout << "Please enter the name of a .txt or .csv file: ";
			cin >> fileName;
			ifstream myfile("data/" + fileName);
			if (myfile.is_open())
			{
				while (myfile >> word)
				{
					convertToLower(word);
					removeSpecialChar(word);
					if (!spellCheckWord(word))
						cout << word << " is spelled wrongly" << endl;
				}
				myfile.close();
			}
		}
		else if (option == 3)
		{
			string word;
			cout << "Please enter a word to add into the dictionary: ";
			cin >> word;
			convertToLower(word);
			removeSpecialChar(word);
			if (!spellCheckWord(word))
			{
				dictionary->insert(word);
				cout << "The word has been successfully added into the dictionary." << endl << endl;
			}
			else
				cout << "The word already exist in the dictionary." << endl << endl;
		}
		else if (option == 4)
		{
			ofstream dictionaryFile;
			dictionaryFile.open("data/dictionary10k.txt", ios::out | ios::trunc);
			dictionaryFile.close();
			dictionaryFile.open("data/dictionary10k.txt", ios::out | ios::app);

			if (!dictionaryFile.is_open()) {
				return false;
			}

			dictionary->saveFile(dictionaryFile);
			dictionaryFile.close();
			cout << "The dictionary has been saved." << endl << endl;
		}
		else if (option == 5)
		{
			cout << "\nPlease enter the prefix of the word : ";
			string prefix;
			cin >> prefix;
			convertToLower(prefix);
			removeSpecialChar(prefix);
			printWordsWithLetters(prefix);
		}
		else if (option == 6)
		{
			string front;
			string word;
			cout << "\nPlease enter a word: ";
			cin >> word;
			convertToLower(word);
			removeSpecialChar(word);
			if (spellCheckWord(word))
			{
				cout << "The word is spelled correctly.\n" << endl;
				continue;
			}

			//Transposition Error
			char charInWord[30];
			bool transpoError = false;
			strcpy_s(charInWord, word.c_str());
			permute(charInWord, 0, strlen(charInWord) - 1);
			while(!wordsQueue.isEmpty())
			{
				wordsQueue.getFront(front);
				wordsQueue.dequeue();
				if (spellCheckWord(front))
				{
					if (transpoError == false)
					{
						cout << "This word has a transposition error." << endl;
						transpoError = true;
					}
					cout << "Did you mean " << front << endl;
				}
			}
			if (transpoError == false)
				cout << "This word does not have a transposition error." << endl;


			//Substitution Error
			bool found = false;
			bool subError = false;
			dictionary->checkSubstitutionError(word, found, subError);
			if (!found && subError)
				cout << "The word has a substitution error." << endl << endl;
			else if (!found && !transpoError && !subError)
				cout << "The word is spelled wrongly." << endl << endl;
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
	cout << "[5] Display words that start with the letter(s)..." << endl;
	cout << "[6] Spell check a word with errors shown" << endl;
	cout << "[0] Exit " << endl;
}

bool loadDictionary(string fileName)
{
	string line;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line, '\n'))
			dictionary->insert(line);
		myfile.close();
		return true;
	}
	else
		return false;
}

bool spellCheckWord(string word)
{
	if (dictionary->search(word) != NULL)
		return true;
	return false;
}

/* This function will pass a prefix that consists of preceding letter(s) that may match
other words that start with the same letters to the AVL Tree function 'getWordsInOrder' in 
that finds words that start with the same letters as the prefix.
*/
void printWordsWithLetters(string prefix)
{
	bool found = false;
	cout << "\nWords that start with the letter(s) '" << prefix <<"'" << endl;
	dictionary->getWordsInOrder(prefix, found);
	if (!found)
		cout << "No words found." << endl;
	cout << endl;
}

void convertToLower(string &word)
{
	for (int i = 0; i < word.length(); i++)
		word[i] = tolower(word[i]);
}

void removeSpecialChar(string &word)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (!(word[i] >= 'a' && word[i] <= 'z'))
			word = word.substr(0, i) + word.substr(i+1, word.length());
	}
}

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// Function to print permutations of string
//This function takes three parameters:
void permute(char *word, int start, int end)
{
	int i;
	if (start == end)
		wordsQueue.enqueue(word);
	else
	{
		for (i = start; i <= end; i++)
		{
			swap((word + start), (word + i));
			permute(word, start + 1, end);
			swap((word + start), (word + i)); //backtrack 
		}
	}
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

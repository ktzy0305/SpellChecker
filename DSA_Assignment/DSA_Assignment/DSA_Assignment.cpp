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

bool loadDictionary(string fileName, AVL* dict);
void displayMenu();

int main()
{
	AVL *dictionary = new AVL(); 
	
	if (!loadDictionary("data/dictionary.txt", dictionary))
	{
		cout << "Error: Could not load dictionary!" << endl;
		return 1;
	}
	while (true)
	{
		displayMenu();
		cout << "Please enter an option : ";
		int option;
		cin >> option;
		cout << endl;
		switch (option)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			return 0;
		}

		return 0;
	}
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
		{
			//cout << line << endl;
			dict->insert(line);
		}
		myfile.close();
		return true;
	}
	else
		return false;
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

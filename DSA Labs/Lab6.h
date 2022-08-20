/*
File:			DSA_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student: Terry Ellison <ellisonterry4@gmail.com>

Created:		02.15.2021
Last Modified:	02.16.2021
Purpose:		Usage of the std::unordered_map class
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Main toggle
#define LAB_6	1

// Individual unit test toggles
#define LAB6_POPULATE_LETTER_VALUES	1
#define LAB6_GET_LETTER_VALUE		1
#define LAB6_GET_WORD_VALUE			1
#define LAB6_CREATE_PAIR			1
#define LAB6_LOAD_FILE				1
#define LAB6_FIND_WORD_SCORE		1

/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <unordered_map>

class DSA_Lab6 {

	friend class UnitTests_Lab6;	// Giving access to test code

	// Data members
	int mLetterValues[26];
	std::unordered_map<std::string, int> mScrabbleMap;

public:

	// In Scrabble, each letter has a value associated with it.
	// This method will populate the array of letter values.
	//
	// In:	_letterValues		The array of 26 values
	void PopulateLetterValues(const int* _letterValues) {
		for (size_t i = 0; i < 26; ++i)
		{
			mLetterValues[i] = _letterValues[i];
		}
	}

	// Retrieve the value of a particular letter
	// 
	// In:	_letter			The letter to get the score for
	//
	// Return:	The score value for the letter passed in
	// NOTE:	The letter passed in will always be upper-case
	int GetLetterValue(char _letter) const {
		int offset = (_letter - 65);
		int val = this->mLetterValues[offset];
		return val;
	}

	// Get the value of a word
	//		This is done by adding up the values of each letter in the word
	//
	// In:	_word		The word to get the value of
	//
	// Return: The total value of the word
	int GetWordValue(const std::string& _word) const {
		int sum = 0;
		size_t size = _word.length();
		const char* wordArr = _word.c_str();
		for (size_t i = 0; i < size; ++i)
		{
			sum += this->GetLetterValue(wordArr[i]);
		}
		return sum;
	}

	// Create a pair to add into the scrabbleMap
	//		This will have a "first" of the word, and a "second" of the total score
	//
	// In:	_word		The word for the pair
	//
	// Return: A pair that contains the word and the total score
	std::pair<std::string, int> CreatePair(const std::string& _word) const {
		return std::make_pair(_word, this->GetWordValue(_word));
	}

	// Load a file containing all of the possible scrabble words, along with their values
	//		This file will contain one word per line
	// In:	_filename	The name of the file to load
	//
	// Note: You may want to use one or more existing methods to help.
	void LoadWords(const char* _filename) {
		std::ifstream inputFile(_filename, std::ios::in);
		if (inputFile.is_open())
		{
			std::string line;

			while (std::getline(inputFile, line))
			{
				this->mScrabbleMap.insert(std::make_pair(line, this->GetWordValue(line)));
			}

			inputFile.close();
		}
	}

	// Searches for a word in the map, and retrieves the score for that word
	//
	// In:	_word			The word to search for
	//
	// Return: The word score for _word (or -1 if not found)
	int FindValueInMap(const std::string& _word) {
		auto found = this->mScrabbleMap.find(_word);

		return found != this->mScrabbleMap.end() ? // if found is not .end(), then it was found so retrun the value, else -1
			found->second
			: -1;
	}
};

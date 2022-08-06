/*
File:			Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Created:		11.30.2020
Last Modified:	11.30.2020
Purpose:		Usage of the std::vector class
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
#define LAB_2	1

// Individual unit test toggles
#define LAB2_PALINDROME_NUMBER		1
#define LAB2_FILL_FILE				1
#define LAB2_FILL_ARRAY				1
#define LAB2_CLEAR					1
#define LAB2_SORT_ASCENDING			1
#define LAB2_SORT_DESCENDING		1
#define LAB2_BRACKETS				1
#define LAB2_CONTAINS_TRUE			1
#define LAB2_CONTAINS_FALSE			1
#define LAB2_MOVE_PALINDROMES		1

/************/
/* Includes */
/************/
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>


// Checks to see if a number is a palindrome (reads the same forwards and backwards)
//		An example of a palindrome word would be "racecar"
//
// In: _num			The number to check
//
// Return: True, if the number is a palindrome number
inline bool IsPalindromeNumber(unsigned int _num) {
	unsigned int reverse = 0, _numCpy = _num;

	while (_numCpy != 0)
	{
		unsigned int digit = _numCpy % 10;
		reverse = (reverse * 10) + digit;
		_numCpy /= 10;
	}

	return reverse == _num;
}

class DSA_Lab2
{
	friend class UnitTests_Lab2;	// Giving access to test code

private:

	std::vector<int> mValues;		// contains all of the values
	std::vector<int> mPalindromes;	// contains just the numbers that are palindromes (only used in MovePalindromes method)

public:

	// Fill out the mValues vector with the contents of the binary file
	//		First four bytes of the file are the number of ints in the file
	//
	// In:	_input		Name of the file to open
	void Fill(const char* _input) {
		std::ifstream inputFile(_input, std::ios::in | std::ios::binary);
		
		int size;

		inputFile.read((char *)&size, sizeof(int));

		int num;

		for (size_t i = 0; i < size; ++i)
		{
			inputFile.read((char *)&num, sizeof(int));

			mValues.push_back(num);
		}

		inputFile.close();
	}

	// Fill out the mValues vector with the contents of an array
	//
	// In:	_arr			The array of values
	//		_size			The number of elements in the array
	void Fill(const int* _arr, size_t _size) {
		if (!mValues.empty())
			mValues.clear();

		for (size_t i = 0; i < _size; ++i)
		{
			mValues.push_back(*(_arr + i));
		}
		return;
	}

	// Remove all elements from vector and decrease capacity to 0
	void Clear() {
		mValues.clear();
		mValues.shrink_to_fit();

		mPalindromes.clear();
		mPalindromes.shrink_to_fit();
	}

	// Sort the vector 
	//
	// In:	_ascending		To sort in ascending order or not
	//
	// NOTE: Use the std::sort method in this implementation
	void Sort(bool _ascending) {
		if (_ascending)
			std::sort(mValues.begin(), mValues.end(),
				[](const int i, const int j) -> bool
				{
					return i < j;
				});
		else
			std::sort(mValues.begin(), mValues.end(),
				[](const int i, const int j) -> bool
				{
					return i > j;
				});
	}

	// Get an individual element from the mValues vector
	int operator[](int _index) {
		return mValues[_index];
	}

	// Determine if a value is present in the vector
	// 
	// In:	_val		The value to find
	//
	// Return: True, if the value is present
	bool Contains(int _val) const {
		size_t size = mValues.size();
		bool found;
		for (size_t i = 0; i < size; ++i)
		{
			found = mValues[i] == _val;
			if (found)
				break;
		}
		return found;
	}

	// Move all palindrome numbers from mValues vector to mPalindromes vector
	//
	// Pseudocode:
	//		iterate through the main values vector
	//			if the value is a palindrome
	//				add it to the palindrome vector
	//				remove it from the values vector
	void MovePalindromes() {	
		size_t values = mValues.size();
		for (size_t i = 0; i < values; ++i)
		{
			if (IsPalindromeNumber(mValues[i]))
			{
				mPalindromes.push_back(mValues[i]);
				mValues.erase(mValues.begin() + i);
				--values;
				--i;
			}
		}
		return;
	}
};


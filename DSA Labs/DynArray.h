/*
File:			DynArray.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student: Terry Ellison <ellisonterry4@gmail.com>

Created:		11.21.2020
Last Modified:	07.31.2021
Purpose:		A dynamically-allocated resizeable array (similar to std::vector)
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
#define LAB_1	1

// Individual unit test toggles
#define LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS			1
#define LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS			1
#define LAB1_BRACKET_OPERATOR						1
#define LAB1_SIZE_ACCESSOR							1
#define LAB1_CAPACITY_ACCESSOR						1
#define LAB1_RESERVE_EMPTY							1
#define LAB1_RESERVE_DOUBLE_CAPACITY				1
#define LAB1_RESERVE_LARGER_CAPACITY				1
#define LAB1_RESERVE_SMALLER_CAPACITY				1
#define LAB1_APPEND_NO_RESIZE						1
#define LAB1_APPEND_RESIZE							1
#define LAB1_CLEAR									1
#define LAB1_DESTRUCTOR								1
#define LAB1_ASSIGNMENT_OPERATOR					1
#define LAB1_COPY_CONSTRUCTOR						1

// Our implementation of a vector (simplified)
template<typename Type>
class DynArray {

	// Gives access to test code
	friend class UnitTests_Lab1;

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Type* mArray = reinterpret_cast<Type*>(-1);
	size_t mSize = -1;
	size_t mCapacity = -1;

public:

	// Default constructor
	//		Creates an empty object
	//
	// In:	_startingCap		Ann initial size to start the array at
	//
	// Note: Do not allocate any memory if the _startingCap is 0
	DynArray(size_t _startingCap = 0) {
		
		if (_startingCap != 0)
		{
			mCapacity = _startingCap;
			mArray = new Type[mCapacity];
			mSize = 0;
		}
		else
		{
			mCapacity = _startingCap;
			mSize = 0;
			mArray = nullptr;
		}
	};

	// Destructor
	//		Cleans up all dynamically allocated memory
	~DynArray() {
		delete[] mArray;
		mArray = nullptr;
	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_copy				The object to copy from
	DynArray(const DynArray& _copy) : DynArray() {
		*this = _copy;
	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_assign				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	DynArray& operator=(const DynArray& _assign) {
		if (this != &_assign)
		{
			if (this->mArray != nullptr) { this->~DynArray(); }
			this->mCapacity = _assign.mCapacity;
			this->mSize = _assign.mSize;

			this->mArray = new Type[mCapacity];

			for (unsigned int i = 0; i < mSize; ++i)
			{
				mArray[i] = _assign.mArray[i];
			}
		}
		return *this;
	}

	// Clear
	//		Cleans up all dynamically allocated memory
	//		Sets all data members back to default values
	void Clear() {
		
		this->~DynArray();
		mCapacity = 0;
		mSize = 0;
	}

	// Overloaded [] operator
	//		Used to access an element in the internal array (writeable)
	// In:	_index			The index to access at
	//
	// Return: The item at the specified index (by reference)
	Type& operator[](size_t _index) {
		return mArray[_index];
	}

	// Get the current number of elements actively being used
	//
	// Return: The current number of elements used
	size_t Size() const {
		
		return mSize;
	}

	// Get the current capacity of the internal array
	//
	// Return: The capacity of the array
	size_t Capacity() const {
		return mCapacity;
	}

	// Add an item to the end of the array
	//		Should resize the array if needed
	//
	// In:	_data			The item to be added
	void Append(const Type& _data) {
		
		if (mSize + 1 > mCapacity)
		{
			Reserve();
		}
		if (mSize == 0)
		{
			mArray[0] = _data;
		}
		else
		{
			mArray[mSize] = _data;
		}
		++mSize;
	}

	// Resizes the internal array, and copies all data over
	// In: _newCapacity		The new capacity of the array
	//		NOTE:	If 0 is passed, the array should double in size
	//				If _newCapacity < mCapacity, do nothing
	//
	//	SPECIAL CASE: If mCapacity is 0, then it should be set to 1
	void Reserve(const size_t _newCapacity = 0) {
		if (_newCapacity < mCapacity && _newCapacity != 0) { return; }
		
		else if (_newCapacity == 0)
		{
			mCapacity = mCapacity == 0 ?
				1
				: mCapacity * 2;
		}
		
		else if (_newCapacity > mCapacity)
		{
			mCapacity = _newCapacity;
		}

		Type* temp = new Type[mCapacity];

		for (unsigned int i = 0; i < mSize; ++i)
		{
			temp[i] = mArray[i];
		}

		delete[] mArray;
		mArray = temp;
		
	}
};
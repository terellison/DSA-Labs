/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student: Terry Ellison <ellisonterry4@gmail.com>

Created:		03.05.2021
Last Modified:	03.21.2021
Purpose:		A binary search tree
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

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
#define LAB_7	1

// Individual unit test toggles
#define BST_CTOR								1
#define BST_NODE_CTOR							1
#define BST_PUSH_EMPTY							1
#define BST_PUSH_ROOT_LEFT						1
#define BST_PUSH_ROOT_RIGHT						1
#define BST_PUSH_LEFT							1
#define BST_PUSH_RIGHT							1
#define BST_CLEAR								1
#define BST_DTOR								1
#define BST_CONTAINS_FOUND						1
#define BST_CONTAINS_NOTFOUND					1
#define BST_REMOVE_CASE0_ROOT					1
#define BST_REMOVE_CASE0_LEFT					1
#define BST_REMOVE_CASE0_RIGHT					1
#define BST_REMOVE_CASE1_ROOT_LEFT				1
#define BST_REMOVE_CASE1_ROOT_RIGHT				1
#define BST_REMOVE_CASE1_LEFT_LEFT				1
#define BST_REMOVE_CASE1_LEFT_RIGHT				1
#define BST_REMOVE_CASE1_RIGHT_LEFT				1
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1
#define BST_REMOVE_CASE2_CASE0					1
#define BST_REMOVE_CASE2_CASE1					1
#define BST_REMOVE_CASE0						1
#define BST_REMOVE_CASE1						1
#define BST_REMOVE_CASE2						1
#define BST_REMOVE_NOT_FOUND					1
#define BST_IN_ORDER_TRAVERSAL					1
#define BST_ASSIGNMENT_OP						0
#define BST_COPY_CTOR							0


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node {
		Type data;					// The value being stored
		Node* left, * right;		// The left and right nodes
		Node* parent;				// The parent node

		// Constructor
		//		Always creates a leaf node
		//
		// In:	_data		The value to store in this node
		//		_parent		The parent pointer (optional)
		Node(const Type& _data, Node* _parent = nullptr) {
			// TODO: Implement this method
			left = NULL, right = NULL;

			data = _data;

			if (_parent != nullptr)
			{
				parent = _parent;
			}
			else
			{
				parent = NULL;
			}
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	// The top-most Node in the tree

public:

	// Default constructor
	//			Always creates an empty tree
	BST() {
		this->mRoot = NULL;
	}

	// Destructor
	//			Clear all dynamic memory
	~BST() {
		// TODO: Implement this method
		if (this->mRoot != NULL)
		{
			this->Clear();
		}
	}

	// Copy constructor
		//			Used to initialize one object to another
		//
		// In:	_copy		The object to copy from
	BST(const BST& _copy) {
		// TODO: Implement this method

	}

	// Assignment operator
	//			Used to assign one object to another
	//
	// In:	_assign		The object to assign from
	//
	// Return:	The invoking object (by reference)
	//		This allows us to daisy-chain
	BST& operator=(const BST& _assign) {
		// TODO: Implement this method
		
	}

private:
	// Recursive helper method for use with Rule of 3
	// 
	// In:	_curr		The current Node to copy
	//
	// NOTE:	Use pre-order traversal
	void Copy(const Node* _curr) {
		// TODO: Implement this method

	}

public:

	// Clears out the tree and readies it for re-use
	void Clear() {
		// TODO: Implement this method

		if (this->mRoot != NULL)
		{
			this->Clear(this->mRoot);
			this->mRoot = NULL;
		}
	}

private:

	// Recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	//
	// NOTE:	Use post-order traversal
	void Clear(Node* _curr) {
		if (_curr->left != NULL)
		{
			this->Clear(_curr->left);
			_curr->left = NULL;
		}
		if (_curr->right != NULL)
		{
			this->Clear(_curr->right);
			_curr->right = NULL;
		}
		delete _curr;
		_curr = NULL;
	}

public:

	// Add a value into the tree
	//
	// In:	_val			The value to add
	void Push(const Type& _val) {
		if (this->mRoot == NULL)
		{
			this->mRoot = new Node(_val);
		}
		else
		{
			this->Push(_val, this->mRoot);
		}
	}

private:

	// Optional recursive helper method for use with Push
	//
	// In:	_val		The value to add
	//		_curr		The current Node being looked at
	void Push(const Type& _val, Node* _curr) {
		bool lessThan = _val < _curr->data;
		if (_curr->left != NULL && _curr->right != NULL)
		{
			lessThan ? this->Push(_val, _curr->left)
				: this->Push(_val, _curr->right);
		}
		else if (_curr->left == NULL && lessThan)
		{
			_curr->left = new Node(_val, _curr);
		}
		else
		{
			_curr->right = new Node(_val, _curr);
		}
	}
	
public:

	// Checks to see if a value is in the tree
	//
	// In:	_val		The value to search for
	//
	// Return:	True, if found
	bool Contains(const Type& _val) {
		return this->FindNode(_val) == NULL ? false : true;
	}

private:

	// Optional helper method for use with Contains and Remove methods
	//
	// In:	_val		The value to search for
	//
	// Return: The node containing _val (or nullptr if not found)
	Node* FindNode(const Type& _val) {
		Node* temp = this->mRoot;

		while (temp != NULL)
		{
			if (temp->data == _val) { break; }

			else if (_val < temp->data)
			{
				temp = temp->left;
			}
			else
			{
				temp = temp->right;
			}
		}

		return temp;
	}

	// Remove a leaf node from the tree
	//		Case 0
	// 	   
	// In:	_node		The node to remove
	void RemoveCase0(Node* _node) {
		// TODO: Implement this method
		Node* parent = _node->parent;

		if (parent != NULL)
		{
			if (parent->left == _node)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
		}
		else
		{
			this->mRoot = NULL;
		}
		delete _node;
	}

	// Remove a node from the tree that has only one child
	//		Case 1
	//
	// In:	_node		The node to remove
	void RemoveCase1(Node* _node) {
		Node* parent = _node->parent;
		Node* child;
		if (parent != NULL)
		{
			// Figure out which side the child is on

			if (_node->right != NULL)
			{
				child = _node->right;
			}
			else
			{
				child = _node->left;
			}

			child->parent = parent;

			// Figure out which side of its parent the node to delete is on
			// then put the child there

			if (parent->right == _node)
			{
				parent->right = child;
			}
			else
			{
				parent->left = child;
			}
		}
		else
		{
			// Root case

			if (_node->right != NULL)
			{
				child = _node->right;
			}
			else
			{
				child = _node->left;
			}
			
			child->parent = NULL;
			this->mRoot = child;
		}

		delete _node;
	}

	// Remove a node from the tree that has both children
	//		Case 2
	//
	// In:	_node		The node to remove
	void RemoveCase2(Node* _node) 
	{
		Node* parent = _node->parent;
		Node* right = _node->right;
		if (parent != NULL)
		{
			Node* nextLargest = right->left == NULL ? right : right->left;
			Node* temp = nextLargest;
			while (temp != NULL)
			{
				nextLargest = temp;
				temp = temp->left;
			}
			
			_node->data = nextLargest->data;

			if ((nextLargest->left == NULL) != (nextLargest->right == NULL))
			{
				this->RemoveCase1(nextLargest);
			}
			else
			{
				this->RemoveCase0(nextLargest);
			}
		}
	}

public:

	// Removes a value from tree (first instance only)
	//
	// In:	_val			The value to search for
	//
	// Return:	True, if a Node was removed
	// NOTE:	Keep in mind the three cases
	//			A) 2 children ("fix" tree)
	//			B) 0 children
	//			C) 1 child
	bool Remove(const Type& _val) {
		Node* temp = this->FindNode(_val);
		if (temp != NULL)
		{
			if (temp->left == NULL && temp->right == NULL)
				this->RemoveCase0(temp);
			else if ((temp->left == NULL) != (temp->right == NULL))
				this->RemoveCase1(temp);
			else
				this->RemoveCase2(temp);
			return true;
		}
		return false;
	}

	// Returns a space-delimited string of the tree in order
	/*
	 Example:
			 24
			/ \
		   10  48
			\   \
			12   50

	 Should return: "10 12 24 48 50"
	*/

	std::string InOrder() {
		std::string result = "";
		this->InOrder(this->mRoot, result);
		return result;
	}

private:

	// Recursive helper method to help with InOrder
	//
	// In:	_curr		The current Node being looked at
	//		_str		The string to add to
	//
	// NOTE:	Use in-order traversal
	// NOTE:	Use to_string to convert an int to its string equivelent
	void InOrder(Node* _curr, std::string& _str) {
		if (_curr->left != NULL)
		{
			this->InOrder(_curr->left, _str);
			_str += ' ';
		}

		_str += std::to_string(_curr->data);

		if (_curr->right != NULL)
		{
			_str += ' ';
			this->InOrder(_curr->right, _str);
		}
	}
};


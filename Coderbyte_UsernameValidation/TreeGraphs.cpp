#include "TreeGraphs.h"
#include <vector>
#include <map>

using namespace std;


// For this challenge you will determine if an array of integer pairs can 
// form a binary tree properly.

// The function TreeConstructor(strArr) has a string array parameter strArr, 
// which will contain pairs of integers in the following format: (i1,i2), 
// where i1 represents a child node in a tree and the second integer i2 signifies 
// that it is the parent of i1. 

// For example: if strArr is ["(1,2)", "(2,4)", "(7,2)"] which you can see forms 
// a proper binary tree. Your program should, in this case, return the string true 
// because a valid binary tree can be formed. If a proper binary tree cannot be 
// formed with the integer pairs, then return the string false. All of the integers 
// within the tree will be unique, which means there can only be one node in the 
// tree with the given integer value.

std::string TreeGraphs::TreeConstructor(std::string strArr[], int length)
{
	bool					validTree = true;
	string					result;
	vector<string>			input(strArr, strArr + length);
	vector<pair<int, int>>	data;
	multimap<int, int>		parents;
	map<int, int>           childCount;
	int						root;

	data = parseInput(input);

	for (pair<int, int> item : data)
	{
		// parents[item.first] = item.second;
		multimap<int, int>::value_type  value(item.first, item.second);
		parents.insert(value);
		childCount[item.second]++;
	}

	// find root
	for (auto item : data)
	{
		map<int, int>::iterator iter;

		iter = parents.find(item.second);
		if (iter == parents.end())
		{
			root = item.second;
		}
	}

	validTree = (root != 0);

	// check for > 2 children
	for (auto item : childCount)
	{
		if (item.second > 2)
		{
			validTree = false;
		}
	}

	// check for child with multiple parents
	for (auto item : parents)
	{
		pair <multimap<int, int>::iterator, multimap<int, int>::iterator> result;
		result = parents.equal_range(item.first);

		if (std::distance(result.first, result.second) > 1)
		{
			validTree = false;
			break;
		}
	}

	result = (validTree) ? "true" : "false";

	return result;
}


// For this challenge you will traverse a binary tree and determine if it is symmetric.
// The function SymmetricTree(strArr) take the array of strings stored in strArr, 
// which will represent a binary tree, and determine if the tree is symmetric (a 
// mirror image of itself). The array will be implemented similar to how a binary 
// heap is implemented, except the tree may not be complete and NULL nodes on any 
// level of the tree will be represented with a #. 

// For example: if strArr is ["1", "2", "2", "3", "#", "#", "3"]
// Tree:
//				1
//		2				2
//	3		#		#		3

// For the input above, your program should return the string true because the 
// binary tree is symmetric.

std::string TreeGraphs::SymmetricTree(std::string strArr[], int length)
{
	string					result;
	bool					isSymmetric = false;
	vector<string>			input(strArr, strArr + length);
	Node *					root = nullptr;

	root = createTreeNode(input[0]);

	//populate tree
	root = fillTree(input, root, 0, input.size());

	// check for symmetry
	isSymmetric = isTreeSymmetric(root, root);


	result = (isSymmetric) ? "true" : "false";

	return result;
}

std::vector<pair<int, int>> TreeGraphs::parseInput(std::vector<std::string> input)
{
	vector<pair<int, int>>	data;

	// parse input into data vector
	for (string str : input)
	{
		int num1, num2;
		pair<int, int>  temp;

		parseInputString(str, num1, num2);
		temp = make_pair(num1, num2);
		data.push_back(temp);
	}

	return data;
}

void TreeGraphs::parseInputString(std::string str, int & num1, int & num2)
{
	// assume correct structure
	// find comma -> substr-> trim '('
	// substr rest of str -> trim ')'

	string::size_type pos;
	string delimiter = string(",");
	string temp;

	// extract first number
	pos = str.find(delimiter);
	if (pos != string::npos)
	{// remove ( char
		temp = str.substr(1, pos);
		num1 = stoi(temp);
	}

	// extract 2nd number
	temp = str.substr(pos + 1, str.length() - 2);
	num2 = stoi(temp);
}

Node* TreeGraphs::createTreeNode(string data)
{
	Node* node = new Node;

	node->data = data;
	node->left = nullptr;
	node->right = nullptr;

	return node;
}



Node * TreeGraphs::fillTree(vector<string> arr, Node * root, int index, int length)
{
	// Base case for recursion 
	if (index  < length)
	{
		Node* temp = createTreeNode(arr[index]);
		root = temp;

		// insert left child 
		root->left = fillTree(arr, root->left, 2 * index + 1, length);

		// insert right child 
		root->right = fillTree(arr,	root->right, 2 * index + 2, length);
	}

	return root;
}


bool TreeGraphs::isTreeSymmetric(Node * node1, Node * node2)
{
	bool isSymmetric = false;

	// empty tree
	if (node1 == nullptr && node2 == nullptr)
	{
		isSymmetric = true;
	}

	// For two trees to be mirror 
	// images, the following
	// three conditions must be true 
	// 1 - Their root node's data must be same 
	// 2 - left subtree of left tree and right subtree of right tree are equal
	// 3 - right subtree of left tree and left subtree of right tree are equal
	else if (node1 && node2 && node1->data == node2->data)
	{
		isSymmetric = isTreeSymmetric(node1->left,  node2->right) && 
					  isTreeSymmetric(node1->right, node2->left);
	}

	return isSymmetric;
}



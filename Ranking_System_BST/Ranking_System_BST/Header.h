#pragma once

#include <iostream> 
static int counts = 1;
static bool update = false;
static bool update_notFound = false;
static bool print_header = true;
using namespace std;


class nodeBST
{
public:
	double key;
	string user_id;
	int m_marks;
	int p_marks;
	int ch_marks;
	int en_marks;
	int rank;
	nodeBST* lft, * rgt;
	nodeBST();
	nodeBST(double key, string user_id, int m_marks, int ch_marks, int en_marks);
	nodeBST* insertFunc(nodeBST* root, double key, string user_id, int m_marks, int ch_marks, int en_marks);
	nodeBST* searchFunc(nodeBST* root, int key);
	nodeBST* deleteNode(nodeBST** rootPtr, string user_id);
	nodeBST* minValueNode(nodeBST* node);
	nodeBST* getParent(nodeBST* root, nodeBST* child);
	nodeBST* searchby_id(nodeBST* root, string user_id);
	nodeBST* updateNode(nodeBST* root, string user_id, double value, int m_marks, int ch_marks, int en_marks);
	void showRankings(nodeBST* root, nodeBST bst);
	void traverseInOrder(nodeBST* root);
	void AssignRank(nodeBST* root);
	void printValueRange(nodeBST* root, double minVal, double maxVal);
};

nodeBST::nodeBST()
	: key(0)
	, user_id(" ")
	, lft(NULL)
	, rgt(NULL)
	, m_marks(0)
	, ch_marks(0)
	, en_marks(0)
	, p_marks(0)
	, rank(0)
{


}
nodeBST::nodeBST(double value, string user_id_s, int m_mark_s, int ch_mark_s, int en_mark_s)
{
	key = value;
	user_id = user_id_s;
	m_marks = m_mark_s;
	ch_marks = ch_mark_s;
	en_marks = en_mark_s;
	rank = 0;
	lft = rgt = NULL;
}


nodeBST* nodeBST::insertFunc(nodeBST* root, double value, string user_id, int m_marks, int ch_marks, int en_marks)

{
	if (!root)
	{
		return new nodeBST(value, user_id, m_marks, ch_marks, en_marks);
	}
	if (value > root->key)
	{
		root->rgt = insertFunc(root->rgt, value, user_id, m_marks, ch_marks, en_marks);
	}
	else
	{
		root->lft = insertFunc(root->lft, value, user_id, m_marks, ch_marks, en_marks);
	}
	counts = 1;
	AssignRank(root);
	
	return root;
}



nodeBST* nodeBST::updateNode(nodeBST* root, string user_id, double value, int m_marks, int ch_marks, int en_marks)
{
	update = true;
	root = deleteNode(&root, user_id);
	update = false;

	// Then, insert a new node with the updated values
	root = insertFunc(root, value, user_id, m_marks, ch_marks, en_marks);
	counts = 1;
	AssignRank(root);
	if (!update_notFound)cout << ">>>>>> Student " << user_id<< " Updated Successfully !" << endl;
	cout << endl;
	return root;
}

nodeBST* nodeBST::searchFunc(nodeBST* root, int key)
{
	if (root == NULL || root->key == key)
		return root;
	if (root->key < key)
		return searchFunc(root->rgt, key);
	return searchFunc(root->lft, key);
}

nodeBST* nodeBST::searchby_id(nodeBST* root, string user_id_s)//filter by Id
{
	if (!root)
	{
		return NULL;
	}

	nodeBST* result = NULL;
	result = searchby_id(root->lft, user_id_s);
	if (result != NULL) {
		return result;
	}

	if (root->user_id == user_id_s) {
		return root;
	}

	result = searchby_id(root->rgt, user_id_s);
	return result;
}


nodeBST* nodeBST::getParent(nodeBST* root, nodeBST* child) {
	// If the tree is empty or the child is the root node
	if (root == NULL || root == child) {
		return NULL;
	}

	// If the child is the left or right child of the root
	if (root->lft == child || root->rgt == child) {
		return root;
	}

	// Recursively search for the parent node in the left and right subtrees
	if (child->key < root->key) {
		return getParent(root->lft, child);
	}
	else {
		return getParent(root->rgt, child);
	}
}

void nodeBST::showRankings(nodeBST* root, nodeBST bst)
{
	cout << "\nStudent ID" << "\t" << "Total Marks" << "\t" << "Mathematics Marks" << "\t" << "Chemistry Marks" << "\t\t\b\b\b\b\b\b" << "English Marks" << "\t   " << "Rank" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	bst.traverseInOrder(root);
	cout << "\n";
}


void nodeBST::traverseInOrder(nodeBST* root)
{

	if (!root)
	{
		return;
	}

	traverseInOrder(root->rgt);

	cout << root->user_id << "\t\t" << root->key << "\t\t" << root->m_marks << "\t\t\t" << root->ch_marks << "\t\t  " << root->en_marks << "\t\t   " << root->rank << endl;


	traverseInOrder(root->lft);

}


void nodeBST::AssignRank(nodeBST* root)
{
	

	if (root->rgt != NULL)
		AssignRank(root->rgt);

	
	
		root->rank = counts; 
		counts++; 

 

	if (root->lft != NULL)
		AssignRank(root->lft);
}

nodeBST* nodeBST::minValueNode(nodeBST* node)
{
	nodeBST* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->lft != NULL)
		current = current->lft;

	return current;
}



void nodeBST::printValueRange(nodeBST* root, double minVal, double maxVal) {
	if (maxVal <= minVal)
	{
		cout << "\nInvalid Range\n"<<endl;
		return;
	}
	if (root == NULL) {
		return;
	}
	if (root->key < maxVal) 
	{
		printValueRange(root->rgt, minVal, maxVal);
	}
	if (root->key >= minVal && root->key <= maxVal)
	{
		if (print_header == true) 
		{
			cout << "\nStudent ID" << "\t" << "Total Marks" << "\t" << "Mathematics Marks" << "\t" << "Chemistry Marks" << "\t\t\b\b\b\b\b\b" << "English Marks" << "\t   " << "Rank" << endl;
			cout << "-----------------------------------------------------------------------------------------" << endl;
	    }
		print_header = false;
		cout << root->user_id << "\t\t" << root->key << "\t\t" << root->m_marks << "\t\t\t" << root->ch_marks << "\t\t  " << root->en_marks << "\t\t   " << root->rank << endl;
	}
	if (root->key > minVal) 
	{
		printValueRange(root->lft, minVal, maxVal);
	}
}



nodeBST* nodeBST::deleteNode(nodeBST** rootPtr, string user_id_s)
{
	nodeBST* root = *rootPtr;
	nodeBST* rootPtrs = searchby_id(root, user_id_s);

	// Return if the tree is empty or the node is not found
	if (rootPtrs == NULL)
	{
		update_notFound = true;
		cout << ">>>>>>There is no student name !! " << user_id_s << endl;
		cout << endl;
		return root;


	}
	update_notFound = false;
	// If the node is a leaf node
	if (rootPtrs->lft == NULL && rootPtrs->rgt == NULL)
	{
		if (root == rootPtrs)
		{ // The node is the root node
			delete root;
			*rootPtr = NULL; // Update the root pointer

			return NULL;
		}
		nodeBST* parent = getParent(root, rootPtrs);
		if (parent->lft == rootPtrs)
			parent->lft = NULL;
		else
			parent->rgt = NULL;
		delete rootPtrs;
	}
	// If the node has only one child
	else if (rootPtrs->lft == NULL)
	{
		nodeBST* temp = rootPtrs->rgt;
		if (root == rootPtrs) 
		{ // The node is the root node
			delete root;
			*rootPtr = temp; // Update the root pointer

			return temp;

		}
		nodeBST* parent = getParent(root, rootPtrs);
		if (parent->lft == rootPtrs)
			parent->lft = temp;
		else
			parent->rgt = temp;
		delete rootPtrs;
	}
	else if (rootPtrs->rgt == NULL)
	{
		nodeBST* temp = rootPtrs->lft;
		if (root == rootPtrs) { // The node is the root node
			delete root;
			*rootPtr = temp; // Update the root pointer

			return temp;
		}
		nodeBST* parent = getParent(root, rootPtrs);
		if (parent->lft == rootPtrs)
			parent->lft = temp;
		else
			parent->rgt = temp;
		delete rootPtrs;
	}
	// If the node has two children
	else
	{
		nodeBST* inorderSucc = minValueNode(rootPtrs->rgt);
		rootPtrs->key = inorderSucc->key;
		rootPtrs->user_id = inorderSucc->user_id;
		rootPtrs->m_marks = inorderSucc->m_marks;
		rootPtrs->ch_marks = inorderSucc->ch_marks;
		rootPtrs->en_marks = inorderSucc->en_marks;
		rootPtrs->rgt = deleteNode(&(rootPtrs->rgt), inorderSucc->user_id); // Pass rootPtr->rgt by reference
	}
	// Reassign ranks to all nodes 
	counts = 1;
	AssignRank(*rootPtr);
	if (!update)cout << ">>>>>> Student " << user_id_s << " Deleted Successfully !" << endl;
	cout << endl;

	// Update the root pointer if necessary
	if (root == rootPtrs) {
		*rootPtr = getParent(root, rootPtrs);
	}
	showRankings(*rootPtr, *root);
	return *rootPtr;

}


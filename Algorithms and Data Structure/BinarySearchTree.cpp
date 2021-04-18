//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Dylan W. Sanderson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <string>
#include "CSVparser.hpp"
#include <algorithm>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// FIXME (1): Internal structure for tree node
struct Node {
	Bid bid;
	Node* left;
	Node* right;

	//Default constructor for null pointers
	Node() {
		left = nullptr;
		right = nullptr;
	}

	//Default with a bid, references previous
	Node(Bid newBid) : Node() {
		this->bid = newBid;
	}
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    // Currently not used
    // void Remove(string bidId);
    Bid Search(string bidId);
    void Printall(Node* node);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
	//We make the root null so the methods can tell the tree is empty
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
}
\
void BinarySearchTree::Printall(Node* node) {
    // If the node is empty, end.
    if (node == nullptr) {
        return;
    }
    // otherwise, recursion time.
    else {
        // Check to the left first, for the smallest, and call the method on the left child
        if (node->left != nullptr) {
            Printall(node->left);
        }
        // Now we know there's nothing else to the left, so print our current bid
        cout << "Bid ID: " << node->bid.bidId << endl;
        cout << "Title: " << node->bid.title << endl;
        cout << "Fund: " << node->bid.fund << endl;
        cout << "Amount: " << node->bid.amount << endl;
        // The, if there's something to the right, recursive call on it
        if (node->right != nullptr) {
            Printall(node->right);
        }
        return;
    }
    return;
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree
	//First we check if it's empty
	if (root == nullptr) {
		//use the constructor with a bid call to build the root
		root = new Node(bid);
	}
	//else call the add node method
	else {
		addNode(root, bid);
	}
}

/**
 * Remove a bid
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
	if (node == nullptr) {
		return node;
	// recurse down the left subtree
	} else if (bidId.compare(node->bid.bidId) < 0) {
		node->left = removeNode(node->left, bidId);
	// recurse down the right subtree
	} else if (bidId.compare(node->bid.bidId) > 0) {
		node->right = removeNode(node->right, bidId);
	} else {
		// no children so node is a leaf node
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
			// one child to the left
		} else if (node->left != nullptr && node->right == nullptr) {
			Node* temp = node;
			node = node->left;
			delete temp;
			// one child to the right
		} else if (node->left == nullptr && node->right != nullptr) {
			Node* temp = node;
			node = node->right;
			delete temp;
			// two children
		} else {
			// find the minimum
			Node* temp = node->right;
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			node->bid = temp->bid;
			node->right = removeNode(node->right, temp->bid.bidId);
		}
	}
	return node;
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid
	//Build a default bid, so default values indicate a not found
	Bid bid;
	//And a node pointer for our loop
	Node* lookit = root;
	//Pull the bidId as an int
	int key = atoi(bidId.c_str());

	//Now we will use a while, checking if we're going left or right.
	//If we ever hit a null, we know it's not in the tree.
	while (lookit != nullptr){
		//pull the current node's id for an int comparison
		int nodeKey = atoi(lookit->bid.bidId.c_str());
		//Return it if we have found it
		if (lookit->bid.bidId == bidId){
			return lookit->bid;
		}
		//use comparison to decide if we go left or right
		else if (key > nodeKey){
			lookit = lookit->right;
		}
		else {
			lookit = lookit->left;
		}
	}

    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree
	//We will attempt to be consistent in out implementation here,
	//Including for repeat key handlings, though they are unlikely.
	//First, we will pull out our bid IDs to compare.
	int nodeKey = atoi(node->bid.bidId.c_str());
	int key = atoi(bid.bidId.c_str());

	//Then, we compare. To the right if it's bigger.
	if (key > nodeKey) {
		//If empty, just add it
		if (node->right == nullptr) {
			node->right = new Node(bid);
		}
		//Otherwise, recursively call itself to traverse the tree
		else {
			addNode(node->right, bid);
		}
	}
	//We won't put a comparitor on else, as we know the insert is
	//smaller than or equal to our target, and we will push any matching
	//IDs to the left.
	else{
		//If empty, just add it
		if (node->left == nullptr) {
			node->left = new Node(bid);
		}
		//Otherwise, reflexively call itself to traverse the tree
		else {
			addNode(node->left, bid);
		}
	}
}
void BinarySearchTree::inOrder(Node* node) {
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            // bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}

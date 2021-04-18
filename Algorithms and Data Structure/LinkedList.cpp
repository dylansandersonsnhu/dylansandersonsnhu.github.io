//============================================================================
// Name        : LinkedList.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

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

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    // FIXME (1): Internal structure for list entries, housekeeping variables
	//Create a struct def for a node to hold data and the next node address
	//We will use a singly linked for now, alter later if needed.
	struct node {
	       Bid theBid;
	       node* nextNode;
	   };
	//Allocate memory for head and tail addresses and a size int
	node* head;
	node* tail;
	int size;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXME (2): Initialize housekeeping variables
	//For initialization, make both adress holders null pointers, make size 0
	//Allow for simple and logical alteration later
	head = nullptr;
	tail = nullptr;
	size = 0;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIXME (3): Implement append logic
	//First, we need to create the node and store the bid in it
	node* newNode = new node;
	newNode->theBid = bid;
	//Let's initialize and null the nextNode pointer
	newNode->nextNode = nullptr;

	//First, if the linked list is empty, the node addition is easy.
	//We make our null head and tail point to the new node, increase our size counter by 1.
	//No alterations needed to the node we already built.
	if (head == nullptr){
		head = newNode;
		tail = newNode;
	}

	//If there is an item in the list, execute this else
	else{
		//First, make the current tail point to the new node
		tail->nextNode = newNode;
		//Then, move the tail to point to our appended node
		tail = newNode;
	}
	//Either if or else appended a node, so increment.
	size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (4): Implement prepend logic
	//Start with the same newNode build as in append
	node* newNode = new node;
	newNode->theBid = bid;
	newNode->nextNode = nullptr;

	//If empty, same as append
	if (head == nullptr){
			head = newNode;
			tail = newNode;
	}

	//If there's anything in it, this is where we get tricky
	//We will have the new node point to the current head as it's next,
	//Then shift the head target to the new node.
	else {
		newNode->nextNode = head;
		head = newNode;
	}

	//Then we increment as we have added a node.
	size++;

}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic
	//relatively striaghtforward, we implement a pointer at the head
	node* curr = head;
	//Now we loop through the whole list, using our nullptr to stop at the end
	while (curr != nullptr) {
		//Print the data specified in the Lab Requirements with cout
		//Referece specific bid aspects with item.sub notation
		cout << curr->theBid.title << " | " ;
	    cout << curr->theBid.amount << " | " ;
	    cout << curr->theBid.fund << endl;
	    //cycle to the next node
	    curr = curr->nextNode;
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic
	//start with a pointer
	node* curr = head;
	//implement another pointer for use case-dependantly
	node* prev;

	//a simple if catch in case we try to remove a bid from an empty list
	//this will prevent crashes
	if (curr == nullptr) {
		return;
	}

	//if we have a one item list, we simply unpoint and delete
	else if (head->theBid.bidId == bidId && head->nextNode == nullptr){
	    head = nullptr;
	    tail = nullptr;
	    delete curr;
	}

	//If it's the head and there's other items
	else if (head->theBid.bidId == bidId && head->nextNode != nullptr){
		//we move the head pointer to the next item and delete the current node
		head = head->nextNode;
		delete curr;
	}

	//All other cases, looping through until we find it
	else {
	    while(curr->theBid.bidId != bidId){
	    	//mark the last node for logic until we find it
	        prev = curr;
	        //increment the current node
	        curr = curr->nextNode;
	    }
	    //like with the last scenario, we unpoint at the current node and delete
	    prev->nextNode = curr->nextNode;
	    delete curr;
	}
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic
	//start with a current pointer at the head
	node* curr = head;
	//cycle through the list searching for it
	while (curr != nullptr){
		//if we find it, return it
        if (curr->theBid.bidId == bidId){
            return curr->theBid;
        }
        //cycle forwards if not found
        curr = curr->nextNode;
    }
	//if we made it this far, it's not in the list
	//therefore, we need to create and return an empty bid structure.
	node* mT = new node;
	mT->theBid.bidId = "";
    return mT->theBid;
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
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

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
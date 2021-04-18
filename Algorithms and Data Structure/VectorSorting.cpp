//============================================================================
// Name        : VectorSorting.cpp
// Author      : Your name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
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
 * Prompt user for bid information using console (std::in)
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
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	//set up low and high ints, midpoint int, pivot and temp bids, done check
	int l = 0;
	int h = 0;
	int midpoint = 0;
	Bid pivot;
	Bid temp;
	bool done = false;

	//Grab the middle bid to use as the pivot
	midpoint = begin + (end - begin) / 2;
	pivot = bids.at(midpoint);

	//set our low and high to the begin and end input
	l = begin;
	h = end;

	//our while not done loop
	while (!done) {

	   //Increment l when we're less than the pivot
	   while (bids.at(l).title < pivot.title) {
	      ++l;
	   }

	   //Decrement h while more than pivot
	   while (pivot.title < bids.at(h).title) {
	      --h;
	   }

	   //If l is >= h, we're at either a 1 unit or empty partition
	   //Partitioning is done, close the boolean while, return h
	   if (l >= h) {
	      done = true;
	   }
	   else {
	      //Swap bids at l and h and increment/decrement as necessary
	      temp = bids.at(l);
	      bids.at(l) = bids.at(h);
	      bids.at(h) = temp;
	      ++l;
	      --h;
	   }
	}
	//return
	return h;

}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
	//setup an int value to catch our partition return int
	int j = 0;

	//If partition is empty or has one element, is already sorted naturally
	//This is considered the base case
	if (begin >= end) {
	   return;
	}

	//Partition array, returns high value from low array (h in partition function)
	//Put returned (h) value in j for recursive self-calls
	j = partition(bids, begin, end);

	//Quicksort low partition (i to j) and high partition (j + 1 to k)
	quickSort(bids, begin, j);
	quickSort(bids, j + 1, end);

	//return
	return;
}

// FIXME (1a): Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
	//Declare our needed variables
	int i = 0;
	int j = 0;
	int ind = 0;
	Bid temp;

	//outer loop, iterate through all but the last item
	for (i=0; i<bids.size()-1; ++i) {
		ind = i;
		//inner loop, finds the smallest item in the remaining vector
		for (j=i+1; j<bids.size(); ++j) {
			//if smaller item is found, save it's index
			if (bids.at(j).title < bids.at(ind).title) {
				ind = j;
			}
		}
		//assign current bid value to a temp holder
		temp = bids.at(i);
		//move lowest to the current
		bids.at(i) = bids.at(ind);
		//put the current back in
		bids.at(ind) = temp;
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
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // FIXME (1b): Invoke the selection sort and report timing results
        case 3:
        	//Catch current system time
        	ticks = clock();

        	//call selection sort function on vector
        	selectionSort(bids);

        	//output how long that function took
        	ticks = clock() - ticks; // current clock ticks minus starting clock ticks
        	cout << "time: " << ticks << " clock ticks" << endl;
        	cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
        	break;

        // FIXME (2b): Invoke the quick sort and report timing results
        case 4:
        	//Catch current system time
        	ticks = clock();

        	//call quicksort (and technically partition) on bid vector
        	quickSort(bids, 0, bids.size() - 1);

        	//Ouput how long that function took
         	ticks = clock() - ticks; // current clock ticks minus starting clock ticks
          	cout << "time: " << ticks << " clock ticks" << endl;
           	cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

        	break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}

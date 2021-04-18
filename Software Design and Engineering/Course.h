#pragma once
using namespace std;
// So we can use strings
#include <string>

//Class declaration
class Course
{
	// Object properties
	string name;
	int iD;
	int credHours;
	string desc;
	string prereqs;

	// Default Constuctor
	Course() {
		name = "Empty";
		iD = 0;
		credHours = 0;
		desc = "Empty";
		prereqs = "None";
	}

	// Below will be methods to interact data in the object
	// Find methods will return the object itself to be used however
	// Change methods will take a single input and alter said data point

	// Return the course's name
	string findName() {
		return name;
	}

	// Alter the course's name
	void changeName(string newName) {
		name = newName;
	}

	// Returns ID as int
	int findID() {
		return iD;
	}

	// Takes new ID number as input, alters value
	void changeID(int id) {
		iD = id;
	}

	// Returns the credit hours (assumed to be whole numbers)
	// If credit hours end up requiring decimals, editing will be needed
	int findCredits() {
		return credHours;
	}

	// Change the credit hours
	void changeCredits(int hours) {
		credHours = hours;
	}

	// Return the course description string
	string findDesc() {
		return desc;
	}

	// Put in a different desctription
	void changeDesc(string description) {
		desc = description;
	}

	// Return the string with prerequisite courses listed
	string findPrereqs() {
		return prereqs;
	}

	// This will allow the prereq list to be completely replaced
	void changePrereqs(string newReqs) {
		prereqs = newReqs;
	}
	// This will allow you to add a prerequisite without retyping the entire list
	void addPrereq(string additional) {
		prereqs.append(" ");
		prereqs.append(additional);
	}
};


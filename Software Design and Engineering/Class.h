#pragma once
using namespace std;
// So we can use strings
#include <string>

// Class declaration
class Class
{
	// Object properties
	int iD;
	string dates;
	string status;
	string uRL;
	string browser;
	string building;
	int room;
	int courseID;

	// Default Constructor
	Class() {
		iD = 0;
		dates = "Unknown";
		status = "Unknown";
		uRL = "Unknown";
		browser = "Unknown";
		building = "Unknown";
		room = 0;
		courseID = 0;
	}

	// Below will be methods to interact data in the object
	// Find methods will return the object itself to be used however
	// Change methods will take a single input and alter said data point

	// Returns ID as int
	int findID() {
		return iD;
	}

	// Takes new ID number as input, alters value
	void changeID(int id) {
		iD = id;
	}

	// Returns dates as string
	string findDates() {
		return dates;
	}

	// Change information in dates
	void changeDates(string newOnes) {
		dates = newOnes;
	}

	// Returns status as string
	string findStatus() {
		return status;
	}

	// Change information in status, should either be "online" or "F2F" (for face to face)
	void changeStatus(string newStat) {
		status = newStat;
	}

	// Returns url if online, "Unknown" if F2F or not input yet
	string findURL() {
		return uRL;
	}

	// Inputs new URL in string form
	void changeURL(string replacement) {
		uRL = replacement;
	}

	// Returns a string of supported browsers, "Unknown" if not known or altered yet
	string findBrowser() {
		return browser;
	}

	// Changes the browser string
	void changeBrowser(string supported) {
		browser = supported;
	}

	// Returns the building name
	string findBuilding() {
		return building;
	}

	// Edit the building name
	void changeBuilding(string newone) {
		building = newone;
	}

	// Returns the room number
	int findRoom() {
		return room;
	}

	// Alter the room number
	void changeRoom(int num) {
		room = num;
	}

	// Return the parent course's ID number
	int findCourseID() {
		return courseID;
	}

	// Alter the parent course ID
	void changeCourseID(int newCourse) {
		courseID = newCourse;
	}
};
#pragma once
using namespace std;
// So we can use strings
#include <string>

// Class declaration
class Student
{
	// Object properties
	string name;
	string dOB;
	int iD;
	string major;
	double gPA;
	string regClass;

	// Default Constructor
	Student() {
		name = "Blank";
		dOB = "Unknown";
		iD = 0;
		major = "Undeclared";
		gPA = 0.0;
		regClass = "None";
	}

	// Below will be methods to interact data in the object
	// Find methods will return the object itself to be used however
	// Change methods will take a single input and alter said data point

	// Return the student name
	string findName() {
		return name;
	}

	// Alter the student name
	void changeName(string newName) {
		name = newName;
	}

	// Return the date of birth, stored as a string
	string findDOB() {
		return dOB;
	}

	// Alter the date of birth
	void changeDOB(string dateBirth) {
		dOB = dateBirth;
	}

	// Returns ID as int
	int findID() {
		return iD;
	}

	// Takes new ID number as input, alters value
	void changeID(int id) {
		iD = id;
	}

	// Return the student's major
	string findMajor() {
		return major;
	}

	// Change the major declaration
	void changeMajor(string newMajor) {
		major = newMajor;
	}

	// This one returns the student's grade point average
	double findGPA() {
		return gPA;
	}

	// And alter said gpa
	void changeGPA(double grades) {
		gPA = grades;
	}

	//// Return the string with registered classes listed
	string findReg() {
		return regClass;
	}

	// This will allow the class registration string to be completely replaced
	void changeReg(string newReg) {
		regClass = newReg;
	}
	// This will allow you to add a prerequisite without retyping the entire list
	void addReg(string additional) {
		regClass.append(" ");
		regClass.append(additional);
	}
};


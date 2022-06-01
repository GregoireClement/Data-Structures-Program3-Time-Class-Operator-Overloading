

 // Header guard directives--ensures header included only once
#ifndef TIME_H
#define TIME_H

#include <iostream>
using std::ostream;
using std::istream;

class Time {
public:
	/*** FUNCTIONS DEFINED FOR YOU IN Time.cpp ***/
	Time();										         // Default constructor
	Time(unsigned h, unsigned m, char AP);		   // Parameterized constructor
	void set(unsigned h, unsigned m, char AP);	// Set time data members
	void display(ostream& out);					   // Print time to desired output stream
	void advance(unsigned h, unsigned m);		   // Advance time by given number of hours and minutes
	bool lessThan(const Time& rhs);				   // Returns true if calling object is less than argument

	/*** OVERLOADED OPERATORS TO BE ADDED FOR PROGRAM 3 ***/
	// Input/output operators
	friend ostream& operator <<(ostream& out, const Time& rhs);
	friend istream& operator >>(istream& in, Time& rhs);

	// Comparison operators
	bool operator ==(const Time& rhs);
	bool operator !=(const Time& rhs);
	bool operator <(const Time& rhs);
	bool operator >(const Time& rhs);

	// Arithmetic operators
	Time operator +(const Time& rhs);
	Time operator -(const Time& rhs);
	Time& operator +=(const Time& rhs);
	Time& operator -=(const Time& rhs);

	// Increment operators--adds 1 minute to current time
	Time& operator++();
	Time operator++(int);
	/*** END OVERLOADED OPERATORS TO BE ADDED FOR PROGRAM 3 ***/


private:
	unsigned hours, minutes;	// Time in hrs/mins (combined with AM/PM)
	char AMorPM;				   // Indicates morning/afternoon--'A' for AM, 'P' for PM
	unsigned miltime;			   // Military (24-hour) time equivalent
};

#endif		// TIME_H
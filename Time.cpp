

#include "Time.h"	   // Necessary for Time class definition; implicitly includes <iostream>
#include <iomanip>	// Necessary for setw(), setfill()
using std::setw;
using std::setfill;
using namespace std;

/*** OVERLOADED OPERATORS TO BE ADDED FOR PROGRAM 3 ***/
/*** PREVIOUSLY DEFINED FUNCTIONS START ON LINE 145 (BEFORE YOU START ADDING CODE) ***/
/*** UPDATED 10/11 TO FIX PARAMETERIZED CONSTRUCTOR, advance() ***/

// Output operator
ostream& operator <<(ostream& out, const Time& rhs) {

	out << rhs.hours << ':'
		<< setw(2) << setfill('0') << rhs.minutes
		<< ' ' << rhs.AMorPM << 'M';

	return out;
}

// Input operator
istream& operator >>(istream& in, Time& rhs) {

	int h, m;
	char discard;
	char ap;

	in >> h;
	in >> discard;
	in >> m;
	in >> ap;
	in >> discard;

	rhs.set(h, m, ap);

	return in;
}

// Comparison operators
bool Time::operator ==(const Time& rhs) {

	if (hours == rhs.hours && minutes == rhs.minutes && AMorPM == rhs.AMorPM) {
		return true;
	}

	return false;
}

bool Time::operator !=(const Time& rhs) {

	return !(*this == rhs);
}

bool Time::operator <(const Time& rhs) {

	if (*this == rhs)
		return false;
	return lessThan(rhs);
}

bool Time::operator >(const Time& rhs) {

	if (*this == rhs)
		return false;
	return !lessThan(rhs);
}

// Arithmetic operators
Time Time::operator +(const Time& rhs) {
	Time sum;

	if (hours == 12 && AMorPM == 'A')
		sum.advance(hours - 12, minutes);
	else
		sum.advance(hours, minutes);
	if (rhs.hours == 12 && rhs.AMorPM == 'A')
		sum.advance(rhs.hours - 12, rhs.minutes);
	else
		sum.advance(rhs.hours, rhs.minutes);
	if (AMorPM == 'P')
		sum.advance(12, 0);
	if (rhs.AMorPM == 'P')
		sum.advance(12, 0);
	return sum;
}


Time Time::operator -(const Time& rhs) {

	int lh = hours;
	if (AMorPM == 'P' && hours != 12)
		lh += 12;
	if (AMorPM == 'A' && hours == 12)
		lh -= 12;


	int rh = rhs.hours;
	if (rhs.AMorPM == 'P' && rhs.hours != 12)
		rh += 12;
	if (rhs.AMorPM == 'A' && rhs.hours == 12)
		rh -= 12;

	int h = lh - rh;
	if (h < 0)
		h = 24 + h;

	int m = minutes - rhs.minutes;
	if (m >= 60)
	{
		m -= 60;
		h++;
	}
	if (m < 0)
	{
		m += 60;
		h--;
	}

	char ap;
	if (h > 12)
	{
		h -= 12;
		ap = 'P';
	}
	else if (h == 12)
		ap = 'P';
	else
	{
		ap = 'A';
	}

	if (h == 0 && ap == 'A')
		h += 12;
	// cout << "h: " << h << "m: " << m << "ap: " << ap << endl;
	Time res(h, m, ap);
	return res;
}

Time& Time::operator +=(const Time& rhs) {

	Time res = *this + rhs;
	set(res.hours, res.minutes, res.AMorPM);
	return *this;

}

Time& Time::operator -=(const Time& rhs) {

	Time temp = *this - rhs;
	set(temp.hours, temp.minutes, temp.AMorPM);
	return *this;

}

// Increment operators--adds 1 minute to current time
Time& Time::operator++() {

	advance(0, 1);
	return *this;

}

Time Time::operator++(int) {

	Time t(hours, minutes, AMorPM);
	advance(0, 1);
	return t;

}
/*** END OVERLOADED OPERATORS TO BE ADDED FOR PROGRAM 3 ***/
/*** DO NOT MODIFY CODE BELOW THIS LINE ***/
// Default constructor
Time::Time() : hours(0), minutes(0), miltime(0), AMorPM('A')
{}

// Parameterized constructor
Time::Time(unsigned h, unsigned m, char AP) : hours(h), minutes(m), AMorPM(AP) {
	miltime = 100 * h + m;

	/*** FIXED 10/11: ORIGINAL VERSION DID NOT CORRECTLY HANDLE 12 AM OR 12 PM ***/
	if (AP == 'P' && h != 12)
		miltime += 1200;
	else if (AP == 'A' && h == 12)
		miltime -= 1200;
}

// Set time data members
void Time::set(unsigned h, unsigned m, char AP) {
	hours = h;
	minutes = m;
	AMorPM = AP;
	miltime = 100 * h + m;
	if (AP == 'P')
		miltime += 1200;
}

// Print time to desired output stream
void Time::display(ostream& out) {
	out << hours << ':'
		<< setw(2) << setfill('0') << minutes		// setw(2) forces minutes to be printed with 2 chars
		<< ' ' << AMorPM << 'M';					// setfill('0') adds leading 0 to minutes if needed
}

// Advance time by h hours, m minutes
// Use modulo arithmetic to ensure 
//   1 <= hours <= 12, 0 <= minutes <= 59
/*** FIXED 10/11: ORIGINAL VERSION DIDN'T WORK FOR ALL CASES AND WAS FAR TOO CONVOLUTED ***/
/***  NEW VERSION DOES ALL MATH ON MILTIME AND THEN CORRECTS HOURS, MINUTES ***/
void Time::advance(unsigned h, unsigned m) {

	unsigned tempMT = h * 100 + m;		// Temporary miltime representing amount
												//   of time to advance by, since math
												 //   is much easier using miltime!

	// If sum of minutes >= 60, need to account for extra hour added
	if (minutes + m >= 60)
		miltime = (miltime + tempMT + 40) % 2400;	// % 2400 ensures time between 0 & 2359
															 //   (since minutes adjustment guarantees
															 //    last two digits < 60)
	else
		miltime = (miltime + tempMT) % 2400;

	// Convert back from miltime to new hours/minutes
	hours = miltime / 100;

	// Special case 1: time in PM (other than 12 PM)
	if (hours > 12)
		hours -= 12;

	// Special case 2: 12:xx AM --> miltime / 100 = 0
	else if (hours == 0)
		hours = 12;

	minutes = miltime % 100;

	// Figure out if new time is in AM or PM
	AMorPM = (miltime < 1200 ? 'A' : 'P');
}

// Returns true if calling object is less than argument
bool Time::lessThan(const Time& rhs) {
	if (miltime < rhs.miltime)
		return true;
	else
		return false;
}
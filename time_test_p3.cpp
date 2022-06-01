/*
 * EECE.3220: Data Structures
 * Instructor: M. Geiger
 *
 * time_test_p3.cpp: Main program to test Time class for Program 3
 */

#include "Time.h"
#include <iostream>
using namespace std;

// RunTestCases() handles all input and output for actual test cases
//   When running in submit mode, main() should only contain a call
//    to this function; leaving the call out of your main() function
//    allows you to run the program in develop mode and test your work
//    without worrying about the test cases
// Function definition can be found in RTC.cpp (which is read-only)
void RunTestCases();

int main() {
	RunTestCases();		// See function description above
						// Comment out/remove this function call if you want
						//   to write your own test code, but make sure your
						//   main() function only contains this function call
						//   when you're ready to run the program in submit mode
	return 0;
}
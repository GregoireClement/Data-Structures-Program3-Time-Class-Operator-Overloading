

#include "Time.h"
#include <iostream>
#include <string>
using namespace std;

// Print results of comparing 2 time objects (RunTestCases helper function)
void conditionTest(Time& T1, Time& T2) {
	cout << T1 << " == " << T2 << ": " << (T1 == T2 ? "true\n" : "false\n")
		<< T1 << " != " << T2 << ": " << (T1 != T2 ? "true\n" : "false\n")
		<< T1 << " < " << T2 << ": " << (T1 < T2 ? "true\n" : "false\n")
		<< T1 << " > " << T2 << ": " << (T1 > T2 ? "true\n" : "false\n");
}

// Print results of arithmetic operations 2 time objects (RunTestCases helper function)
// This function copies original Time objects so they aren't actually modified
void arithTest(const Time& T1ref, const Time& T2ref) {
	Time T1 = T1ref;
	Time T2 = T2ref;

	cout << T1 << " + " << T2 << " = " << T1 + T2 << '\n'
		<< T1 << " - " << T2 << " = " << T1 - T2 << '\n'
		<< T1 << " += " << T2 << " = ";
	T1 += T2;
	cout << T1 << '\n'
		<< T1 << " -= " << T2 << " = ";
	T1 -= T2;
	cout << T1 << "\n\n";
}

// RunTestCases() handles all input and output for actual test cases
//   When running in submit mode, main() should only contain a call
//    to this function; leaving the call out of your main() function
//    allows you to run the program in develop mode and test your work
//    without worrying about the test cases
void RunTestCases() {
	unsigned tCase;				// Number representing test case(s) to run
	string repeat;				// Indicates desire to repeat program

	// Standalone Time objects for testing
	Time T1(3, 35, 'P');
	Time T2(12, 17, 'A');
	Time T3(8, 0, 'A');
	Time T4(7, 6, 'P');

	do {
		cout << "\nWhich operators would you like to test?\n"
			<< "1 = input/output, 2 = comparisons,\n"
			<< "3 = arithmetic, 4 = pre-/post increment: ";
		cin >> tCase;

		switch (tCase) {
		case 1:				// >> and << operator tests
			cout << "<< and >> operator tests:\n";
			cout << "T1-T4 original values:\nT1: ";
			cout << T1;
			cout << "\nT2: " << T2;
			cout << "\nT3: " << T3 << "\nT4: " << T4 << '\n';
			cout << "Enter new time for T1: ";
			cin >> T1;
			cout << "Enter new times for T2 & T3: ";
			cin >> T2 >> T3;
			cout << "New times:\nT1: " << T1
				<< "\nT2: " << T2 << "\nT3: " << T3 << '\n';

			break;

		case 2:				// Comparisons: == != < >
			cout << "Relative operator tests\n";

			T3.set(3, 35, 'P');		// T1 & T3 now match
			T4.set(12, 17, 'P');	// T2 & T4 hrs and minutes match, but not AM/PM

			cout << "\nComparing T1 & T2:\n";
			conditionTest(T1, T2);

			cout << "\nComparing T2 & T3:\n";
			conditionTest(T2, T3);

			cout << "\nComparing T1 & T3:\n";
			conditionTest(T1, T3);

			cout << "\nComparing T2 & T4:\n";
			conditionTest(T2, T4);
			break;

		case 3:				// Arithmetic: + - += -=
			cout << "Arithmetic operator tests:\n";
			arithTest(T1, T2);
			arithTest(T3, T4);

			T3.set(4, 15, 'A');
			T4.set(3, 20, 'A');
			arithTest(T3, T4);

			T3.set(1, 15, 'P');
			T4.set(3, 20, 'P');
			arithTest(T3, T4);

			break;

		case 4:				// ++ operators (pre- and post-increment)
			cout << "Pre- and post-increment operator tests:\n";

			cout << "T1: " << T1;
			cout << "\nT1++ before increment: " << T1++;
			cout << ", and after increment: " << T1;

			cout << "\n++T1: " << ++T1;

			T1.set(11, 59, 'A');
			cout << "\n\nNow, T1: " << T1;
			cout << "\nT1++ before increment: " << T1++;
			cout << ", and after increment: " << T1;

			T1.set(11, 59, 'P');
			cout << "\n\nFinally, T1: " << T1;
			cout << "\n++T1: " << ++T1 << '\n';

			break;

		default:
			cout << "Invalid selection " << tCase << '\n';
		}

		do {
			cout << "Would you like to test more operators (yes/no)? ";
			cin >> repeat;

			if (repeat != "yes" && repeat != "no")
				cout << "Invalid response " << repeat << '\n';
		} while (repeat != "yes" && repeat != "no");

	} while (repeat == "yes");		// Return to start of function if user enters "yes"
}
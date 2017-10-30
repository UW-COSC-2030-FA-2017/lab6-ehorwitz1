// SortedDriver.cpp

// Erik Horwitz 10/30/2017

// Construct sorted sequences and call functions that 
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <set>


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	double diff;
	double nextDiff = 0;
	int next = 1;
	double prevDiff = 0;
	int prevNext = 0;
	double maxPrevDiff = 0;
	double maxNextDiff = 0;
	int maxDiffIndex=0;

	for (int i = 0; i < number.size()-1; i++)
	{
		diff = abs(number[i] - number[next]); 
		if (prevNext == 0)
		{
			prevDiff = abs(number[prevNext] - number[prevNext]);
		}
		else
		{
			prevDiff = abs(number[prevNext] - number[prevNext - 1]);
		}

		nextDiff = diff;

		if (prevDiff >= maxPrevDiff)
		{

			maxPrevDiff = prevDiff;
			maxDiffIndex = i;
		}
		else
		{
			maxNextDiff = abs(number[maxDiffIndex] - number[maxDiffIndex + 1]);
			if (maxNextDiff > nextDiff)
			{
				maxDiffIndex = maxDiffIndex;
			}
			else
			{
				maxDiffIndex = i;
			}
		}

		next++;
		prevNext++;
	}
	return number[maxDiffIndex];
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	int diff = 0;
	int indexDiff = A.size();


	
	auto it1 = A.begin();
	auto it2 = B.begin();



	while (it1 != A.end() && it2 != B.end())
	{


		if (*it1 > *it2) {


			

			it2++;
		}

		else if (*it1 == *it2) {
			it1++;
			indexDiff--;
		}
		else
		{
			it1++;
		}
		
		
	}

	return indexDiff;
}


int
main()
{

	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
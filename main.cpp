//A Merge Sort Implementation
// Written by Will Sumner in C++
#include <iostream> // for input
#include <time.h> //for timing
int size = 2; // initial list size
int listSize = 100; // max printable list size

// Random Number Generation Functions
int prettyGoodNumberGen (unsigned int value) //This is a pseudo random number generator, the results are predictable
// Its predictability is helpful in bug testing as the same output can be recovered by using the same input
{
	static unsigned int seed = value; //Static declares this number only ONCE, makes it a seed
	static long m = 4294967296; //Declare this number once as well, for efficiency
	seed = (71*seed) + 22695477; //Bordland LCG, basic form of this is x = (ax)+y
	int randNum = seed % m; // return the modulo of the number
	if (randNum < 0)
		randNum *= -1;

	return (randNum % 1000); //the modulo here outputs numbers 0 - 999
}

//Array Functions
void randomArray (int *newArray, int size,int numSeed) //Fills an array with random number
{
	int num = 0;
	for (int i = 0; i < size; i++)
	{ // A C++ for loop
		num = prettyGoodNumberGen(numSeed); // Generate a random number
		newArray[i] = num; // Add it to the list
	}
}
void emptyArray (int *array, int start, int end) //fills an array with 0's to help find bugs
{
	for (int i = start; i < end; i++)
	{
		array[i] = 0;
	}
}
void printArray (int *array,int start, int end) //Prints an array from predefined start to end
{
	if (end-start > 30){
		int length = end-start;
		int step = 20;
		int overlap = length % step;
		int div = (int) length/step;
		for (int i=start;i<div;i++)
		{
			for (int j = 0; j < step; j++)
			{
				if (array[(i*step)+j] < 10) { std::cout << "0"; }
				std::cout << array[(i*step)+j]<<" ";
			}
			std::cout <<"\n";
		}
		for (int i=end-overlap;i<=end;i++)
		{
			if (array[i] < 10) { std::cout << "0"; }
			std::cout << array[i] << " ";
		}
		std::cout << "\n";
	}

	else
	{
	for (int i=start;i<end;i++)
		std::cout << array[i] << " ";
	std::cout << array[end] << "\n";
	}
}

//Sorting Functions
void mergeStep (int *array,int *tempList,int start, int lengthOne, int lengthTwo) //the merge step of a merge sort
{
	// Only pointers to arrays can be passed, so the indices are set to the start of each list
	int i = start;
	int j = i+lengthOne;
	int k = 0; // index for the entire templist

	while (k < lengthOne+lengthTwo) // a C++ while loop
	{
		if (i - start == lengthOne)
		{ //list one exhausted
			for (int n = 0; n+j < lengthTwo+lengthOne+start;n++ ) //add the rest
			{
				tempList[k++] = array[j+n];
			}
			break;
		}

		if (j-(lengthOne+lengthTwo)-start == 0)
		{//list two exhausted
			for (int n = i; n < start+lengthOne;n++ ) //add the rest
			{
				tempList[k++] = array[n];
			}
			break;
		}

		if (array[i] > array[j]) // figure out which variable should go first
		{
			tempList[k] = array[j++];
		}

		else
		{
			tempList[k] = array[i++];
		}
		k++;
	}

	for (int s = 0; s < lengthOne+lengthTwo;s++) // add the templist into the original
	{
		array[start+s] = tempList[s];
	}
}
void sortStep (int *array, int length, int start, int end,int *tempList)
{
	if (length < 3)
	{
		if (length > 1){
			if (array[start] > array[end]){
				int temp = 0;
				temp = array[start];
				array[start] = array[end];
				array[end] = temp;
			}
		}
	}
	else
	{
		int mid = (int)(start+end)/2;//find mid
		sortStep(array,mid-start+1,start,mid,tempList); //left sort
		sortStep(array,end-mid,mid+1,end, tempList); // right sort
		mergeStep(array,tempList,start,mid-start+1,end-mid); // merge
	}
}

// Main Program
int main()
{
	std::cout << "Vanilla Merge Sort\n";
	while (size > 1)
	//just to start the looping, if size is less than one the program will exit before this condition is checked
	{
		std::cout << "Please enter the length of the list: ";
		std:: cin >> size;
		if (size <= 1)
		{
			std::cout << "\nExiting...";
			return (0); //Anything less than 1 will end the program (also to protect it)
		}

		std::cout << "Allocating array memory...";
		int *testArray = new int[size]; //original list
		int *tempList = new int[size]; //sorting list
		std::cout << "Done\nGenerating random numbers...";
		randomArray(testArray,size,31415); //fill list with random numbers
		std::cout << "Done\n";
		std::cout << "Sorting...";
		std::cout <<" ";
		if (size<=listSize)
		{
			std::cout << "Original list: \n";
			printArray(testArray,0,size-1);
		}


		float x = clock(); //timing
		sortStep(testArray,size,0,size-1,tempList); //Call sort
		float y = clock() - x; //timing
		std::cout << "Done \n\nIt took " << y/CLOCKS_PER_SEC << " seconds to sort the list of " << size << " items, and " << y << " clocks. \n";
		if (size<=listSize)
		{
			std::cout << "Sorted list: \n";
			printArray(testArray,0,size-1);
		}
		std::cout << "\n";

		// Memory Cleanup
		delete[] testArray;
		testArray = 0;
		delete[] tempList;
		tempList = 0;
	}
	return (0);
}

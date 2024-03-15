//Muhammad Masab Hammad 
//22I-1004


#include"DataAnalyzer.h"

int main()
{
	DataAnalyzer obj("data.csv");											//DataAnalyzer object

	cout << "---- Data Analyzer Object Created ----" << endl;
	cout << "----	  CSV File Provided       ----" << endl << endl;

	cout << "1. Mean: ";
	cout << obj.getMean();													//functions called to test the DataAnalyzer class
	cout << endl;															//results printed
	cout << endl;

	cout << "2. Median: ";
	cout << obj.getMedian();
	cout << endl;
	cout << endl;

	cout << "3. Mode: ";
	cout << obj.getMode();
	cout << endl;
	cout << endl;

	cout << "4. Standard Deviation: ";
	cout << obj.getStandardDeviation();
	cout << endl;
	cout << endl;

	cout << "5. Variance: ";
	cout << obj.getVariance();
	cout << endl;
	cout << endl;

	int choice;

	cout << "Choose a Sorting Algorithm: " << endl;
	cout << "1. Bubble Sort" << endl;
	cout << "2. Insertion Sort" << endl;
	cout << "\nEnter your choice: ";
	cin >> choice;
	cout << endl;

	if (choice == 1)												//method of sorting depending on choice
	{
		obj.bubbleSort(obj.getDataArray(), obj.getArraySize());
	}

	else if (choice == 2)
	{
		obj.insertionSort(obj.getDataArray(), obj.getArraySize());
	}

	else
	{
		cout << "Invalid Choice" << endl;
	}

	obj.printDataArray();													//sorted array printed

	int val;

	cout << "\nEnter a value to search: ";
	cin >> val;

	int index = obj.binarySearch(obj.getDataArray(), 0, obj.getArraySize() - 1, val);    //index of the key found

	if (index == -1)																	//index returns -1, if value not found
	{
		cout << "Value not found" << endl;
	}

	else
	{
		cout << "Value " << val << " found at Index " << index << endl;

	}

	return 0;
}
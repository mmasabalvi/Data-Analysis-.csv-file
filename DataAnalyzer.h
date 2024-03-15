//Muhammad Masab Hammad 
//22I-1004


#include<iostream>
#include<string>
#include<fstream>
#include <cmath>
using namespace std;

class DataAnalyzer
{
private:
	int* dataArray;												//array for storing data
	int arraySize;												//for storing size

public:

	DataAnalyzer(const string& fileName)
	{
		ifstream file(fileName);							//file open now


		string line;										//to store each line of the file
		int num = 0;										//to store the number of lines = number of elements

		getline(file, line);								//file header ignored ("Data DS")

		while (getline(file, line))							//loop will work until all lines read
		{													//after each getline, file ptr points to next line
			num++;											//'line' variable overwritten each time - num incremented
		}

		dataArray = new int[num];								//array provided size num
		arraySize = num;

		file.clear();
		file.seekg(0, ios::beg);


		getline(file, line);								//file header ignored ("Data DS")

		for (int i = 0; i < num; i++)
		{
			getline(file, line);							//data read each time and stored in 'line'
			//cout << "Line " << i + 2 << ": " << line << endl;
			dataArray[i] = stoi(line);							//stoi converts data from string to int and stores in array
		}

		file.close();										//file closed
	}


	int getArraySize() const
	{
		return arraySize;										//getter for size
	}

	int* getDataArray() const
	{
		return dataArray;										//getter for array
	}

	void printDataArray()
	{
		for (int i = 0; i < arraySize; i++)
		{
			cout << dataArray[i] << ", ";						//void function to print array
		}

		cout << endl;
	}

	float getMean()
	{
		//int size = sizeof(array) / sizeof(array[0]);

		int sum = 0;

		for (int i = 0; i < arraySize; i++)
		{
			sum += dataArray[i];								//firstly, array is summed
		}

		float average = static_cast<double>(sum) / arraySize;    //then sum divided by number of elements

		return average;										//average returned
	}

	float getMedian()
	{
		int temp;											//array sorted first using bubble sort

		for (int i = 0; i < arraySize; i++)
		{
			for (int j = 0; j < arraySize - i - 1; j++)
			{
				if (dataArray[j] > dataArray[j + 1])				//if next element smaller than current - swapped
				{
					temp = dataArray[j];
					dataArray[j] = dataArray[j + 1];
					dataArray[j + 1] = temp;
				}
			}
		}
															//array sorted
		float median;									

		if (arraySize % 2 == 0)									//size of array checked
		{
			int x1 = arraySize / 2;								//if even num of elements, mean of middle 2 elements is median
			int x2 = (arraySize / 2) + 1;

			median = (dataArray[x1 - 1] + dataArray[x2 - 1]) / 2;
		}

		else
		{
			int x = arraySize / 2;								//if odd num of elements, middle element is median

			median = dataArray[x];
		}

		return median;

	}

	float getMode()
	{
		int mode = 0;										//to store mode
		int maxFreq = 0;									//count for max Frequency

		for (int i = 0; i < arraySize; i++)
		{
			int num = dataArray[i];
			int frequency = 0;

			for (int j = 0; j < arraySize; j++)					//each element checked with rest of Array
			{
				if (num == dataArray[j])						//if repeated, than frequency inceremented
				{
					frequency++;
				}
			}

			if (frequency > maxFreq)						
			{
				maxFreq = frequency;						//element with maxFrequency stored as mode
				mode = num;
			}
		}

		return mode;
	}

	float getStandardDeviation()
	{
		int sum = 0;

		for (int i = 0; i < arraySize; i++)
		{
			sum += dataArray[i];
		}

		float average = static_cast<double>(sum) / arraySize;	//Average calculated first

		float temp;
		float diff = 0;

		for (int i = 0; i < arraySize; i++)
		{
			temp = dataArray[i] - average;						//Average subtracted from each Datapoint
			temp *= temp;									//square of values taken
			diff += temp;									//values added
		}

		float dev = sqrt(diff / arraySize);						//square root of values over size is StandardDeviation

		return dev;
	}

	float getVariance()
	{
		int sum = 0;

		for (int i = 0; i < arraySize; i++)
		{
			sum += dataArray[i];
		}

		float average = static_cast<double>(sum) / arraySize;	//Average calculated first

		float temp;
		float diff = 0;

		for (int i = 0; i < arraySize; i++)
		{
			temp = dataArray[i] - average;						//Average subtracted from each Datapoint
			temp *= temp;									//square of values taken
			diff += temp;									//values added
		}

		float var = diff / arraySize;							//values over size is variance

		return var;
	}

	int* bubbleSort(int* arr, int size)
	{
		int temp;											//Simple Bubble Sort Algo

		for (int i = 0; i < size; i++)						//after each iteration, max value set at last address considered
		{
			for (int j = 0; j < size - i - 1; j++)
			{
				if (arr[j] > arr[j + 1])				  //if next element smaller than current - swapped
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}

		return arr;
	}

	int* insertionSort(int* arr, int size)
	{
		int j;

		for (int i = 1; i < size; i++)						//Index from 1, as array[0] considered sorted
		{
			int temp = arr[i];

			for (j = i; j > 0 && temp < arr[j - 1]; j--)		//condition fulfilled if next element < current
			{
				arr[j] = arr[j - 1];						//element swapped
			}

			arr[j] = temp;									//new element kept at previous index
		}

		return arr;
	}

	int binarySearch(int* arr, int left, int right, int key)
	{
		int index = -1;											//to store index of key
		bool found = 0;											//true if found - breaks

		while (left <= right)
		{
			int mid = (left + right) / 2;						//half of start and end

			if (dataArray[mid] == key)								//if found, then index set and breaks
			{
				index = mid;
				found = 1;
				break;
			}

			else if (dataArray[mid] > key)							//if mid value larger, then key at left
			{
				right = mid - 1;									//end set to mid-1
			}

			else                                               //if mid value smaller, then key at right
			{
				left = mid + 1;							  //start set to mid+1
			}
		}

		return index;

	}



	
};

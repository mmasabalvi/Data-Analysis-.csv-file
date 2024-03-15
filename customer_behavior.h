


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class CustomerBehavior 
{
private:

    //2-D Array to store Data
    float** dataArray;

public:

    CustomerBehavior()
    {
        const int rows = 1000;
        const int cols = 5;

        // Allocate memory for the 2D array
        dataArray = new float* [rows];

        for (int i = 0;i < rows;i++) 
        {
            dataArray[i] = new float[cols];
        }

    }

    // Read data from a csv file to the dataArray
    void readData(string filename) 
    {
        //File opened
        ifstream file(filename);

        //rows and cols declared
        const int rows = 1000;
        const int cols = 5;

        string line;                                                                    //to read lines from file
        getline(file, line);                                                            //first line containing header ignored

        for (int row = 0; getline(file, line); row++)                                   //loop works until all lines read
        {
            size_t pos = 0;                                                             //position declared for substring
            int col = 0;                                                                //col declared outside for last column excpetion case

            for (; (pos = line.find(',')) != string::npos; col++)                       //find() searches for ',' i.e delimiter b/w data points
            {                                                                           //if ',' found, then loop works - pos given ',' index
                string check = line.substr(0, pos);                                     //substring extracted from first postion till comma
                                                                                        //one datapoint stored in check
                try
                {
                    dataArray[row][col] = stof(check);                                  //try block tries to read check
                }                                                                       //converting to float

                catch (const invalid_argument& e)                                       //invalid_arguments error when function passed wrong parameters
                {                                                                       //this means datapoint was empty and stof() unable to read it
                    dataArray[row][col] = 0;                                            //so speicifc index given 0.0 if no data present
                }

                line.erase(0, pos + 1);                                                 //current datapoint erased from line
            }                                                                           //for next iteration, line shortened and new datapoint stored in check 

            if (col < cols)                                                             //this condition to specifically check the last column
            {                                                                           //used as inner loop terminates when no new commas found
                try                                                                     //so last column may remain unchecked
                {
                    dataArray[row][col] = stof(line);                                   //same principle of storing and checking for exception applied here
                }
                catch (const invalid_argument& e)
                {
                    dataArray[row][col] = 0;
                }
            }
        }
        this->dataArray = dataArray;


        file.close();                                                                   //file closed as all data read
                                                                                        //getline(file, line) condition terminates

        //for (int i = 0; i < 1000; i++)                                                //for testing purposes
        //{
        //    for (int j = 0; j < 5; j++)
        //    {
        //        cout << dataArray[i][j] << " ";
        //    }

        //    cout << endl;
        //}

    }


    // Calculate the correlationCoefficient of the x and y columns
    double correlationCoefficient(int x, int y)                                         //Formula for slope is used 
    {
        double sumX = 0;                                                                //sum of one col
        double sumY = 0;                                                                //sum of other col

        for (int i = 0;i < 1000;i++)
        {
            sumX += dataArray[i][x];                                                    //columnX summed
            sumY += dataArray[i][y];                                                    //columnY summed
        }

        double meanX = sumX / 1000;                                                     //mean of Y and X calculated

        double meanY = sumY / 1000;

        double tempX, tempY, temp;                                                      //variables used in calculation of numerator and denominator

        double num = 0;
        double dem1 = 0;
        double dem2 = 0;                                                                //Pearson Formula used for correlation analysis

        for (int i = 0; i < 1000; i++)
        {
            tempX = dataArray[i][x] - meanX;                                            //mean subtracted from each data point 
            tempY = dataArray[i][y] - meanY;                                            //For both X and Y

            num += tempX * tempY;                                                       //Numerator is sum of product of difference of X and Y

            dem1 += tempX * tempX;                                                      //denominator 1 is sum of product of X individually
            dem2 += tempY * tempY;                                                      //denominator 2 is sum of product of Y individually
        }

        double corelation = num / sqrt(dem1 * dem2);                                    //Overall denominator is product of both squared

        return corelation;                                                              //correlation returned

    }

    // Function to calculate the slope (beta1) of the regression line
    // Calculate the slope of the regression line of the x and y columns
    double slope(int x, int y) 
    {
        double sumX = 0;                                                                //sum of one col
        double sumY = 0;

        for (int i = 0; i < 1000; i++)
        {
            sumX += dataArray[i][x];                                                    //columnX summed
            sumY += dataArray[i][y];                                                    //columnY summed
        }

        double meanX = sumX / 1000;                                                     //mean of Y and X calculated

        double meanY = sumY / 1000;

        double tempX, tempY;                                                           //variables used in calculation of numerator and denominator

        double dem = 0;

        double num = 0;

        for (int i = 0; i < 1000; i++)
        {
            tempX = dataArray[i][x] - meanX;                                            //mean subtracted from each data point 
            tempY = dataArray[i][y] - meanY;                                            //For both X and Y

            dem += tempX * tempX;                                                       //Denominator is sum of square of sum of difference of datapoint X and its mean

            num += tempX * tempY;                                                       //Numerator is sum of product of difference of datapoint X and its mean and
                                                                                        //difference of datapoint Y and its mean 
        }

        double slope = num / dem;

        return slope;
    }

    // Function to calculate the y-intercept (beta0) of the regression line
    // Calculate the y-intercept of the regression line of the x and y columns
    double calculateIntercept(int x, int y, double slope) 
    {
        double sumX = 0;                                                                //sum of one col
        double sumY = 0;

        for (int i = 0; i < 1000; i++)
        {
            sumX += dataArray[i][x];                                                    //columnX summed
            sumY += dataArray[i][y];                                                    //columnY summed
        }

        double meanX = sumX / 1000;                                                     //mean of Y and X calculated

        double meanY = sumY / 1000;

        double intercept = meanY - (meanX * slope);                                     //equation: y = intercept + x(slope)
                                                                                        // so: intercept = y - x(slope)
        return intercept;
    }


    // Function to calculate the distance between two points
    // Calculate the distance between two points

    double distance(double x1, double y1, double x2, double y2)                         //using the simplest formula for distance
    {                                                                                   // d = square root of [(x2-x1)^2 + (y2-y1)^2]
        double numX = x2 - x1;
        numX *= numX;                                                                   //Difference between x squared

        double numY = y2 - y1;
        numY *= numY;                                                                   //Difference between y squared
            
        double distance = sqrt((numY + numX));                                          //Differences added, square root taken

        return distance;
    }

    // Function to calculate the centroids of the clusters
    // Calculate the centroids of the clusters
    // Print the centroids of the clusters

    void kMeansClustering(double x1, double y1, double x2, double y2, double x3, double y3, int col1, int col2)
    {
        double center[3][2] = { x1, y1, x2, y2, x3, y3 };                                                       //user has provided us with centroids and columns
                                                                                                                //centroids x and y values put in Array
        int s1 = 0;                                                                                             //count for the number of data points   
        int s2 = 0;                                                                                             //in each cluster
        int s3 = 0;                                                                                             //will be used to calculate mean

        bool converge = false;                                                                                  //K-means clustering works until the new clusters converge
        int max = 10;                                                                                           //or until max iterations are reached, 10 set for now
        int num = 0;                                                                                            //variable to hold current iteration

        while (converge == false && num < max)                                                                  //loop runs if centroid not converged and max iterations not reached
        {
            double SumofCluster1[2] = { 0 };                                                                    //Sum of Clusters required for Mean
            double SumofCluster2[2] = { 0 };                                                                    //Array of 2 declared to store x and y values both
            double SumofCluster3[2] = { 0 };

            for (int i = 0; i < 1000; i++)                                                                      //loop for number of rows
            {
                double minDistance = numeric_limits<double>::max();                                             //min distance set the highest for the first iteration
                                                                                                                //so if block can run to store new value in min Distance
                int nearestCluster;                                                                             //to hold nearest cluster for each data point

                for (int j = 0; j < 3; j++)
                {
                    double dist = distance(dataArray[i][col1], dataArray[i][col2], center[j][0], center[j][1]); //For each centroid loop runs individually
                                                                                                                //distance between each data point and each centroid found
                    if (dist < minDistance)                                                                     //if distance is smaller than previous calculated distance for some other centroid
                    {                                                                                           //then nearest cluster set as the new cluster with min distance
                        minDistance = dist;                                                                     
                        nearestCluster = j;
                    }

                    if (nearestCluster == 0)                                                                    //operations for each cluster
                    {                                                                                           //if specific cluster given to a data point
                        SumofCluster1[0] += dataArray[i][col1];                                                 //then data point added in array of Sum of specific Cluster
                        SumofCluster1[1] += dataArray[i][col2];                                                 //Size of cluster increased
                        s1++;                                                                                   //Both variables will be used in calculating mean
                    }
                    else if (nearestCluster == 1)
                    {
                        SumofCluster2[0] += dataArray[i][col1];
                        SumofCluster2[1] += dataArray[i][col2];
                        s2++;
                    }
                    else
                    {
                        SumofCluster3[0] += dataArray[i][col1];
                        SumofCluster3[1] += dataArray[i][col2];
                        s3++;
                    }
                }

                converge = true; // Assume convergence              

                for (int j = 0; j < 3; ++j)                                                                     //loop to calculate mean for each cluster
                {                                                                                               //and replace old centroid with new one, if not converged
                    double originalX = center[j][0];                                                            //original centroids set
                    double originalY = center[j][1];

                    double newX, newY;                                                                          //new centroids declared

                    if (j == 0)
                    {
                        newX = SumofCluster1[0] / s1;                                                           //new centroids calculated by mean of each cluster
                        newY = SumofCluster1[1] / s1;                                                           //calculated for both x and y
                    }
                    else if (j == 1)                                                                            //each iteration refers to a different cluster
                    {
                        newX = SumofCluster2[0] / s2;
                        newY = SumofCluster2[1] / s2;
                    }
                    else
                    {
                        newX = SumofCluster3[0] / s3;
                        newY = SumofCluster3[1] / s3;
                    }

                    if (newX != originalX || newY != originalY)                                                 //if new centroid are not equal to previous one
                    {                                                                                           //converge set as false
                        converge = false;                                                                       //whole process repeated again until all centroids have converged   
                    }

                    center[j][0] = newX;                                                                        //after each iteration, Centroids updated
                    center[j][1] = newY;
                }

                num++;                                                                                          //iteration incremented

            }

        }

        cout << "Final Clusters: " << endl;

        for (int i = 0; i < 3; i++)
        {
            cout << "Cluster " << i + 1 << ":          x = " << center[i][0] << "     y = " << center[i][1] << endl;
        }
    }
};
 

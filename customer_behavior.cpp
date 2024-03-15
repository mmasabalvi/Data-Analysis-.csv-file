
#include "customer_behavior.h"


int main() {

	// Create an object of CustomerBehavior class
	CustomerBehavior obj;

	cout << "--- Customer Behavior Object Created ---" << endl << endl;

	obj.readData("customer_behavior.csv");																//data read from csv and stored in 2D array

	cout << "# Function readData() used to store Data Values in 2-D Array" << endl << endl;

	int x, y;
	cout << "# Enter the column indexes for which Correlation Coefficient is required:  " << endl;
	cin >> x >> y;																						//indexes of both columns for correlation analysis

	double coeff = obj.correlationCoefficient(x, y);													//correlation returned from function stored

	cout << "\n# Correlation Coefficient is: " << coeff << endl << endl;

	cout << "# Correlation Matrix: " << endl;															//Correlation Matrix of 2 variables is 2x2
																										//point[0][0] and point[1][1] always 1
	cout << " ------       ------" << endl;																//show perfect relationship of each col with itself
	cout << "| 1" << "      " << coeff;
	cout << "  | " << endl;																				//point[0][1] and point[1][0] is typically the coefficient
	cout << "| " << coeff;
	cout << "       1 |" << endl;
	cout << " ------       ------" << endl << endl;

	cout << "The Correlation Coefficient and Matrix show ";												//Analysis done from Coefficient shown depending on ranges

	if (coeff == 1)
	{
		cout << "a perfect positive linear relationship between the variables" << endl;
		cout << "If one variable increases, the other increases propotionally" << endl;
	}

	else if (coeff == -1)
	{
		cout << "a perfect negative linear relationship between the variables" << endl;
		cout << "If one variable increases, the other decreases" << endl;
	}

	else if (abs(coeff)>0.8)
	{
		cout << "a strong linear relationship between the variables" << endl;
	}

	else if (abs(coeff) <= 0.3)
	{
		cout << "a very weak linear relationship between the variables" << endl;
	}

	else if (abs(coeff) > 0.5 && abs(coeff) <= 0.8)
	{
		cout << "a moderate linear relationship between the variables" << endl;
	}

	else if(abs(coeff) > 0.3 && abs(coeff) <= 0.5)
	{
		cout << "a moderate linear relationship between the variables" << endl;
	}

	cout << endl << endl;

	int a, b;
	cout << "# Enter the column indexes for which Linear Regression is required:  " << endl;
	cin >> a >> b;

	double slope = obj.slope(a, b);

	cout << "\n# Equation: y = beta0 + x(beta1)" << endl;
	cout << "beta0 - Intercept" << endl;
	cout << "beta1 - Slope" << endl;

	cout << "\n-> Slope of Regression Line is: " << slope << endl;

	double intercept = obj.calculateIntercept(a, b, slope);

	cout << "-> Intercept of Regression Line is: " << intercept << endl;

	cout << endl << "# Enter the column indexes for which K-Means Clustering is required: " << endl;
	cin >> a >> b;

	double x1, x2, x3, y1, y2, y3;

	cout << "# Enter datapoints in the format: x1, y1, x2, y2, x3, y3" << endl;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

	cout << endl;

	obj.kMeansClustering(x1, y1, x2, y2, x3, y3, a, b);
	


}

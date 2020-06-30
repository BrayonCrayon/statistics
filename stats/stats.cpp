//Braydon Deroy
//Calculates statistics of a user inputed data set or a text file data input
//Feb 8th 2015

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <iomanip>
#include <locale>

using namespace std;

//Calculate median function
double MedianCalc(vector<double>);
//Calculate mean function
double MeanCalc(vector<double>);
//Calculate mode function
vector<double> ModeCalc(vector<double>);
//Absolute Deviation
double MeanAbsDev(vector<double>, double);
double MedianAbsDev(vector<double>, double);
double ModeAbsDev(vector<double>, double);
//Vraiance 
double Variance(vector<double>);
//standard deviation 
double StandDev(double variance);
//Frequency Distribution
void FrequencyDis(vector<double>, double, double);
//Qunitile 
void Quintile(vector<double>);
//Outliers
void Outliers(vector<double>, double, double);
//print formattors
void printfComma(double);
void printfComma2(double);
int main()
{
	//Thousands seperator
	struct seperator : numpunct < char >
	{
	protected:
		virtual char do_thousands_sep() const override { return ','; }
		virtual string do_grouping() const override { return "\03"; }
	};
	cout.imbue(locale(cout.getloc(), new seperator));

	//getting input from the user for data
	cout << "Stats, " << char(69) << "2015-2-20 Braydon Deroy" << endl;
	cout << "Enter a white space seperated data values terminated by ^Z\n" << endl;
	vector<double> statsicValues;
	double i;

	while (cin >> i)
		statsicValues.push_back(i);

	cout << "\nResults: " << endl;
	sort(statsicValues.begin(), statsicValues.end());
	//size of array 
	cout << "N = " << statsicValues.size() << endl;

	if (statsicValues.size() == 0)
		cout << "Empty data set!" << endl;
	else
	{
		//mininum value
		double minValue = *(min_element(statsicValues.begin(), statsicValues.end()));
		cout << "Min = " << fixed << setprecision(3) << minValue << endl;

		//maximum value
		double maxValue = *(max_element(statsicValues.begin(), statsicValues.end()));
		cout << "Max = " << fixed << setprecision(3) << maxValue << endl;

		//arithmetic mean
		double mean = MeanCalc(statsicValues);
		cout << "Arithmatic mean = " << fixed << setprecision(3) << mean << endl;

		//median value
		double median = MedianCalc(statsicValues);
		cout << "Statistical median = " << fixed << setprecision(3) << median << endl;

		//mode
		vector<double> mode = ModeCalc(statsicValues);
		if (mode.size() > 1 && mode.size() < statsicValues.size())
		{
			cout << "Mode = " << "{ ";
			for (auto x : mode)
				cout << fixed << setprecision(3) << x << ", ";
			cout << " }" << endl;
		}
		else if (mode.size() == 0)
			cout << "Mode = No mode" << endl;
		else if (mode.size() == 1)
		{
			cout << "Mode = " << "{ ";
			for (auto x : mode)
				cout << fixed << setprecision(3) << x;
			cout << " }" << endl;
		}
		else if (mode.size() == statsicValues.size())
			cout << "Mode = No mode" << endl;
		//absolute deviation
		//mean absolute devation
		double meanAbsDev = MeanAbsDev(statsicValues, mean);
		cout << "Mean absolute deviation = " << fixed << setprecision(3) << meanAbsDev << endl;
		//median absolute deviation
		double medianAbsDev = MedianAbsDev(statsicValues, median);
		cout << "Median absolute deviation = " << fixed << setprecision(3) << medianAbsDev << endl;
		//mode absolute deviation
		if (mode.size() == 1)
			cout << "Mode absolute deviation = " << fixed << setprecision(3) << ModeAbsDev(statsicValues, mode[0]) << endl;
		else
			cout << "Mode absolute deviation = " << "N/A <no unique mode>" << endl;


		//variance
		double variance = Variance(statsicValues);
		cout << "Variance = " << fixed << setprecision(3) << variance << endl;

		//standard deviation
		double standardDev = StandDev(variance);
		cout << "Standard Deviation = " << fixed << setprecision(3) << standardDev << endl;

		cout << endl;
		//frequency distribution
		FrequencyDis(statsicValues, minValue, maxValue);

		cout << endl;
		//Quintile
		cout << "Quintile means" << endl;
		if (statsicValues.size() < 5)
			cout << "\nNo quintiles to compute, thee are less than 5 samples." << endl;
		else
			Quintile(statsicValues);

		cout << endl;
		//outlier report
		cout << "\nOutliers" << endl;
		cout << "--------" << endl;
		Outliers(statsicValues, mean, standardDev);

	}
}

//calculates the median of a vector of any size.
//it takes in a vector that the user inputed
//returns a calculated value of double 
double MedianCalc(vector<double> data)
{
	double median = 0;
	double num1 = 0, num2 = 0;
	//calculates the median value of the data.
	if (data.size() % 2 == 0)
	{
		num1 = (data[((data.size() - 1) / 2)]);
		num2 = (data[((data.size() - 1) / 2) + 1]);
		median = (num1 + num2) / 2;
	}
	else
		median = data[data.size() / 2];
	return median;
}

//calculates the mean of a vector of any size.
//Takes in the vector that the user inputed
// reurns a calculated value of double 
double MeanCalc(vector<double> data)
{
	double sum = 0;
	//sum up the valuse to calculate the mean value
	for (auto x : data)
		sum += x;
	double mean = sum / data.size();
	return mean;
}

//calculates the mode of a vector of any size
//Takes in the vector that the user inputed
//returns a calculated value of a vector
vector<double> ModeCalc(vector<double> data)
{
	double count = 1;
	//fill the map with the data the user inputted
	map<double, double> mInt;
	for (auto x : data)
		++mInt[x];
	vector<double> mode;
	map<double, double>::iterator it = mInt.begin();
	//go through the map and make count the most frequent number
	for (it = mInt.begin(); it != mInt.end(); ++it)
		if (it->second > count)
			count = it->second;
	//go through the map and put the frequent numbers into a mode vector
	for (it = mInt.begin(); it != mInt.end(); ++it)
		if (it->second == count)
			mode.push_back(it->first);
	//if in a special case erase the vector
	if (mode.size()*count == data.size())
		mode.erase(mode.begin(), mode.end());
	return mode;
}

// calculates the Mean Absolute Deviation 
// takes in the user input and the mean of a fuction
// returns a calculated value of double
double MeanAbsDev(vector<double> data, double mean)
{
	double meanAbs = 0;
	double sum = 0;
	//sum up the data and find the absolute value for the Mean Absolute Deviation
	for (auto x : data)
		sum += abs(x - mean);
	return 	meanAbs = (sum / data.size());
}

// calculates the Median Absolute Deviation 
// takes in the user input and the median of a fuction
// returns a calculated value of double
double MedianAbsDev(vector<double> data, double median)
{
	double medianAbs = 0;
	double sum = 0;
	// sum up the data and find the absolute value for the median Absolute Deviation
	for (auto x : data)
		sum += abs(x - median);
	return medianAbs = (sum / data.size());
}

// calculates the Mode Absolute Deviation
// takes in the user input data and the mode of a fuction
// returns a calculated value if double 
double ModeAbsDev(vector<double> data, double mode)
{
	double modeAbs = 0;
	double sum = 0;
	// sum up the data and find the absolute value for the Mode Absolute Deviation
	for (auto x : data)
		sum += abs(x - mode);
	return modeAbs = (sum / data.size());
}

//calculates the Variance of any vector
// takes in the user input data
// returns a calculated value of double
double Variance(vector<double> data)
{
	long double variance = 0;
	double expValue = 0;
	//fill the data into the map
	map<double, double> mInt;
	for (auto x : data)
		++mInt[x];
	//go through the map and sum up the expected value
	for (map<double, double>::iterator it = mInt.begin(); it != mInt.end(); ++it)
		expValue += (it->first * (it->second / data.size()));
	//got through the map and sum up the variance
	for (map<double, double>::iterator it = mInt.begin(); it != mInt.end(); ++it)
		variance += pow((it->first - expValue), 2) * (it->second / data.size());
	return variance;
}

//calculates the standar deviation of any vector
// takes a double calculated variable 
// returns a calculated double 
double StandDev(double variance)
{
	//calculate the standard deviation 
	double standardDev = 0;
	standardDev = sqrt(variance);
	return standardDev;
}

//does a frequency distribution with a given vector
// takes a the user input data, the min value and the max value
// it returns nothing and prints out
void FrequencyDis(vector<double> data, double min, double max)
{
	double range = min;
	double addRange = (max - min) / 10;
	double freqNum = 0;
	float freqNum2 = 0.00;
	double percentage = 0;
	map<double, double> frequency;
	//filling up the map
	for (auto x : data)
		++frequency[x];
	map<double, double>::iterator it = frequency.begin();
	//going through a loop ten times to print the frequency distribution
	for (int i = 0; i < 10; ++i, range += addRange)
	{
		freqNum = 0;
		percentage = 0;
		//go through the map and iterate the frequency and percentage
		for (map<double, double>::iterator point = frequency.begin(); point != frequency.end(); ++point)
		{
			if (point->first >= range && point->first < (range + (addRange)))
			{
				++freqNum;
				++percentage;
				if (point->second > 1)
				{
					for (int i = 1; i < point->second; ++i)
					{
						++freqNum;
						++percentage;
					}
				}
			}
		}
		//print out the frequency distribution
		if (freqNum > 0)
		{
			addRange *= 1.01;
			cout << "[" << setw(6) << fixed << setprecision(2) << range << ".." << setw(6) << setprecision(2) << (range + addRange) << "> =" << setw(2) << setprecision(0) << freqNum << setw(2) << ":" << setw(5) << setprecision(2) << (percentage / data.size()) << endl;
		}
		else
			cout << "[" << setw(6) << fixed << setprecision(2) << range << ".." << setw(6) << setprecision(2) << (range + addRange) << "> =" << setw(2) << setprecision(0) << "0" << setw(2) << ":" << setw(5) << setprecision(2) << (freqNum2 / data.size()) << endl;
	}
}

//Does a quntile calculate of the data set
// takes in the user input 
// returns nothing but prints the data set
void Quintile(vector<double> data)
{
	sort(data.begin(), data.end());
	vector<int> quinInter;
	for (int i = 0; i < 6; ++i)
		quinInter.push_back(int(floor(data.size()*(i / 5.0))));
	//makes 5 vectors for filling quintile means
	vector<double> Quin1;
	vector<double> Quin2;
	vector<double> Quin3;
	vector<double> Quin4;
	vector<double> Quin5;
	int iterQuin = 0;
	int i = 0;
	//filling the quintile means with data
	for (int j = 0; j < data.size(); ++j)
	{
		if (j >= quinInter[iterQuin] && j < quinInter[(iterQuin + 1)])
			Quin1.push_back(data[j]);
		else if (j >= quinInter[iterQuin + 1] && j < quinInter[(iterQuin + 2)])
			Quin2.push_back(data[j]);
		else if (j >= quinInter[iterQuin + 2] && j < quinInter[(iterQuin + 3)])
			Quin3.push_back(data[j]);
		else if (j >= quinInter[iterQuin + 3] && j < quinInter[(iterQuin + 4)])
			Quin4.push_back(data[j]);
		else if (j >= quinInter[iterQuin + 4] && j < quinInter[(iterQuin + 5)])
			Quin5.push_back(data[j]);
	}
	//sending the quntile mean vectors to calculate the mean
	double quinMean1 = MeanCalc(Quin1);
	double quinMean2 = MeanCalc(Quin2);
	double quinMean3 = MeanCalc(Quin3);
	double quinMean4 = MeanCalc(Quin4);
	double quinMean5 = MeanCalc(Quin5);
	//Outputting the quintile means
	cout << "Q" << (i + 1) << ":" << setw(6) << fixed << setprecision(3) << quinMean1 << setw(2) << "[" << quinInter[i] << ".." << quinInter[i + 1] << ")" << endl;
	cout << "Q" << (i + 2) << ":" << setw(6) << fixed << setprecision(3) << quinMean2 << setw(2) << "[" << quinInter[i + 1] << ".." << quinInter[i + 2] << ")" << endl;
	cout << "Q" << (i + 3) << ":" << setw(6) << fixed << setprecision(3) << quinMean3 << setw(2) << "[" << quinInter[i + 2] << ".." << quinInter[i + 3] << ")" << endl;
	cout << "Q" << (i + 4) << ":" << setw(6) << fixed << setprecision(3) << quinMean4 << setw(2) << "[" << quinInter[i + 3] << ".." << quinInter[i + 4] << ")" << endl;
	cout << "Q" << (i + 5) << ":" << setw(6) << fixed << setprecision(3) << quinMean5 << setw(2) << "[" << quinInter[i + 4] << ".." << quinInter[i + 5] << ")" << endl;

}

//This fuctions determines if any out liers are in any given data set
//takes in the user data , the mean and the standarad deviation
// returns nothing but print the outlier
void Outliers(vector<double> data, double mean, double standard)
{
	//four variables for deviations
	double threeBelow = 0;
	double twoBelow = 0;
	double twoAbove = 0;
	double threeAbove = 0;
	//increment the deviations of the data set
	for (auto x : data)
	{
		if (x <= (mean - (standard * 3)))
			++threeBelow;
		else if (x >= (mean + (standard * 3)))
			++threeAbove;
		else if (x <= (mean - (standard * 2)))
			++twoBelow;
		else if (x >= (mean + (standard * 2)))
			++twoAbove;
	}
	//print out the outliers 
	cout << "<= 3 dev above: " << setprecision(0) << threeAbove << setw(2) << "(" << setprecision(2) << (threeAbove / data.size()) * 100 << "%)" << endl;
	cout << "<= 2 dev above: " << setprecision(0) << twoAbove << setw(2) << "(" << setprecision(2) << (twoAbove / data.size()) * 100 << "%)" << endl;
	cout << ">= 2 dev below: " << setprecision(0) << twoBelow << setw(2) << "(" << setprecision(2) << (twoBelow / data.size()) * 100 << "%)" << endl;
	cout << ">= 3 dev below: " << setprecision(0) << threeBelow << setw(2) << "(" << setprecision(2) << (threeBelow / data.size()) * 100 << "%)" << endl;

}
// Reads in number from console and stores the numbers in to a vector
// load_vector used as a starting point for Project 1
// To use this program, run the cmd.exe and redirect your input file into
// this program 
// load_vector < test.txt
// to redirect the input and output 
// load_vector < text.txt < out.txt
// to run the visual studio, type in the numbers then hit ctrl.z to end
// If confused read chapter 1 in the textBook!!!!!

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include"AR.h"
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "novasParameters.h"

#ifndef NOVAS_ALGORITHM
#define NOVAS_ALGORITHM
using namespace std;
class novasParameters
{
public:
	double alpha;
	double a;
	int p;
};
double mean(vector<double> const & tab);

double kurtosis(vector<double> const & Y);

double estimateurVariance(vector<double>& Y);

vector<double> novasAlgorithm(vector<double>& Y, novasParameters * P);



#endif
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
using namespace std;
#ifndef UTIL_FUNCTION
#define UTIL_FUNCTION
int get_file_size(const char* filename);

vector<double> download_datas(const char* filename);

vector<double> return_series(vector<double> dataLoad);

double median(vector<double>& element);

void ForwardLinearPrediction(vector<double>& coeffs, const vector<double>& x);

vector<double> wchapeau(int q, int n, vector<double>& W);

double muFonctorCaseOne(int p, int q, int n, vector<double>& W, double ao);

double muFonctorCaseTwo(int p, int q, int n, vector<double>& W, double ao);

vector<double> autoCorrelation(const vector<double>& x);


#endif
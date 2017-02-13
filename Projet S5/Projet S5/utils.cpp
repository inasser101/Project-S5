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
#include "utils.h"






using namespace std;
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
int get_file_size(const char* filename) // path to file
{
	int number_of_lines = 0;
	std::string line;
	std::ifstream myfile(filename);

	while (std::getline(myfile, line))
		++number_of_lines;
	return number_of_lines;
}
//lecture en ligne fichier txt, si binaire on doit reprendre cette partie
vector<double> download_datas(const char* filename){
	int size;
	size = get_file_size(filename);
	cout << size << endl;
	int i = 0;
	int dates[6819];
	double cr;
	vector<double> pt;
	FILE * pFile;
	pFile = fopen(filename, "r");

	while (i<size) {

		fscanf(pFile, "%d   %lf", &dates[i], &cr);
		pt.push_back(cr);
		i++;
	}
	cout << i;
	for (int i = 0; i < pt.size(); i++) {
		cout << pt[i] << " ";
	}
	cout << endl;
	return pt;
	}

#endif

// Create the return series from the financial time series of prices P as dataLoad

vector<double> return_series(vector<double> dataLoad) {
	vector<double> Y;
	vector<double>::iterator it;
	it = dataLoad.begin();
	//j'ai considéré qu'on calcul que les Y(i), i >=1, si les input démare à 0 par exemple
	double start;
	start = *it;
	it++;
	for (it = dataLoad.begin();it != dataLoad.end();it++)
	{
		Y.push_back(log(*it)-log(start));
		start = *it;
	}
	return Y;
}

// transformation toward i i d Ness


//Novas foe W, alpha,p, a0,...ap;


/**Volatility Prediction using NoVaS
2 cases:
Case 1: les W(t,a) uncorrelated p 224; µ=median{W(t,a)²/(1-a0*W(t,a)²),t entre p+1 et n}
Case 2:W(t,a) correlated p 225; 
**/

//Calcul du W^ dans AR

//Fonction qui retourne µ selon le cas 1 

double median(vector<double> &element ) {
	size_t size = element.size();

	sort(element.begin(), element.end());

	if (size % 2 == 0)
	{
		return (element[size / 2 - 1] + element[size / 2]) / 2;
	}
	else
	{
		return element[size / 2];
	}

}

/////////////////////////////////////////AR/////////////////////////////////////////
void ForwardLinearPrediction(vector<double> &coeffs, const vector<double> &x)
{
	// GET SIZE FROM INPUT VECTORS
	size_t N = x.size() - 1;
	size_t m = coeffs.size();
	// INITIALIZE R WITH AUTOCORRELATION COEFFICIENTS
	vector<double> R(m + 1, 0.0);
	for (size_t i = 0; i <= m; i++)
	{
		for (size_t j = 0; j <= N - i; j++)
		{
			R[i] += x[j] * x[j + i];
		}
	}
	// INITIALIZE Ak
	vector<double> Ak(m + 1, 0.0);
	Ak[0] = 1.0;
	// INITIALIZE Ek
	double Ek = R[0];
	// LEVINSON-DURBIN RECURSION
	for (size_t k = 0; k < m; k++)
	{
		// COMPUTE LAMBDA
		double lambda = 0.0;
		for (size_t j = 0; j <= k; j++)
		{
			lambda -= Ak[j] * R[k + 1 - j];
		}
		lambda /= Ek;
		// UPDATE Ak
		for (size_t n = 0; n <= (k + 1) / 2; n++)
		{
			double temp = Ak[k + 1 - n] + lambda * Ak[n];
			Ak[n] = Ak[n] + lambda * Ak[k + 1 - n];
			Ak[k + 1 - n] = temp;
		}
		// UPDATE Ek
		Ek *= 1.0 - lambda * lambda;
	}
	// ASSIGN COEFFICIENTS
	coeffs.assign(++Ak.begin(), Ak.end());
}
// W chapeau 
vector<double> wchapeau(int q, int n, vector<double>&W) {
	vector<double> coeffs(q, 0.0);
	ForwardLinearPrediction(coeffs, W);
	// PREDICT DATA LINEARLY
	vector<double> predicted(W);
	size_t m = coeffs.size();
	for (size_t i = m; i < predicted.size(); i++)
	{
		predicted[i] = 0.0;
		for (size_t j = 0; j < m; j++)
		{
			predicted[i] = coeffs[j] * W[i - 1 - j];
		}
	}
	// CALCULATE AND DISPLAY ERROR
	double error = 0.0;
	for (size_t i = m; i < predicted.size(); i++)
	{
		printf("Index: %.2d / Original: %.6f / Predicted: %.6f\n", i, W[i], predicted[i]);
		double delta = predicted[i] - W[i];
		error += delta * delta;
	}
	printf("Forward Linear Prediction Approximation Error: %f\n", error);
	return predicted;

}
///////////////////////// F I N     A R /////////////////////////////////////// 

double muFonctorCaseOne(int p,int q, int n, vector<double>& W,double ao) {
	//vector<double> wchap;
	//wchap = wchapeau(q, n, W);
	//create the vector described in 10.25
	vector<double> elements(n - p, 0.0);
	int i;
	for (i = 0; i < n-p; i++)
	{
			elements[i] = W[p + 1 + i] * W[p + 1 + i]/(1-ao*W[p + 1 + i] * W[p + 1 + i]);
		
	}
return median(elements);
}

//just talked to the guy and it seems to be all good
double muFonctorCaseTwo(int p, int q, int n, vector<double>& W, double ao) {
	vector<double> wchap;
	wchap = wchapeau(q, n, W);
	double temp;
	//create the vector described in 10.25
	// we try here to define the vector of element with detaled factors to simplify 
	vector<double> elements(n - p, 0.0);
	int i, r;
	r = max(p, q);
	vector<double> e_t(n - r, 0.0);
	for (i = 0; i < n-r; i++) {
		e_t[i] = W[i + r] - wchap[i + r];
	}
	for (i = 0; i < n - r; i++)
	{
		temp = e_t[i] + wchap[n + 1];
		elements[i] = temp*temp / (1 - ao*temp*temp);

	}
	return median(elements);
}

//generalize with a G function, It's a little bit harder to write a generalized function 
// with unspecified parameters for it 



/* Calculate the (UN-normalized) autocorrelation for a frame of a
signal   */

vector<double> autoCorrelation(const vector<double> &x)
{
	short order = x.size();

	vector<double> R(order);
	float sum;
	int i, j;

	for (i = 0; i<order; i++) {
		sum = 0;
		for (j = 0; j<order - i; j++) {
			sum += x[j] * x[j + i];
		}
		R[i] = sum;
	}
	return R;
}


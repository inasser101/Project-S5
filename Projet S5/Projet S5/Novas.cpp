#pragma
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include "Novas.h"



using namespace std;

double mean(vector<double> const& tab)
{
	double a(0);

	for (int i(0); i<tab.size(); ++i)
	{
		a += tab[i];
	}

	a = a / tab.size();
	return a;
}


double kurtosis(vector<double> const& Y)
{
	double n(0);
	double d(0);
	double m = mean(Y);
	for (int i(0); i<Y.size(); ++i)
	{
		n = n + pow((Y[i] - m), 4);
		d = d + pow((Y[i] - m), 2);
	}
	return Y.size()*n / pow(d, 2);
}



double estimateurVariance(vector<double> &Y) {
	double y = 0;
	for (int i(0); i<Y.size(); ++i)
	{
		y = y + pow(Y[i], 2);
	}
	return y / Y.size();

}




void novasAlgorithm(vector<double> &Y,novasParameters *P) {

	double s_carre, Kurt = 0;
	s_carre = estimateurVariance(Y);
	vector<double> w(Y.size());
	int k,p = 0;
	double differenceOriginal,difference,keep;

	for (int i(0); i < Y.size(); i++)
	{
		w[i + p] = Y[i + p] / sqrt(1 / (p + 1)*pow(Y[i + p], 2));
	}
	differenceOriginal = labs(3 - Kurt);
	for (k = 0; k < Y.size();k++){
		p = p + 1;
		for (int i(0); i < Y.size(); i++)
		{
			w[i + p] = Y[i + p] / sqrt(1 / (p + 1)*pow(Y[i + p], 2));
		}
		Kurt = kurtosis(w);
		difference = labs(3 - Kurt);
		if (min(difference, differenceOriginal) == differenceOriginal)
			keep = p-1;
		else 
			keep=p;
		differenceOriginal = difference;
	}
	(*P).alpha = 0; (*P).a = 1 / (keep + 1);(*P).p = keep;
}


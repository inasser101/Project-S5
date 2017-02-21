#pragma
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include "Novas.h"



using namespace std;

long double mean(vector<double> &tab,int p) 
{
	long double a=0;
	int i;
	int n = tab.size();
	for (i=1; i <n-p; i++)
	{
		a += tab[i];
		//cout<<"tab["<<i<<"]	:" << tab[i]<< endl;
	}
	//cout <<"a	"<< a;
	return a;
}


long double kurtosis(vector<double> & Y,int p)
{
	long double n(0);
	long double d(0);
	long double m = mean(Y,p);
	//cout << "mean:  " << m;
	for (int i(1); i<Y.size(); i++)
	{
		n = n + (long double)pow((Y[i] - m), 4);
		d = d + (long double)pow((Y[i] - m), 2);
		//cout << " first 1:" << (long double)pow((Y[i] - m), 4);
		//cout << " second 1:" << d;
	}
	return (long double)Y.size()*n / (long double)pow(d, 2);
}



double estimateurVariance(vector<double> &Y) {
	double y = 0;
	for (int i(0); i<Y.size(); ++i)
	{
		y = y + pow(Y[i], 2);
	}
	return y / Y.size();

}

int  min_element(vector<double> &Y)
{
	int t=0;
	double min = Y[0];
	for (int i(1); i < Y.size(); i++) {
		if (Y[i]<min){
			min = Y[i];
			t = i;
		}
	}
	return t;
}


vector<double> novasAlgorithm(vector<double> &Y,novasParameters *P) {

	double s_carre;
	long double Kurt=0.0;
	s_carre = estimateurVariance(Y);
	vector<double> w(Y.size());
	int k,stop,p = 0;
	long double differenceOriginal,difference,keep=0;
	cout << "	" << "novas Algorithm w size :" << w.size() << endl;
	for (int i(0); i < Y.size()-p; i++)
	{
		w[i + p] = Y[i + p] / sqrt(1 / (p + 1)*pow(Y[i + p], 2));
	}
	differenceOriginal = abs(3 - Kurt);
	//cout <<" differenceOriginal before the main "<< differenceOriginal << endl;
	stop = 1;
	vector<double> kur;
	while (p < w.size() && stop != 0) {
		//cout << " step : " << p;
		for (int i(0); i < Y.size() - p; i++)
		{
			
			w[i + p] = Y[i + p] / sqrt(1 /( (p + 1)*pow(Y[i + p], 2)));
			//cout << "    "<< 1/sqrt(1 / ((p + 1)*pow(Y[i + p], 2)));
			//cout << "	" << Y[i + p] / sqrt(1 / ((p + 1)*pow(Y[i + p], 2)));
		}
		Kurt = kurtosis(w,p);
		
		difference = abs(3 - Kurt);
		kur.push_back(difference);
		//cout << "  des difference : " << difference<<" et "<< differenceOriginal;
		/*if (min(difference, differenceOriginal) == differenceOriginal)
			{
				
			keep = p - 1;}
		else 
			keep=p;
			*/

		differenceOriginal = difference;
		//cout << " Kurt : " << Kurt;
		//cout << "	"<< " the p order:" << keep << endl;

		if (p == Y.size()) { stop = 0; }
		if (p < Y.size()) { p = p + 1; }
		
	}
	
	keep = min_element(kur);
	cout << "checkpoint 3 #### choice of p-order is: " << keep << " | kurtosis - 3|  = "<<kur[keep] << endl;
	double temp1 = 0;
	vector<double> ww(Y.size()-keep);
	cout << "Normalized return series" << endl; 
	for (int t(keep+1); t < Y.size(); t++)
	{
		for (int i(0); i <= keep; i++) {
			temp1 += pow(Y[t-i], 2) / (keep + 1);
		}
		ww[t-keep-1] =Y[t]/sqrt(temp1);
		cout << "   W[" << t-1 << "]    :        "<< ww[t-keep-1] <<endl;
	}
	cout << endl; cout << endl; cout << endl;
	
	cout << "	" << " the p order:" << keep << endl;
	(*P).alpha = 0; (*P).a = 1 / (keep + 1);(*P).p = keep;
	cout << "Novas succeed quit checkpoint 3" << endl;
	return ww;
}



double A_n(vector<double> &Y, int p) {

	double s_carre;
	long double Kurt = 0.0;
	s_carre = estimateurVariance(Y);
	double A_n=0.0;
	
		for (int i(1); i <= p; i++) {
			A_n += pow(Y[Y.size() - i], 2) / (p + 1);
		}

	return A_n;
}

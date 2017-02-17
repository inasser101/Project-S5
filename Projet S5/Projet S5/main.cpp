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
#include "Novas.h"
#include "utils.h"
using namespace std;
int main() {
	vector<double> data = download_datas("\Nikkei_index_1984_2010.dat");
	vector<double> returns = return_series(data);
	cout << "Checkpoint  1" << endl;
	novasParameters  m;
	(m).p = 0;
	(m).a = 0.0;
	(m).alpha = 0.0;
	novasParameters  *P=&m;
	cout << "Checkpoint  2:" << endl;
	cout << "	" << "return series size:" << returns.size() << endl;

	vector <double> w=novasAlgorithm(returns, P);
	int n = w.size();
	cout << "Checkpoint  4" << endl;
	double wchapeau_n1 = wchapeau_n(n, n, w);
	cout << "Checkpoint  5" << endl;
	cout << "n" << n;
	double mu_1 = muFonctorCaseOne(P->p, n - 1, n, w, P->a);
	cout <<  endl;
	cout << "predicted Y_n_+_1 " << sqrt(mu_1)*A_n(returns, P->p);
	//double mu_2 = muFonctorCaseTwo(P->p, n - 1, n, w, P->a);
	//cout << mu_1 << mu_2 << endl;

	system("pause");
	return 0;
}                    
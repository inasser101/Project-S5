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

	system("pause");
	return 0;
}                    
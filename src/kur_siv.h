#ifndef __KUR_SIV__
#define __KUR_SIV__

#include <complex>
#include <vector>
#include <cmath> // M_PI
#include <random>

using namespace std;

class KuramotoSivashinsky {
  vector<complex<double> > C;
  int N;
  double h;
  double K;
  vector<double> a;
  vector<double> eah;
  vector<int> modes;

public:
  KuramotoSivashinsky(double, double, int);
  vector<complex<double> > GetC() {return C;}
  vector<double> Geta() {return a;}
  vector<double> Geteah() {return eah;}
  vector<int> Getmodes() {return modes;}
};

#endif

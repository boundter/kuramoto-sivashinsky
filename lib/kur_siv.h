// This file kur_siv.h is part of kuramoto-sivashinksy.
//
// It contains the header for class KuramotoSivashinsky.
//
// Copyright (C) 2017 Erik Teichmann (eteichma@uni-potsdam.de)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef __KUR_SIV__
#define __KUR_SIV__

#include <complex>
#include <vector>
#include <cmath> // M_PI
#include <random>

using namespace std;

class KuramotoSivashinsky {
  vector<complex<double> > C; // Fourier modes
  int N; // number of modes to consider
  double h; // time-step
  double K; // wave-vector = 2*pi/L
  vector<double> a; // a = n^2*K^2 - n^4*K^4
  vector<double> eah; // eah = exp(a*h)
  vector<int> modes; // evolving modes (a, C =/= 0)
  vector<complex<double> > GetF(vector<complex<double> >*);

public:
  KuramotoSivashinsky(double, double, int);
  vector<complex<double> > GetC() {return C;}
  vector<double> Geta() {return a;}
  vector<double> Geteah() {return eah;}
  vector<int> Getmodes() {return modes;}
  vector<double> Getu(vector<double>*);
  void Integrate();
};

#endif

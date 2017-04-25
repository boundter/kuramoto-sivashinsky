// This file kur_siv.cpp is part of kuramoto-sivashinksy.
//
// It contains the class KuramotoSivashinsky to model the equation.
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


#include "kur_siv.h"

KuramotoSivashinsky::KuramotoSivashinsky(double step, double L,
                                         int number_modes) {
  h = step;
  K = 2*M_PI/L;
  N = number_modes;
  long seed = 123456;
  mt19937_64 gen (seed);
  uniform_real_distribution<double> dist(-1.0, 1.0);
  C.resize(N + 1, 0);
  C[0] = complex<double> (1., 0.);
  for (int i = 1; i <= N; ++i) {
    C[i] = complex<double> (dist(gen), dist(gen));
  }

  for (int i = 0; i <= N; ++i) {
    double ai = i*i*K*K - i*i*i*i*K*K*K*K;
    double precision = 1e-12;
    if (fabs(ai) > precision) {
      modes.push_back(i);
    }
    a.push_back(ai);
    eah.push_back(ai*h);
  }
}

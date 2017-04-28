// This file velocity_modes.cpp is part of kuramoto-sivashinksy.
//
// It simulates the evolution of the veclocity-field for a certain number of
// modes.
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

#include <cstdio>
#include <vector>
#include <string>
#include <cmath> // M_PI, floor
#include "../lib/kur_siv.h"

using namespace std;

int main(int argc, char *argv[]) {
  const double h = 0.01;
  const double L = 30;
  const int N = atof(argv[1]);
  const int n = 20000;
  const double spatial_resolution = 200;
  FILE * datafile = fopen("data/velocity_modes.dat", "w");
  fprintf(datafile, "# h= %.9f , L= %.9f , N= %d\n", h, L, N);

  KuramotoSivashinsky kuramoto(h, L, N);
  vector<double> x;
  for (int i = 0; i < spatial_resolution; ++i) {
    x.push_back(i*L/spatial_resolution);
  }
  vector<double> u = kuramoto.Getu(&x);
  fprintf(datafile, "%.4f", kuramoto.Gett());
  for (int j = 0; j < u.size(); ++j) {
    fprintf(datafile, " %.6f", u[j]);
  }
  fprintf(datafile, "\n");

  for (int i = 0; i < n; ++i) {
    kuramoto.Integrate();
      vector<double> u = kuramoto.Getu(&x);
      fprintf(datafile, "%.4f", kuramoto.Gett());
      for (int j = 0; j < x.size(); ++j) {
        fprintf(datafile, " %.6f", u[j]);
      }
      fprintf(datafile, "\n");
  }

  fclose(datafile);
}

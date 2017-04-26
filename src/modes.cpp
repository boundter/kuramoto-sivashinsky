// This file modes.cpp is part of kuramoto-sivashinksy.
//
// It simulates the evolution of the Fourier-modes
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
#include "../lib/kur_siv.h"

using namespace std;

int main() {
  const double h = 0.001;
  const double L = 40.;
  const int N = 120;
  const int n = 1000;
  FILE * datafile = fopen("data/modes.dat", "w");

  fprintf(datafile, "# h= %.9f , L= %.9f , N= %d\n", h, L, N);

  KuramotoSivashinsky kuramoto(h, L, N);
  vector<complex<double> > C = kuramoto.GetC();
  // Save the modes to file
  fprintf(datafile, "%.9f %.9f", C[0].real(), C[0].imag());
  for (int i = 1; i < C.size(); ++i) {
    fprintf(datafile, " %.9f %.9f", C[i].real(), C[i].imag());
  }
  fprintf(datafile, "\n");
  fflush(datafile);
  // Integrate the system and save the modes after every step
  for (int i = 0; i < n; ++i) {
    kuramoto.Integrate();
    C = kuramoto.GetC();
    fprintf(datafile, "%.9f %.9f", C[0].real(), C[0].imag());
    for (int j = 1; j < C.size(); ++j) {
      fprintf(datafile, " %.9f %.9f", C[j].real(), C[j].imag());
    }
    fprintf(datafile, "\n");
    fflush(datafile);
  }
  fclose(datafile);
}

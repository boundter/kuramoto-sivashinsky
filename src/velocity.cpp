// This file velocity.cpp is part of kuramoto-sivashinksy.
//
// It simulates the evolution of the veclocity-field.
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
#include <cmath> // M_PI
#include "../lib/kur_siv.h"

using namespace std;

int main() {
  const double h = 0.001;
  const double L = 40.;
  const int N = 4*floor(L/(2*M_PI));
  const int n = 1000;
  FILE * datafile = fopen("data/veclocity.dat", "w");

  fclose(datafile);
}

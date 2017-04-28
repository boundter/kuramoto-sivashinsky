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
  K = 2*M_PI/L; // Wave vector
  N = number_modes;
  t = 0;

  // Create a random distribution of modes
  long seed = 123456; // arbitrary seed for the RNG
  mt19937_64 gen (seed);
  uniform_real_distribution<double> dist(-1.0, 1.0);
  C.resize(N + 1, 0);
  C[0] = complex<double> (0., 0.);
  for (int i = 1; i <= N; ++i) {
    C[i] = complex<double> (dist(gen), dist(gen));
  }

  // Calculate the constant a=i**2*K**2 - i**4*K**4 and eah=exp(a*h) to save
  // computing-time later on.
  // For a=0 there won't be any evolution, so we can exclude these modes.
  // The evolving modes are saved in modes.
  for (int i = 0; i <= N; ++i) {
    double ai = i*i*K*K - i*i*i*i*K*K*K*K;
    double precision = 1e-12;
    if (fabs(ai) > precision) {
      modes.push_back(i);
    }
    a.push_back(ai);
    eah.push_back(exp(ai*h));
  }
}


vector<double> KuramotoSivashinsky::Getu(vector<double>* x) {
  vector<double> u;
  // Calculate u by using the discrete inverse Fouriertransformation
  // u = sum_n(C_n*exp(i*n*K*x)).
  // Since u is real the modes C_(-n) = C_n^*, this reduces to trigonometric
  // equations.
  for (int i = 0; i < (*x).size(); ++i) {
    u.push_back(C[0].real());
    for (int j = 1; j < C.size(); ++j) {
      u[i] += 2*C[j].real()*cos(j*K*(*x)[i]) - 2*C[j].imag()*sin(j*K*(*x)[i]);
    }
  }
  return u;
}


vector<complex<double> > KuramotoSivashinsky::GetF(vector<complex<double> >* c) {
  vector<complex<double> > F, G = (*c);
  for (int i = 0; i < G.size(); ++i) {
    F.push_back(0);
    // Conjugate the C, if their index is smaller than 0.
    for (int j = -N + i; j <= N; ++j) {
      complex<double> C_off, C_norm;

      if (j < 0) C_norm = conj(G[-j]);
      else C_norm = G[j];

      if (i - j < 0) C_off = conj(G[j - i]);
      else C_off = G[i-j];

      F[i] -= C_off*C_norm*complex<double>(0., j*K);
    }
  }
  return F;
}


void KuramotoSivashinsky::Integrate() {
  vector<complex<double> > C_before = C;
  vector<complex<double> > F = GetF(&C_before);
  for (int i = 0; i < modes.size(); ++i) {
    int j = modes[i];
    C_before[j] = C_before[j]*eah[j] + F[j]*(eah[j] - 1)/a[j];
  }
  vector<complex<double> > F_new = GetF(&C_before);
  for (int i = 0; i < modes.size(); ++i) {
    int j = modes[i];
    C[j] = C_before[j] + (F_new[j] - F[j])*(eah[j] - 1 - a[j]*h)/(a[j]*a[j]*h);
  }
  t += h;
}

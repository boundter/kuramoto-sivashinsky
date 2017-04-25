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

import numpy as np
import matplotlib.pyplot as plt


class Kur_Siv:
    def __init__(self, h, L, N, u0):
        self.C = np.fft.rfft(u0)
        self.N = N
        if self.N > self.C.size + 1:
            print("Too few fourier-modes for the Galerkin-Approximation")
        for i in range(N+1, self.C.size):
            self.C[i] = 0
        self.h = h
        self.K = 2*np.pi/L
        self.a = np.zeros(self.N)
        self.eah = np.zeros(self.N)
        for i in range(1, self.N + 1):
            self.a[i - 1] = i**2*self.K**2 - i**4*self.K**4
            self.eah[i - 1] = np.exp(self.a[i - 1]*h)
        self.modes = np.where(np.abs(self.a) > 1e-12)[0]
        self.a = self.a[self.modes]
        self.eah = self.eah[self.modes]

    def get_u(self):
        return np.fft.irfft(self.C)

    def calc_F(self, C):
        F = np.zeros(C.size - 1, dtype=np.complex128)
        for i in range(1, self.N + 1):
            su = 0
            for j in range(-self.N + i, self.N + 1):
                if (i - j) < 0:
                    C_off = np.conjugate(C[j - i])
                else:
                    C_off = C[i - j]
                if j < 0:
                    C_norm = np.conjugate(C[-j])
                else:
                    C_norm = C[j]
                su += 1j*j*self.K*C_norm*C_off
            F[i - 1] = su
        return F

    def integrate(self):
        C_before = np.copy(self.C[self.modes + 1])
        F = self.calc_F(self.C[:self.N + 1])[self.modes]
        C_mid = np.copy(self.C[:self.N + 1])
        C_mid[self.modes + 1] = C_before*self.eah + \
            F*(self.eah - 1)/self.a
        F_mid = self.calc_F(C_mid)[self.modes]
        self.C[self.modes + 1] = C_mid[self.modes + 1] + \
            (F_mid - F)*(self.eah - 1 - self.a*self.h)/(self.a*self.a*self.h)


if __name__ == "__main__":
    L = 2*np.pi
    N = 3*int(L/(2*np.pi))
    n = 41
    x = np.linspace(0., L, 200)
    y = np.cos(3*np.sin(x))
    kur = Kur_Siv(0.01, 8*np.pi, N, y)
    u = kur.get_u()
    result = [u]
    for i in range(0, n):
        kur.integrate()
        result.append(kur.get_u())
    plt.imshow(result, cmap='hot', interpolation='nearest')
    plt.show()

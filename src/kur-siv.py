import numpy as np


class Kur_Siv:
    def __init__(self, h, L, N, u0):
        self.C = np.fft.rfft(u0)
        self.N = N
        for i in range(N+1, self.C.size):
            self.C[i] = 0
        self.h = h
        self.K = 2*np.pi/L
        self.a = np.zeros(self.N + 1)
        self.eah = np.zeros(self.N + 1)
        for i in range(1, self.N + 1):
            self.a[i] = i**2*self.K**2 - i**4*self.K**4
            self.eah[i] = np.exp(self.a[i]*h)

    def Getu(self):
        return np.fft.irfft(self.C)

    def CalcF(self, C):
        F = np.zeros(C.size, dtype=np.complex128)
        for i in range(0, self.N + 1):
            su = 0
            for j in range(-self.N + i, self.N + 1):
                if (i - j) < 0:
                    C_off = np.conjugate(C[j - i])
                else:
                    C_off = C[i - j]
                su += 1j*j*self.K*C[j]*C_off
            F[i] = su
        return F

    def Integrate(self):
        F = self.CalcF(self.C)
        C_mid = self.C*self.eah + F*(self.eah - 1)/self.a
        F_mid = self.CalcF(C_mid)
        self.C = C_mid + \
            (F_mid - F)*(self.eah - 1 - self.a*self.h)/(self.a*self.a*self.h)

if __name__ == "__main__":
    L = 8*np.pi
    N = 3*int(L/(2*np.pi))
    x = np.linspace(0., L, 100)
    y = np.sin(x)
    kur = Kur_Siv(0.1, 8*np.pi, N, y)
    u = kur.Getu()
    print(y - u)

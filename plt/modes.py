# This file modes.py is part of kuramoto-sivashinksy.
#
# It plots the evolution over time of the modes.
#
# Copyright (C) 2017 Erik Teichmann (eteichma@uni-potsdam.de)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

import sys
sys.path.insert(0, "lib")
import numpy as np
import matplotlib.pyplot as plt
from fileoperations import ReadFile

plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 17

header, modes = ReadFile("data/modes.dat", 1, " ")
modes = modes.transpose()
cmodes = []

# TODO: Find a more pythonic way
for i in range(0, modes.shape[0]):
    cmode = []
    for j in range(0, int(modes[i].size/2)):
        cmode.append(modes[i][2*j] + 1j*modes[i][2*j + 1])
    cmodes.append(cmode)
cmodes = np.array(cmodes, dtype=np.complex128)
n = np.arange(0, cmodes[0].size)

fig, ax = plt.subplots()
ax.set_xlabel(r"$n$")
ax.set_ylabel(r"$\vert C_n \vert$")
width = 0.35
ax.bar(n, np.abs(cmodes[0]), width, fill=False, ls="-", label=r"$t=0$")
ax.bar(n, np.abs(cmodes[-1]), width, color='r', label=r"$t=1$")
ax.set_xlim(0., 50.)
ax.legend(loc="best")
fig.tight_layout()
fig.savefig("plt/modes.pdf", dpi=300)

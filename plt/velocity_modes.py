# This file velocity_modes.py is part of kuramoto-sivashinksy.
#
# It plots the evolution over time of the velocity-field for a certain number
# of modes.
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
sys.path.insert(0, "lib")  # for import of fileoperations
import numpy as np
import matplotlib.pyplot as plt
from fileoperations import ReadFile

# Define size of the plot for the rport
plt.rcParams["figure.figsize"] = [8, 5]
plt.rcParams["font.size"] = 17

header, field = ReadFile("data/velocity_modes.dat", 1, " ")
t = field[0]
u = field[1:]
x = np.linspace(0., header["L"], num=u.shape[0], endpoint=False)
u_min, u_max = -np.abs(u[-1]).max(), np.abs(u[-1]).max()

x_new = []
for i in range(0, u.shape[0]):
    xi = np.zeros(u.shape[1])
    xi.fill(x[i])
    x_new.append(xi)
x = np.array(x_new, dtype=np.float64)

t_new = []
for i in range(0, u.shape[0]):
    t_new.append(t)
t = np.array(t_new, dtype=np.float64)


plt.xlabel(r"$t$")
plt.ylabel(r"$x$")
plt.pcolormesh(t, x, u, cmap='RdBu', vmin=u_min, vmax=u_max)
cbar = plt.colorbar()
cbar.ax.set_ylabel(r"$u(x,t)$")
plt.ylim(0., x[-1][0])
plt.tight_layout()
plt.savefig("plt/velocity_N%d.png" % header["N"], dpi=300)

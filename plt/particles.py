# This file particles.py is part of kuramoto-sivashinksy.
#
# It plots the evolution of particles on the veclocity-field.
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

header, particles = ReadFile("data/particles.dat", 1, " ")

fig, ax = plt.subplots()
cmap = plt.get_cmap('jet')
colors = cmap(np.linspace(0, 1.0, particles[1:].shape[0]))
ax.set_ylabel(r"$x$")
ax.set_xlabel(r"$t$")
for i in range(1, particles.shape[0]):
    abs_d_data = np.abs(np.diff(particles[i]))
    mask = np.hstack([ abs_d_data > abs_d_data.mean()+12*abs_d_data.std(), [False]])
    masked_data = np.ma.MaskedArray(particles[i], mask)
    ax.plot(particles[0], masked_data, color=colors[i - 1])
ax.set_ylim(0., header["L"])
fig.tight_layout()
fig.savefig("plt/particles.pdf", dpi=300)

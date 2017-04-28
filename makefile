CXX = g++
FLAGS = -O3
LIBS = lib/kur_siv.cpp

OBJ_DIR = bin/
SRC_DIR = src/
PLT_DIR = plt/
DAT_DIR = data/

MODES = modes
VELOCITY = velocity
VELOCITY_PLOT_PREFIx = $(PLT_DIR)$(VELOCITY)_

L = 6.29 10 15 20 25 30
L_PLOTS = $(addprefix $(PLT_DIR)$(VELOCITY)_$(MODES)_L, $(L).png)
N = 16 12 8 7
N_PLOTS = $(addprefix $(PLT_DIR)$(VELOCITY)_$(MODES)_N, $(N).png)

modes: $(PLT_DIR)$(MODES).pdf
velocity: $(L_PLOTS)
n : $(N_PLOTS)

#-------------------------------------------------------------------------------
# Modes
#-------------------------------------------------------------------------------

$(PLT_DIR)$(MODES).pdf: $(PLT_DIR)$(MODES).py $(DAT_DIR)$(MODES).dat
	python3 $(PLT_DIR)$(MODES).py

$(DAT_DIR)$(MODES).dat: $(OBJ_DIR)$(MODES).x
	$(OBJ_DIR)$(MODES).x

$(OBJ_DIR)$(MODES).x: $(SRC_DIR)$(MODES).cpp
	$(CXX) $< $(LIBS) $(FLAGS) -o $@;

#-------------------------------------------------------------------------------
# Velocity
#-------------------------------------------------------------------------------

$(L_PLOTS): $(OBJ_DIR)$(VELOCITY).x $(PLT_DIR)$(VELOCITY).py
	$(OBJ_DIR)$(VELOCITY).x$(subst .png,,$(subst  plt/velocity_L,, $@))
	python3 $(PLT_DIR)$(VELOCITY).py

$(OBJ_DIR)$(VELOCITY).x: $(SRC_DIR)$(VELOCITY).cpp
	$(CXX) $< $(LIBS) $(FLAGS) -o $@;

#-------------------------------------------------------------------------------
# Velocity_modes
#-------------------------------------------------------------------------------

$(N_PLOTS): $(OBJ_DIR)$(VELOCITY)_$(MODES).x $(PLT_DIR)$(VELOCITY)_$(MODES).py
	$(OBJ_DIR)$(VELOCITY)_$(MODES).x$(subst .png,,$(subst  plt/velocity_modes_N,, $@))
	python3 $(PLT_DIR)$(VELOCITY)_$(MODES).py

$(OBJ_DIR)$(VELOCITY)_$(MODES).x: $(SRC_DIR)$(VELOCITY)_$(MODES).cpp
	$(CXX) $< $(LIBS) $(FLAGS) -o $@;

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
L_PLOTS = $(addprefix $(PLT_DIR)$(VELOCITY)_L, $(L).png)

modes: $(PLT_DIR)$(MODES).pdf
velocity: $(L_PLOTS)

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

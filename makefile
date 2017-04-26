CXX = g++
FLAGS = -O3
LIBS = lib/kur_siv.cpp

OBJ_DIR = bin
SRC_DIR = src
SCRPT_DIR = plt
PLT_DIR = plt
DAT_DIR = data

MAIN_FILES := $(shell ls $(SRC_DIR)/*.cpp | xargs -n 1 basename)
OBJECTS = $(MAIN_FILES:%.cpp=$(OBJ_DIR)/%.x)
SCRIPT_FILES := $(shell ls $(SCRPT_DIR)/*.py | xargs -n 1 basename)
PLOTS = $(SCRIPT_FILES:%.py=$(PLT_DIR)/%.pdf)

sim: $(OBJECTS)
plt: $(PLOTS)

$(OBJ_DIR)/%.x: $(SRC_DIR)/%.cpp
	$(CXX) $< $(LIBS) $(FLAGS) -o $@;
	$@

$(PLT_DIR)/%.pdf: $(SCRPT_DIR)/%.py $(DAT_DIR)/%.dat
	python3 $<

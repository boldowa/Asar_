# Enable gcov
CPPUTEST_USE_GCOV = Y

# Execute flags
CPPUTEST_EXE_FLAGS = -c

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- FLAGS ----#
CPPUTEST_CXXFLAGS = -std=c++98 -Dstricmp=strcasecmp
CPPUTEST_CXXFLAGS += -include include/common/autoarray.h
CPPUTEST_CXXFLAGS += -include include/common/assocarr.h
CPPUTEST_CXXFLAGS += -DINTERFACE_LIB
#CPPUTEST_CXXFLAGS += -Dlinux

#---- Outputs ----#
COMPONENT_NAME = Asar
#Set this to @ to keep the makefile quiet
SILENCE = @

#--- Inputs ----#
PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ../CppUTest
endif
CPP_PLATFORM = Gcc

SRC_DIRS = \
    src/*

#SRC_DIRS = \
    src\
    src/*

# to pick specific files (rather than directories) use this:    
SRC_FILES = src/interface-lib.cpp

TEST_SRC_DIRS = \
    tests \
    tests/*

MOCKS_SRC_DIRS = \
    mocks \

INCLUDE_DIRS =\
  .\
  include \
  include/* \
  $(CPPUTEST_HOME)/include/ \
  $(CPPUTEST_HOME)/include/Platforms/Gcc\
  mocks

CPPUTEST_WARNINGFLAGS = -Wall -Werror #-Wswitch-default 
#CPPUTEST_WARNINGFLAGS += -Wconversion -Wswitch-enum 
CPPUTEST_WARNINGFLAGS += -Wno-unused-result -Wno-uninitialized

include $(CPPUTEST_HOME)/build/MakefileWorker.mk


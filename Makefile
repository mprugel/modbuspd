# Makefile to build class 'counter' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.
PDINCLUDEDIR=/usr/local/include/pd
# library name
lib.name = externals.modbus

# input source file (class name == source file basename)
class.sources = modbus.c
# all extra files to be included in binary distribution of the library
datafiles =
ldlibs = libmodbus.so
cflags = -lmodbus
# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=./pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder

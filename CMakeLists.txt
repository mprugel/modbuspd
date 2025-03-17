# Define your standard CMake header (for example):
cmake_minimum_required(VERSION 3.18)

# Include pd.cmake (1):
set(PDCMAKE_DIR pd.cmake/ CACHE PATH "Path to pd.cmake")
include(${PDCMAKE_DIR}/pd.cmake)

add_library(modbus SHARED IMPORTED)
set_property(TARGET modbus PROPERTY IMPORTED_LOCATION "/usr/local/lib/libmodbus.so")

# Declare the name of the project:
project(modbus_external)

# Add one or several externals (5):
pd_add_external(modbus_external modbus.c)

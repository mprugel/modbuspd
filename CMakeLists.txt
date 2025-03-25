# Define your standard CMake header (for example):
cmake_minimum_required(VERSION 3.18)

# Include pd.cmake (1):
set(PDCMAKE_DIR pd.cmake/ CACHE PATH "Path to pd.cmake")
set(PD_SOURCES_PATH /usr/local/include/pd)

include(${PDCMAKE_DIR}/pd.cmake )
include_directories(libmodbus/src libmodbus)

#add_library(modbus SHARED IMPORTED)
#set_property(TARGET modbus PROPERTY IMPORTED_LOCATION "/usr/local/lib/libmodbus.so")

# Declare the name of the project:
project(modbus_external)


file(GLOB EXTERNAL_SOURCES "${CMAKE_SOURCE_DIR}/libmodbus/src/*.c")
list(APPEND EXTERNAL_SOURCES modbus_external.c)
# Add one or several externals (5):
pd_add_external(modbus_external ${EXTERNAL_SOURCES})

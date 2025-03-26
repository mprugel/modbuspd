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
project(modbus)

set(SOURCES ./libmodbus/src/modbus.c ./libmodbus/src/modbus-data.c ./libmodbus/src/modbus-rtu.c ./modbus.c)
file(GLOB EXTERNAL_SOURCES "${CMAKE_SOURCE_DIR}/libmodbus/src/*.c")
set(EXTERNAL_SOURCES "${EXTERNAL_SOURCES} ${CMAKE_SOURCE_DIR}/modbus.c")
message(SOURCES="${EXTERNAL_SOURCES}")
# Add one or several externals (5):
add_pd_external(modbus modbus ${SOURCES})

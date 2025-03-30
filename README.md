# modbuspd
This external for Pure Data is a simple Wrapper for the libmodbus C library.
Following Commands are supported at the moment:
- Reading of a single register
- Writing of a single register
<img src="https://github.com/mprugel/modbuspd/blob/main/modbus_help.png?raw=true" width="450px">

## Installation
- Download the zip folder for your Operating System under the **Release** section.
- Extract the zip archive and copy the `modbus` folder into the Pure Data externals folder.
- Add the `modbus` folder in the preferences to the path
- 
## Build from Sources
### Linux
```
git submodule init
git submodule update
cd libmodbus
./configure
cd ..
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows
For Windows mingw64 is used for compilation. Just install it and run the Linux command in the mingw64 shell to compile the external.

### MacOS
Currently not supported, although the build should work with the Linux commands.

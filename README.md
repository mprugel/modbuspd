# modbuspd
This external for Pure Data is a simple Wrapper for the libmodbus C library.
Following Commands are supported at the moment:
- Reading of a singe register
- Wrting of a single register
<img src="https://github.com/mprugel/modbuspd/blob/main/modbus_help.png?raw=true" width="450px">

## Build
### Linux
```
git submodule init
git submodule update
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows
For Windows mingw64 is used for compilation. Just install it and run the Linux command in the mingw64 shell to compile the external.

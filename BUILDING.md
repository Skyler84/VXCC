# Building VXCC

VXCC uses the CMake build generator system.

## Building using CMake

Create a build directory - usually ./build under the project root directory.
run `cd build/` to enter the build directory
run `cmake ..` or `cmake path/to/project/root` if not directly under the root directory of the project. 
This will generate the build files
run `cmake --build .` to build the project. This will build a few targets
- vxcc-bin: The main application that will run all the relevant compilation/translation phases. Can be found in app/vxcc
- vxcc: The main source library. Can be found in src/libvxcc.a
- vxcc_test: The test executable to verify the function of the code.

## Running

Running the program is as simple as running `build/app/vxcc`.

## Running tests

Running the tests is as simple as running `build/test/vxcc_test`.

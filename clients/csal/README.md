#CSAL
C client for Simple Access Layer (SAL)

##Build
Environment variable BUILD_DIR can be set for the output directory - defaults to "build"
Type make to build libcsal.so and tests in the BUILD_DIR directory.

##Testing
LD_LIBRARY_PATH=./build/:$LD_LIBRARY_PATH   ./build/test

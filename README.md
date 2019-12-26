To test the file matix.h:

mkdir -p build_debug
cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug .. 
cmake  --build . 
./tests/test_matrix
ctest


There is a useful article about fast matrix multiplication https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
and Eigen Matrix Multiplication (to speed up the process) https://stackoverflow.com/questions/36659004/eigen-matrix-multiplication-speed


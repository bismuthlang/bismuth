rm -rf cov/ # Remove the coverage folder
cmake -S . -B cov -DCMAKE_BUILD_TYPE=Debug -DBUILD_COVERAGE=ON && cmake --build cov && cd cov && make coverage


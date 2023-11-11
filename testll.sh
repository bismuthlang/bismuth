#!/bin/bash
rm ./a.out
clang++ $1.ll ./bdwgc/libgc.a ./bdwgc/libgccpp.a ./build/bin/runtime/libbismuth_runtime_archive.a -no-pie
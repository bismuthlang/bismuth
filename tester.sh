#!/bin/bash
rm ./a.out
./build/bin/bismuthc $1.prism --compile=clangll && ./a.out && sha256sum $1.ll
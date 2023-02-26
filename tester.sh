#!/bin/bash
./build/bin/wplc $1.prism --compile=clang && ./a.out && sha256sum $1.ll
#!/bin/bash
./build/bin/wplc $1.prism --compile=clangll && ./a.out && sha256sum $1.ll
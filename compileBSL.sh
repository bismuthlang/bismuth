#!/bin/bash
rm ./a.out
./build/bin/bismuthc ./bsl/lib/Types.bismuth ./bsl/lib/Lists.bismuth ./bsl/lib/Optional.bismuth ./bsl/lib/Arrays.bismuth $1.bismuth -verbose --compile=clangll && ./a.out && sha256sum $1.ll
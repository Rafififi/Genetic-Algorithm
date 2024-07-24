#!/bin/bash
make
rustc parser.rs
seq 1 10 | xargs -n 1 -P 4 -I {} bash -c './Algo 1000 1000 0.5 0.05 0 2; sleep 1'
./parser
make clean

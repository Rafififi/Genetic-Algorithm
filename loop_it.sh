#!/bin/bash

for i in {1..100}
do 
    ./Algo 1000 1000 0.5 0.05 0 2
    echo $i
done

./parser
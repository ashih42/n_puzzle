#!/bin/bash

rm -f temp.txt
python mod-gen.py $@ > temp.txt
./npuzzle -f temp.txt

#! /bin/bash


docker build --tag dgse:defi1 . && docker run -ti --rm -h AttrapeLeDrapeau --network none defi1:latest

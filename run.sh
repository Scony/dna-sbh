#!/bin/bash

runtests() {
for i in $(ls tests/${1} | sort -n); do
    echo ${1}/$i; ./general.out $tests/${1}/$i;
  done
}

echo GROUP 1
runtests group1

echo
echo GROUP 2
runtests group2

echo
echo GROUP 3
runtests group3

echo
echo GROUP 4
runtests group4

echo
echo OWN
runtests group4

#!/bin/bash

#find tests/* | xargs -I {} sh -c 'cat {} | ./general.out'
echo
echo GROUP 1
find tests/group1 -type f -exec sh -c 'echo {}; ./general.out < {}' \;
echo
echo GROUP 2
find tests/group2 -type f -exec sh -c 'echo {}; ./general.out < {}' \;
echo
echo GROUP 3
find tests/group3 -type f -exec sh -c 'echo {}; ./general.out < {}' \;
echo
echo GROUP 4
find tests/group4 -type f -exec sh -c 'echo {}; ./general.out < {}' \;
echo
echo OWN
find tests/own -type f -exec sh -c 'echo {}; ./general.out < {}' \;

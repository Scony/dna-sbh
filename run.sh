#!/bin/bash

find tests/* | xargs -I {} sh -c 'cat {} | ./general.out'
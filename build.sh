#!/bin/bash

set -xe
cc test_gate.c  gates.c -ggdb -o test_gate
cc main.c gates.c -Wall -Wextra -o logic
./test_gate

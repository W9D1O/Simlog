#!/bin/bash

set -xe
cc test_gate.c  gates.c -ggdb -o test_gate
cc graphics2.c -I/home/w9d1o/Projects/de_terceros/raylib-6.0_linux_amd64/include \
  -L/home/w9d1o/Projects/de_terceros/raylib-6.0_linux_amd64/lib \
  -Wl,-rpath,/home/w9d1o/Projects/de_terceros/raylib-6.0_linux_amd64/lib \
  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
-o graphics
cc main.c gates.c -Wall -Wextra -o logic
#./test_gate

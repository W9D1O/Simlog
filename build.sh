#!/bin/bash


cc test_gate.c  gates.c -o test_gate
cc main.c gates.c -o logic

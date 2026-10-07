#include <stdio.h>
#include "gates.h"
#include <stdlib.h>


#define CANT_INI 256

typedef struct {
    int max;
    int count;
    logic_gate **gates;
} logic_circ;


void init_circuit(logic_circ *circ)
{
    circ->gates = (logic_gate**) malloc(CANT_INI * sizeof(logic_circ));
    circ->max = CANT_INI;
    circ->count = 0;
}





void add_gate(logic_circ *circuit, logic_gate *gate)
{
    if (circuit->count == circuit->max) realloc_circuit(circuit);
    //TODO: Se pretende sumar 1 a count, verificar si es correcto o si lo que se esta haciendo es sumar la dir de mem.
    circuit->count++;
    circuit->gates[circuit->count] = gate;
}

int main()
{
    logic_circ lcNot;
    init_circuit(&lcNot);
    logic_gate *not = generate_gate(NOT);
    printf("Arrancamos con esto!!!");
    return 0;
}

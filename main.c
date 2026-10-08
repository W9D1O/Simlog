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

void free_array_logic_gate(logic_gate **array,int count)
{
    if (array != NULL) {
        for (int i = 0; i < count; i++) free_logic_gate(array[i]);
        free(array);
    }
}

void realloc_gate(logic_gate **circuit, int *max)
{
    int nAux = *max;
    (*max) += CANT_INI;
    logic_gate **aux = realloc(*circuit, *max * sizeof(logic_gate*));
    free_array_logic_gate(circuit,nAux);
    circuit = aux;
}


void add_gate(logic_circ *circuit, logic_gate *gate)
{
    if (circuit->count == circuit->max) realloc_gate(circuit->gates,&circuit->max);
    //TODO: Se pretende sumar 1 a count, verificar si es correcto o si lo que se esta haciendo es sumar la dir de mem.
    circuit->count++;
    circuit->gates[circuit->count] = gate;
}


void del_gate(logic_circ *circuit, int pos)
{
    int c = circuit->count;
    if (circuit->gates[pos] != NULL && pos >= 0 && pos < c) {
        free_logic_gate(circuit->gates[pos]);
        /*Estamos considerando lo siguiente: Si el array tiene un solo elemento o si la posicion que
         se quiere eliminar es la ultima posicion no va a entrar en el for pero eso tambien quiere decir
        que no es necesario hacer desplazamientos, solo se debe disminuir el contador.*/
        for (int i = pos; i < circuit->count - 1; i++) *circuit->gates[i] = *circuit->gates[i + 1];

        circuit->count--;
    }

}


int main()
{
    logic_circ lcNot;
    init_circuit(&lcNot);
    /* logic_gate *not = generate_gate(NOT); */
    printf("Arrancamos con esto!!!");
    return 0;
}

#include "gates.h"
#include <stdlib.h>
#include <stdio.h>


/*Recibe un tipo y genera la compuerta logica estandar*/
logic_gate* generate_gate(gate_type type)
{
    logic_gate *gate = (logic_gate*) malloc(sizeof(logic_gate));
    if (gate == NULL) {
        fprintf(stderr,"ERROR MALLOC: No se pudo reservar memoria\n", __LINE__, __FILE__);
        exit(-1);
    }
    if (gate != NULL) {
        if (type == NOT) {
            gate->input = (bool*) malloc(sizeof(bool));
            gate->output = (bool*) malloc(sizeof(bool));
            gate->nInput = 1;
            *gate->input = false;
            //TODO: estas cosas de C me resultan desagradables, averiguar cual es la manera correcta de hacerlo.
            *gate->output = true;
            gate->type = type;
        } else {
            gate->input = (bool*) malloc(2 * sizeof(bool));
            gate->output = (bool*) malloc(sizeof(bool));
            gate->nInput = 2;
            gate->input[0] = false;
            gate->input[1] = false;
            gate->output[0] = false;
            gate->type = type;
        }
    }
}



//TODO: Pensar como si las compuertas binarias van a aceptar mas de dos input.
void and_gate(logic_gate *gate)
{
    *gate->output = gate->input[0] & gate->input[1];
}


void not_gate(logic_gate *gate)
{
    *gate->output = !gate->input[0];

}


void or_gate(logic_gate *gate)
{
    *gate->output = gate->input[0] | gate->input[1];

}


void xor_gate(logic_gate *gate)
{
    *gate->output = gate->input[0] ^ gate->input[1];

}


void nor_gate(logic_gate *gate)
{
    *gate->output = !(gate->input[0] | gate->input[1]);

}


void xnor_gate(logic_gate *gate)
{
    *gate->output = !(gate->input[0] ^ gate->input[1]);

}


void nand_gate(logic_gate *gate)
{
    *gate->output = !(gate->input[0] & gate->input[1]);

}


int set_input(logic_gate *gate, bool input, int nInput)
{
    if (nInput > 0 && nInput <= gate->nInput) gate->input[nInput - 1] = input;
    else {
        fprintf(stderr, "ERROR: El numero de entradas de la compuerta es menor del que se intenta asignar\n",
                __LINE__,__FILE__);
        return -1;
    }
    return 0;
}

void update_output(logic_gate *gate)
{
    switch (gate->type) {
        case NOT:
            not_gate(gate);
            break;
        case OR:
            or_gate(gate);
            break;
        case AND:
            and_gate(gate);
            break;
        case XOR:
            xor_gate(gate);
            break;
        case NOR:
            nor_gate(gate);
            break;
        case NAND:
            nand_gate(gate);
            break;
        case XNOR:
            xnor_gate(gate);
            break;
    }
}

void multiplex(bool *io, logic_gate *gate, int nInput)
{
    int p = nInput - 1;
    if (nInput > 0 && nInput <= gate->nInput) {
        if (gate->input + p != NULL && gate->input + p != io) {
            free(gate->input + p);
            gate->input[p] = io;
        } else if (gate->input + p == NULL) gate->input[p] = io;

    } else {
        fprintf(stderr,"MULTIPLEX ERROR: Numero de entrada invalido. "
                   "El numero de entrada debe ser mayor a cero y menor o igual a la de la compuerta.\n",__LINE__);
        exit(-1);
    }
}

void update_gate(logic_gate *gate, bool input, int nInput)
{
    set_input(gate,input,nInput);
    update_output(gate);
}

void free_logic_gate(logic_gate *gate)
{
    if (gate != NULL) {
        free(gate->output);
        free(gate->input);
        free(gate);
    }
}

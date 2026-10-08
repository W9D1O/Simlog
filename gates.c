#include "gates.h"
#include <stdlib.h>
#include <stdio.h>

int get_bit(int n)
{
    /* Vamos a explicar esto: tengo varias operaciones binaria
     y no puedo usar la misma mascara para todos, definir una mascara para cada uno
    es molesto por lo que estoy desplazando bit, es decir hago normalmente la operacion
    y despues desplazo los bits para quedarme con el valor que me interesa.*/
    int bit = n << 7;
    return (bit >> 7);
}
//TODO: Pensar como si las compuertas binarias van a aceptar mas de dos input.
void and_gate(logic_gate *gate)
{
    if (gate->input[0] != NULL && gate->input[1] != NULL) {
        int byte = *gate->input[0] & *gate->input[1];
        *gate->output = get_bit(byte);
    }
}


void not_gate(logic_gate *gate)
{
    if (gate->input[0] != NULL) {
        int byte = ~(*gate->input[0]);
        *gate->output = get_bit(byte);
    }
}


void or_gate(logic_gate *gate)
{
    if(gate->input[0] != NULL && gate->input[1] != NULL) {
        int byte = *gate->input[0] | *gate->input[1];
        *gate->output = get_bit(byte);
    }
}


void xor_gate(logic_gate *gate)
{
    if (gate->input[0] != NULL && gate->input[1] != NULL) {
        int byte = *gate->input[0] ^ *gate->input[1];
    }    *gate->output = get_bit(byte);
}


void nor_gate(logic_gate *gate)
{
    if (gate->input[0] != NULL && gate->input[1] != NULL) {
        int byte = ~(*gate->input[0] | *gate->input[1]);
        *gate->output = get_bit(byte);
    }
}


void xnor_gate(logic_gate *gate)
{
    if (gate->input[0] != NULL && gate->input[1] != NULL) {
        int byte = ~(*gate->input[0] ^ *gate->input[1]);
        *gate->output = get_bit(byte);
    }
}


void nand_gate(logic_gate *gate)
{
    int byte = ~(*gate->input[0] & *gate->input[1]);
    *gate->output = get_bit(byte);

}



/*Esta en este lugar para poder generar una salida logica al crear una compuerta*/
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


/*Recibe un tipo y genera la compuerta logica estandar*/
logic_gate* generate_gate(gate_type type)
{
    logic_gate *gate = (logic_gate*) malloc(sizeof(logic_gate));
    if (gate == NULL) {
        fprintf(stderr,"ERROR MALLOC: No se pudo reservar memoria %d %s\n", __LINE__, __FILE__);
        exit(-1);
    }
    if (gate != NULL) {
        if (type == NOT) {
            gate->input = (int**) malloc(1 *sizeof(int *));
            gate->output = (int*) malloc(sizeof(int));
            gate->nInput = 1;
            gate->type = type;
        } else {
            gate->input = (int**) malloc(2 * sizeof(int *));
            gate->output = (int*) malloc(sizeof(int));
            gate->nInput = 2;
            gate->type = type;
        }
    }
    /*OJO: Parece que si te olvidas el return C dice algo como 'Tranqui, te doy el puntero igual'
      pero si llamas otra funcion dentro ahi se se acuerda que no hiciste el  return.*/
    return gate;
}




/*Setea un input con un valor*/
int set_input(logic_gate *gate, int input, int nInput)
{
    int pos = nInput - 1;
    if (nInput >= 0 && pos < gate->nInput) {
        if (gate->input[pos] != NULL) *gate->input[pos] = input;
        else {
            gate->input[pos] = (int*) malloc(sizeof(int));
            *gate->input[pos] = input;
        }
    }
    else {
        fprintf(stderr, "ERROR: El numero de entradas de la compuerta es menor del que se intenta asignar %d %s\n",
                __LINE__,__FILE__);
        return -1;
    }
    return 0;
}


/*Recibe un puntero y numero de input, si el input tiene un valor
libera la memoria y compia la direccion de memoria. Si se intenta
copiar la direccion del mismo input se ignora. Si el input ya se encuentra en NULL
simplemente se realiza la copia.*/
void multiplex(int *io, logic_gate *gate, int nInput)
{

    int p = nInput - 1;
    if (nInput > 0 && nInput <= gate->nInput) {
        if (gate->input != NULL && gate->input[p] != io) {
            gate->input[p] = io;
        } else if (gate->input == NULL) {
            //TODO: Considerar la idea de usar unior para generar Input.
            if (gate->type == NOT) {
                gate->input = (int**) malloc(sizeof(int *));
                gate->input[p] = io;
            } else {
                gate->input = (int**) malloc(2 * sizeof(int));
                gate->input[p] = io;
            }
        }

    } else {
        fprintf(stderr,"MULTIPLEX ERROR: Numero de entrada invalido. "
                   "El numero de entrada debe ser mayor a cero y menor o igual a la de la compuerta. %d\n",__LINE__);
        exit(-1);
    }
}


/*Encapsula set_input y update_output*/
void update_gate(logic_gate *gate, int input, int nInput)
{
    set_input(gate,input,nInput);
    update_output(gate);
}


/*Libera la memoria reservada*/
void free_logic_gate(logic_gate *gate)
{
    if (gate != NULL) {
        free(gate->output);
        free(gate->input);
        free(gate);
    }
}

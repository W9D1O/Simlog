#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    NOT,
    OR,
    AND,
    XOR,
    NOR,
    NAND,
    XNOR,
} gate_type; //Buscar un mejor nombre, este se puede confundir con gate_t.


typedef struct {
    bool *input;
    bool *output;
    gate_type type;
} logic_gate;

logic_gate* generate_gate(gate_type type)
{
    logic_gate *gate = (logic_gate*) malloc(sizeof(logic_gate));
    if (gate != NULL) {
        if (type == NOT) {
            gate->input = (bool*) malloc(sizeof(bool));
            gate->output = (bool*) malloc(sizeof(bool));
            gate->input = false;
            //TODO: estas cosas de C me resultan desagradables, averiguar cual es la manera correcta de hacerlo.
            gate->output[0] = true;
            gate->type = type;
        } else {
            gate->input = (bool*) malloc(2 * sizeof(bool));
            gate->output = (bool*) malloc(sizeof(bool));
            gate->input[0] = false;
            gate->input[1] = false;
            gate->output[0] = true;
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
    *gate->output = ~gate->input[0];
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
    *gate->output = ~(gate->input[0] | gate->input[1]);
}


void xnor_gate(logic_gate *gate)
{
    *gate->output = ~(gate->input[0] | gate->input[1]);
}


void nand_gate(logic_gate *gate)
{
    *gate->output = ~(gate->input[0] & gate->input[1]);
}


int set_input(logic_gate *gate, bool input, int nInput)
{
    int len = sizeof(gate->input) / sizeof(gate->input[0]);
    if (nInput >= 0 && nInput < len) gate->input[nInput];
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

int main()
{
    printf("Arrancamos con esto!!!");
    return 0;
}

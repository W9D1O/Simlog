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

void and_gate()
{
}




int main()
{
    printf("Arrancamos con esto!!!");
    return 0;
}

#ifndef GATES_H
#define GATES_H

#define TRUE  1
#define FALSE 0

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
    int **input;
    int *output;
    int nInput; //Agregamos a cantidad de input, porque c no me deja salar la longitud de un array dentro de una funcion.
    gate_type type;
} logic_gate;


logic_gate* generate_gate(gate_type type);

void and_gate(logic_gate *gate);

void not_gate(logic_gate *gate);

void or_gate(logic_gate *gate);

void xor_gate(logic_gate *gate);

void nor_gate(logic_gate *gate);

void xnor_gate(logic_gate *gate);

void nand_gate(logic_gate *gate);

int set_input(logic_gate *gate, int input, int nInput);

void update_output(logic_gate *gate);

void update_gate(logic_gate *gate, int input, int nInput);

void free_logic_gate(logic_gate *gate);

void multiplex(int *io, logic_gate *gate, int nInput);
#endif

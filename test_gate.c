#include "gates.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_not(logic_gate *not)
{
    int *t = malloc(sizeof(int));
    int *f = malloc(sizeof(int));
    *f = FALSE;
    *t = TRUE;
    update_gate(not,*f,1);
    assert(*not->output && "NOT: Recibio false y retorno false");
    update_gate(not,*t,1);
    assert(!(*not->output) && "NOT: Recibio true y retorno true");
}


void test_and(logic_gate *and)
{
    update_gate(and,FALSE,1);
    update_gate(and,FALSE,2);
    assert(!(*and->output) && "AND: Recibio false en ambas entradas y retorno true");
    update_gate(and,TRUE,2);
    assert(!(*and->output) && "AND: Recibio true en una de sus  entradas y retorno true");
    update_gate(and,TRUE,1);
    assert(*and->output && "AND: Recibio true en ambas  entradas y retorno false");
}


void test_or(logic_gate *or)
{
    update_gate(or,FALSE,1);
    update_gate(or,FALSE,2);
    assert(or->input[0] != NULL && or->input[1] != NULL && "No se reservo la memoria\n");
    printf("%d %p\n", *or->input[0], or->output);
    assert(!(*or->output) && "OR: Recibio false en ambas entradas y retorno true");
    update_gate(or,TRUE,2);
    assert(*or->output && "OR: Recibio true en una de sus  entradas y retorno false");
    update_gate(or,TRUE,1);
    assert(*or->output && "OR: Recibio true en ambas  entradas y retorno false");
}



void test_xor(logic_gate *xor)
{
    update_gate(xor,FALSE,1);
    update_gate(xor,FALSE,2);
    assert(!(*xor->output) && "XOR: Recibio false en ambas entradas y retorno true");
    update_gate(xor,TRUE,2);
    assert(*xor->output && "XOR: Recibio true en una de sus  entradas y retorno false");
    update_gate(xor,TRUE,1);
    assert(!(*xor->output) && "XOR: Recibio true en ambas  entradas y retorno true");

}


void test_nand(logic_gate *nand)
{
    update_gate(nand,FALSE,1);
    update_gate(nand,FALSE,2);
    assert(*nand->output && "NAND: Recibio false en ambas entradas y retorno false");
    update_gate(nand,TRUE,2);
    assert(*nand->output &&  "NAND: Recibio true en una de sus  entradas y retorno false");
    update_gate(nand,TRUE,1);
    assert(!(*nand->output) && "NAND: Recibio true en ambas  entradas y retorno true");

}



void test_nor(logic_gate *nor)
{
    update_gate(nor,FALSE,1);
    update_gate(nor,FALSE,2);
    assert(*nor->output && "NOR: Recibio false en ambas entradas y retorno false");
    update_gate(nor,TRUE,2);
    assert(!(*nor->output) && "NOR: Recibio true en una de sus  entradas y retorno true");
    update_gate(nor,TRUE,1);
    assert(!(*nor->output) && "NOR: Recibio true en ambas  entradas y retorno true");

}


void test_xnor(logic_gate *xnor)
{
    update_gate(xnor,FALSE,1);
    update_gate(xnor,FALSE,2);
    assert(*xnor->output &&  "XNOR: Recibio false en ambas entradas y retorno false");
    update_gate(xnor,TRUE,2);
    assert(!(*xnor->output) && "XNOR: Recibio true en una de sus  entradas y retorno true");
    update_gate(xnor,TRUE,1);
    assert(*xnor->output && "XNOR: Recibio true en ambas  entradas y retorno false");

}

/*Es mejorable pero por el momento basta.*/
int main()
{
    logic_gate *not = generate_gate(NOT);
    logic_gate *or = generate_gate(OR);
    logic_gate *and = generate_gate(AND);
    /* logic_gate *xor = generate_gate(XOR); */
    /* logic_gate *nor = generate_gate(NOR); */
    /* logic_gate *nand = generate_gate(NAND); */
    /* logic_gate *xnor = generate_gate(XNOR); */
    /* test_not(not); */
    test_or(or);
    /* test_and(and); */
    /* test_xor(xor); */
    /* test_nor(nor); */
    /* test_nand(nand); */
    /* test_xnor(xnor); */
    return 0;

}

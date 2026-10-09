#include "gates.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_not(logic_gate *not)
{

    printf("TEST NOT: 0/2\n");
    update_gate(not,FALSE,1);
    assert(*not->output && "NOT: Recibio false y retorno false\n");
    printf("TEST NOT: 1/2\n");
    update_gate(not,TRUE,1);
    assert(!(*not->output) && "NOT: Recibio true y retorno true\n");
    printf("TEST NOT: 2/2\n");

}


void test_and(logic_gate *and)
{
    printf("TEST AND: 0/3\n");
    update_gate(and,FALSE,1);
    update_gate(and,FALSE,2);
    assert(!(*and->output) && "AND: Recibio false en ambas entradas y retorno true\n");
    printf("TEST AND: 1/3\n");
    update_gate(and,TRUE,2);
    assert(!(*and->output) && "AND: Recibio true en una de sus  entradas y retorno true\n");
    printf("TEST AND: 2/3\n");
    update_gate(and,TRUE,1);
    assert(*and->output && "AND: Recibio true en ambas  entradas y retorno false\n");
    printf("TEST AND: 3/3\n");

}


void test_or(logic_gate *or)
{
    printf("TEST OR: 0/3\n");
    update_gate(or,FALSE,1);
    update_gate(or,FALSE,2);
    assert(!(*or->output) && "OR: Recibio false en ambas entradas y retorno true\n");
    printf("TEST OR: 1/3\n");
    update_gate(or,TRUE,2);
    assert(*or->output && "OR: Recibio true en una de sus  entradas y retorno false\n");
    printf("TEST OR: 2/3\n");
    update_gate(or,TRUE,1);
    assert(*or->output && "OR: Recibio true en ambas  entradas y retorno false\n");
    printf("TEST OR: 3/3\n");
}



void test_xor(logic_gate *xor)
{
    printf("TEST XOR: 0/3\n");
    update_gate(xor,FALSE,1);
    update_gate(xor,FALSE,2);
    assert(!(*xor->output) && "XOR: Recibio false en ambas entradas y retorno true\n");
    printf("TEST XOR: 1/3\n");
    update_gate(xor,TRUE,2);
    assert(*xor->output && "XOR: Recibio true en una de sus  entradas y retorno false\n");
    printf("TEST XOR: 2/3\n");
    update_gate(xor,TRUE,1);
    assert(!(*xor->output) && "XOR: Recibio true en ambas  entradas y retorno true\n");
    printf("TEST XOR: 3/3\n");


}


void test_nand(logic_gate *nand)
{
    printf("TEST NAND: 0/3\n");
    update_gate(nand,FALSE,1);
    update_gate(nand,FALSE,2);
    assert(*nand->output && "NAND: Recibio false en ambas entradas y retorno false\n");
    printf("TEST NAND: 1/3\n");
    update_gate(nand,TRUE,2);
    assert(*nand->output &&  "NAND: Recibio true en una de sus  entradas y retorno false\n");
    printf("TEST NAND: 2/3\n");
    update_gate(nand,TRUE,1);
    assert(!(*nand->output) && "NAND: Recibio true en ambas  entradas y retorno true\n");
    printf("TEST NAND: 3/3\n");


}



void test_nor(logic_gate *nor)
{
    printf("TEST NOR: 0/3\n");
    update_gate(nor,FALSE,1);
    update_gate(nor,FALSE,2);
    assert(*nor->output && "NOR: Recibio false en ambas entradas y retorno false\n");
    printf("TEST NOR: 1/3\n");
    update_gate(nor,TRUE,2);
    assert(!(*nor->output) && "NOR: Recibio true en una de sus  entradas y retorno true\n");
    update_gate(nor,TRUE,1);
    printf("TEST NOR: 2/3\n");
    assert(!(*nor->output) && "NOR: Recibio true en ambas  entradas y retorno true\n");
    printf("TEST NOR: 3/3\n");

}


void test_xnor(logic_gate *xnor)
{
    printf("TEST XNOR: 0/3\n");
    update_gate(xnor,FALSE,1);
    update_gate(xnor,FALSE,2);
    assert(*xnor->output &&  "XNOR: Recibio false en ambas entradas y retorno false\n");
    printf("TEST XNOR: 1/3\n");
    update_gate(xnor,TRUE,2);
    assert(!(*xnor->output) && "XNOR: Recibio true en una de sus  entradas y retorno true\n");
    printf("TEST XNOR: 2/3\n");
    update_gate(xnor,TRUE,1);
    assert(*xnor->output && "XNOR: Recibio true en ambas  entradas y retorno false\n");
    printf("TEST XNOR: 3/3\n");
}

/*Es mejorable pero por el momento basta.*/
int main()
{
    logic_gate *not = generate_gate(NOT);
    logic_gate *or = generate_gate(OR);
    logic_gate *and = generate_gate(AND);
    logic_gate *xor = generate_gate(XOR);
    logic_gate *nor = generate_gate(NOR);
    logic_gate *nand = generate_gate(NAND);
    logic_gate *xnor = generate_gate(XNOR);
    test_not(not);
    test_or(or);
    test_and(and);
    test_xor(xor);
    test_nor(nor);
    test_nand(nand);
    test_xnor(xnor);
    printf("Todos los test fueron exitosos. Sentite increiblemente poderoso!!!!\n");
    return 0;

}

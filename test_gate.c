#include "gates.h"
#include <stdio.h>
#include <assert.h>

void test_not(logic_gate *not)
{
    update_gate(not,false,1);
    assert(*not->output && "NOT: Recibio false y retorno false");
    update_gate(not,true,1);
    assert(!(*not->output) && "NOT: Recibio true y retorno true");
}


void test_and(logic_gate *and)
{
    update_gate(and,false,1);
    update_gate(and,false,2);
    assert(!(*and->output) && "AND: Recibio false en ambas entradas y retorno true");
    update_gate(and,true,2);
    assert(!(*and->output) && "AND: Recibio true en una de sus  entradas y retorno true");
    update_gate(and,true,1);
    assert(*and->output && "AND: Recibio true en ambas  entradas y retorno false");
}


void test_or(logic_gate *or)
{
    update_gate(or,false,1);
    update_gate(or,false,2);
    assert(!(*or->output) && "OR: Recibio false en ambas entradas y retorno true");
    update_gate(or,true,2);
    assert(*or->output && "OR: Recibio true en una de sus  entradas y retorno false");
    update_gate(or,true,1);
    assert(*or->output && "OR: Recibio true en ambas  entradas y retorno false");
}



void test_xor(logic_gate *xor)
{
    update_gate(xor,false,1);
    update_gate(xor,false,2);
    assert(!(*xor->output) && "XOR: Recibio false en ambas entradas y retorno true");
    update_gate(xor,true,2);
    assert(*xor->output && "XOR: Recibio true en una de sus  entradas y retorno false");
    update_gate(xor,true,1);
    assert(!(*xor->output) && "XOR: Recibio true en ambas  entradas y retorno true");

}


void test_nand(logic_gate *nand)
{
    update_gate(nand,false,1);
    update_gate(nand,false,2);
    assert(*nand->output && "NAND: Recibio false en ambas entradas y retorno false");
    update_gate(nand,true,2);
    assert(*nand->output &&  "NAND: Recibio true en una de sus  entradas y retorno false");
    update_gate(nand,true,1);
    assert(!(*nand->output) && "NAND: Recibio true en ambas  entradas y retorno true");

}



void test_nor(logic_gate *nor)
{
    update_gate(nor,false,1);
    update_gate(nor,false,2);
    assert(*nor->output && "NOR: Recibio false en ambas entradas y retorno false");
    update_gate(nor,true,2);
    assert(!(*nor->output) && "NOR: Recibio true en una de sus  entradas y retorno true");
    update_gate(nor,true,1);
    assert(!(*nor->output) && "NOR: Recibio true en ambas  entradas y retorno true");

}


void test_xnor(logic_gate *xnor)
{
    update_gate(xnor,false,1);
    update_gate(xnor,false,2);
    assert(*xnor->output &&  "XNOR: Recibio false en ambas entradas y retorno false");
    update_gate(xnor,true,2);
    assert(!(*xnor->output) && "XNOR: Recibio true en una de sus  entradas y retorno true");
    update_gate(xnor,true,1);
    assert(*xnor->output && "XNOR: Recibio true en ambas  entradas y retorno false");

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
    return 0;

}

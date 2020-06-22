/*
// Created by hn on 6/18/20.
*/

#include <stdlib.h>
#include "cpp2c_defs_poly.h"

extern funPtr MultiplierVTable[2];

void doPrePostFixer()
{
    PrePostFixer angleBrackets;

    printf("\n--- start doPrePostFixer() ---\n\n");

    PrePostFixer_CTOR_kcpkcp(&angleBrackets, "<<< ", " >>>");
    PrePostFixer_print_kcp(&angleBrackets, "Hello World!");
    PrePostFixer_print_lc(&angleBrackets, -777, '\0');
    PrePostFixer_print_lc(&angleBrackets, 350, '#');
    PrePostFixer_print_lc(&angleBrackets, (long int)3.14, '\0');

    printf("\n--- end doPrePostFixer() ---\n\n");

    angleBrackets.defaultTextFormatter.textFormatter._vptr[0](&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;

    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer_CTOR_kcpkcp(&asterisks, "***** ", " *****");
    PrePostDollarFixer_print_ic(&asterisks, -777, '$');
    PrePostDollarFixer_print_ic(&asterisks, 350, '#');
    PrePostDollarFixer_print_dc(&asterisks, 3.14f, '$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer_DTOR(&asterisks);
}

void doPrePostChecker()
{
    PrePostChecker check;
    printf("\n--- start doPrePostChecker() ---\n\n");

    PrePostChecker_CTOR(&check);
    PrePostChecker_printThisSymbolUsingFunc(&check);
    PrePostChecker_printThisSymbolDirectly(&check);
    PrePostChecker_printDollarSymbolByCastDirectly(&check);
    PrePostChecker_printDollarSymbolByScopeDirectly(&check);
    PrePostChecker_printDollarSymbolByCastUsingFunc(&check);
    PrePostChecker_printDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");
    PrePostChecker_DTOR(&check);
}

void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer_CTOR_kcpkcp(&hashes, "### ", " ###");
    PrePostFloatDollarFixer_print_f(&hashes, -777);
    PrePostFloatDollarFixer_print_fc(&hashes, 350, '#');
    PrePostFloatDollarFixer_print_f(&hashes, 3.14f);

    PrePostDollarFixer_CTOR_kPrePostDollarFixerp(&hashes2, (PrePostDollarFixer*)&hashes);
    PrePostDollarFixer_print_dc(&hashes2, 7.5, '$');
    PrePostDollarFixer_print_ic(&hashes2, 100, '$');

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostDollarFixer_DTOR(&hashes2);
    PrePostFloatDollarFixer_DTOR(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer* pp){
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    pp -> defaultTextFormatter.textFormatter._vptr[2](pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer* pp){
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    PrePostDollarFixer_print_ic((PrePostDollarFixer*)pp, 123, '$');

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    PrePostDollarFixer_print_ic(&pp, 123, '$');

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}

void runAsPrePostHashFixerRef(const PrePostHashFixer* pp){
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

    PrePostHashFixer_print_ic(pp, 123, '#');

    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier() {
    Multiplier m1, m2, m3, m4;
    printf("\n--- start doMultiplier() ---\n\n");

    DefaultTextFormatter_CTOR((DefaultTextFormatter*)&m1);
    m1.DefaultTextFormatter.textFormatter._vptr = MultiplierVTable;
    m1.times = 3;
    printf("--- Multiplier CTOR: times = %d\n", 3);

    DefaultTextFormatter_CTOR((DefaultTextFormatter*)&m2);
    m2.DefaultTextFormatter.textFormatter._vptr = MultiplierVTable;
    m2.times = 5;
    printf("--- Multiplier CTOR: times = %d\n", 5);

    DefaultTextFormatter_CTOR_kDefaultTextFormatter((DefaultTextFormatter*)&m3, (DefaultTextFormatter*)&m1);
    m3.DefaultTextFormatter.textFormatter._vptr = m1.DefaultTextFormatter.textFormatter._vptr;
    m3.times = m1.times;

    DefaultTextFormatter_CTOR_kDefaultTextFormatter((DefaultTextFormatter*)&m4, (DefaultTextFormatter*)&m2);
    m4.DefaultTextFormatter.textFormatter._vptr = m2.DefaultTextFormatter.textFormatter._vptr;
    m4.times = m2.times;

    Multiplier_print_kcp(&m1, "abc ");
    Multiplier_print_kcp(&m2, "abc ");
    Multiplier_print_kcp(&m3, "abc ");
    Multiplier_print_kcp(&m4, "abc ");

    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier_Dtor(&m4);
    Multiplier_Dtor(&m3);
    Multiplier_Dtor(&m2);
    Multiplier_Dtor(&m1);

}

void doFormatterArray(){
    PrePostDollarFixer prePostDollarFixer;
    Multiplier multiplier;
    PrePostChecker prePostChecker;
    DefaultTextFormatter formatters[3];
    int i;

    printf("\n--- start doFormatterArray() ---\n\n");

    PrePostDollarFixer_CTOR_kcpkcp(&prePostDollarFixer, "!!! ", " !!!");
    DefaultTextFormatter_CTOR_kDefaultTextFormatter(&formatters[0], (DefaultTextFormatter*)&prePostDollarFixer);
    PrePostDollarFixer_DTOR(&prePostDollarFixer);

    DefaultTextFormatter_CTOR((DefaultTextFormatter*)&multiplier);
    multiplier.DefaultTextFormatter.textFormatter._vptr = MultiplierVTable;
    multiplier.times = 4;
    printf("--- Multiplier CTOR: times = %d\n", 4);

    DefaultTextFormatter_CTOR_kDefaultTextFormatter(&formatters[1], (DefaultTextFormatter*)&multiplier);
    Multiplier_Dtor(&multiplier);

    PrePostChecker_CTOR(&prePostChecker);
    DefaultTextFormatter_CTOR_kDefaultTextFormatter(&formatters[2], (DefaultTextFormatter*)&prePostChecker);
    PrePostChecker_DTOR(&prePostChecker);

    for (i = 0; i < 3; ++i)
        DefaultTextFormatter_print_kcp(&formatters[i], "Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");

    for (i = 2; i >= 0; --i) {
        DefaultTextFormatter_DTOR(&formatters[i]);
    }
}

void doFormatterPtrs()
{
    DefaultTextFormatter* pfmt[3];
    int i;

    printf("\n--- start doFormatterPtrs() ---\n\n");

    pfmt[0] = malloc(sizeof(PrePostDollarFixer));
    PrePostDollarFixer_CTOR_kcpkcp((PrePostDollarFixer*)pfmt[0], "!!! ", " !!!");

    pfmt[1] = malloc(sizeof(Multiplier));
    DefaultTextFormatter_CTOR((DefaultTextFormatter*)pfmt[1]);
    ((Multiplier*)pfmt[1])->DefaultTextFormatter.textFormatter._vptr = MultiplierVTable;
    ((Multiplier*)pfmt[1])->times = 4;
    printf("--- Multiplier CTOR: times = %d\n", 4);

    pfmt[2] = malloc(sizeof(PrePostChecker));
    PrePostChecker_CTOR((PrePostChecker*)pfmt[2]);

    for (i = 0; i < 3; ++i)
        pfmt[i]->textFormatter._vptr[1](pfmt[i], "Hello World!");

    for (i = 2; i >= 0; --i) {
        pfmt[i]->textFormatter._vptr[0](pfmt[i]);
        free(pfmt[i]);
    }

    printf("\n--- end doFormatterPtrs() ---\n\n");
}

void doFormatterDynamicArray()
{
    DefaultTextFormatter* formatters;
    int i;

    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    formatters = generateFormatterArray();

    for (i = 0; i < 3; ++i)
        formatters[i].textFormatter._vptr[1](&formatters[i], "Hello World!");

    for (i = 2; i >= 0; --i)
        formatters[i].textFormatter._vptr[0](&formatters[i]);

    free(formatters);

    printf("\n--- start doFormatterDynamicArray() ---\n\n");
}

int main()
{
    PrePostHashFixer hfix;
    PrePostDollarFixer tmp;
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();
    doPrePostDollarFixer();
    doPrePostFloatDollarFixer();
    doPrePostChecker();

    PrePostHashFixer_CTOR_i(&hfix, 4);
    runAsPrePostFixerRef((PrePostFixer*)&hfix);
    runAsPrePostDollarFixerRef((PrePostDollarFixer*)&hfix);

    PrePostDollarFixer_CTOR_kPrePostDollarFixerp(&tmp, (PrePostDollarFixer*)&hfix);
    runAsPrePostDollarFixerObj(tmp);
    PrePostDollarFixer_DTOR(&tmp);
    runAsPrePostHashFixerRef(&hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");

    PrePostHashFixer_DTOR(&hfix);

    return 0;
}


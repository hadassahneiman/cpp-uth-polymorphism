/*
// Created by hn on 6/18/20.
*/

#include "cpp2c_defs_poly.h"

void doPrePostFixer()
{
    PrePostFixer angleBrackets;

    printf("\n--- start doPrePostFixer() ---\n\n");

    /*PrePostFixer angleBrackets("<<< ", " >>>");
    angleBrackets.print("Hello World!");
    angleBrackets.print(-777);
    angleBrackets.print(350, '#');
    angleBrackets.print(static_cast<long int>(3.14));*/

    PrePostFixer_CTOR_kcpkcp(&angleBrackets, "<<< ", " >>>");
    PrePostFixer_print_kcp(&angleBrackets, "Hello World!");
    PrePostFixer_print_lc(&angleBrackets, (long int)-777, '\0');
    PrePostFixer_print_lc(&angleBrackets, 350, '#');
    PrePostFixer_print_lc(&angleBrackets, (long int)3.14, '\0');

    printf("\n--- end doPrePostFixer() ---\n\n");

    angleBrackets.defaultTextFormatter.textFormatter._vptr[0](&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;

    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    /*PrePostDollarFixer asterisks("***** ", " *****");
    asterisks.print(-777);
    asterisks.print(350, '#');
    asterisks.print(3.14f);*/

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

    Multiplier_CTOR_i(&m1, 3);
    Multiplier_CTOR_i(&m2, 5);

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

    Multiplier_CTOR_i(&multiplier, 4);
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
/*
void doFormatterPtrs()
{
    printf("\n--- start doFormatterPtrs() ---\n\n");

    DefaultTextFormatter* pfmt[] =
    {
        new PrePostDollarFixer("!!! ", " !!!"),
        new Multiplier(4),
        new PrePostChecker()
    };

    for (int i = 0; i < 3; ++i)
        pfmt[i]->print("Hello World!");

    for (int i = 2; i >= 0; --i)
        delete pfmt[i];

    printf("\n--- end doFormatterPtrs() ---\n\n");
}

void doFormatterDynamicArray()
{
    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    DefaultTextFormatter* formatters = generateFormatterArray();

    for (int i = 0; i < 3; ++i)
        formatters[i].print("Hello World!");

    delete[] formatters;

    printf("\n--- start doFormatterDynamicArray() ---\n\n");
}*/

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
    /*doFormatterPtrs();
    doFormatterDynamicArray();*/

    printf("\n--- End main() ---\n\n");

    return 0;
}


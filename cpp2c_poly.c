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

    angleBrackets._vptr[0](&angleBrackets);
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
/*
void doPrePostChecker()
{
    printf("\n--- start doPrePostChecker() ---\n\n");

    PrePostChecker check;
    check.printThisSymbolUsingFunc();
    check.printThisSymbolDirectly();
    check.printDollarSymbolByCastDirectly();
    check.printDollarSymbolByScopeDirectly();
    check.printDollarSymbolByCastUsingFunc();
    check.printDollarSymbolByScopeUsingFunc();

    printf("\n--- end doPrePostChecker() ---\n\n");
}

void doPrePostFloatDollarFixer()
{
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer hashes("### ", " ###");
    hashes.print(-777);
    hashes.print(350, '#');
    hashes.print(3.14f);

    PrePostDollarFixer hashes2(hashes);
    hashes2.print(7.5);
    hashes2.print(100);

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");
}

void runAsPrePostFixerRef(const PrePostFixer& pp)
{
printf("\n--- start runAsPrePostFixerRef() ---\n\n");

pp.print(123);

printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer& pp)
{
printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

pp.print(123);

printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    pp.print(123);

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}

void runAsPrePostHashFixerRef(const PrePostHashFixer& pp)
{
printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

pp.print(123);

printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier()
{
    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier m1(3);
    Multiplier m2 = 5;
    Multiplier m3 = m1;
    Multiplier m4(m2);

    m1.print("abc ");
    m2.print("abc ");
    m3.print("abc ");
    m4.print("abc ");

    printf("\n--- start doMultiplier() ---\n\n");
}

void doFormatterArray()
{
    printf("\n--- start doFormatterArray() ---\n\n");

    DefaultTextFormatter formatters[] =
            {
                    PrePostDollarFixer("!!! ", " !!!"),
                    Multiplier(4),
                    PrePostChecker()
            };

    for (int i = 0; i < 3; ++i)
        formatters[i].print("Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");
}

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
    printf("\n--- Start main() ---\n\n");

    doPrePostFixer();
    doPrePostDollarFixer();
    /*doPrePostFloatDollarFixer();
    doPrePostChecker();

    PrePostHashFixer hfix;
    runAsPrePostFixerRef(hfix);
    runAsPrePostDollarFixerRef(hfix);
    runAsPrePostDollarFixerObj(hfix);
    runAsPrePostHashFixerRef(hfix);

    doMultiplier();

    doFormatterArray();
    doFormatterPtrs();
    doFormatterDynamicArray();*/

    printf("\n--- End main() ---\n\n");

    return 0;
}


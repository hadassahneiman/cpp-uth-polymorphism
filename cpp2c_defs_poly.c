/*
// Created by hn on 6/18/20.
*/

#include <stdlib.h>
#include "cpp2c_defs_poly.h"

/************TextFormatter************/

funPtr TextFormatterVTable[] = {TextFormatter_DTOR, TextFormatter_print_kcp};

void TextFormatter_DTOR(TextFormatter* const this){}

void TextFormatter_print_kcp(const TextFormatter* const this, const char* text){}

/***********DefaultTextFormatter************/

funPtr DefaultTextFormatterVTable[] = {DefaultTextFormatter_DTOR, DefaultTextFormatter_print_kcp};

int next_id = 0;

void DefaultTextFormatter_CTOR(DefaultTextFormatter* const this){

    this -> textFormatter._vptr = DefaultTextFormatterVTable;

    this -> id = next_id++;
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this -> id);
}

void DefaultTextFormatter_CTOR_kDefaultTextFormatter(DefaultTextFormatter* const this, const DefaultTextFormatter* other){

    this -> textFormatter._vptr = other ->textFormatter._vptr;

    this -> id = next_id++;
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other -> id, this -> id);
}

DefaultTextFormatter DefaultTextFormatter_As_kDefaultTextFormatter(DefaultTextFormatter* const this, const DefaultTextFormatter* other){

    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other -> id, this -> id);
    return *this;
}

void DefaultTextFormatter_DTOR(DefaultTextFormatter* const this){

    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this -> id);
    this -> textFormatter._vptr = TextFormatterVTable;
    TextFormatter_DTOR((TextFormatter*)this);
}

void DefaultTextFormatter_print_kcp(const DefaultTextFormatter* const this, const char* text){

    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray(){
    DefaultTextFormatter* formatter = malloc(sizeof(DefaultTextFormatter)*3);
    int i;

    for(i = 0; i < 3; ++i)
        DefaultTextFormatter_CTOR(formatter + i);

    return formatter;
}

/***********PrePostFixer************/

funPtr PrePostFixerVTable[] = {PrePostFixer_DTOR, PrePostFixer_print_kcp,
                               (funPtr) PrePostFixer_print_lc, (funPtr) PrePostFixer_getDefaultSymbol};

void PrePostFixer_CTOR_kcpkcp(PrePostFixer* const this, const char* prefix, const char* postfix){

    DefaultTextFormatter_CTOR((DefaultTextFormatter*)this);

    this -> defaultTextFormatter.textFormatter._vptr = PrePostFixerVTable;

    this -> pre = prefix;
    this -> post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", prefix, postfix);
}

void PrePostFixer_DTOR(PrePostFixer* const this){

    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this -> pre, this -> post);
    this -> defaultTextFormatter.textFormatter._vptr = DefaultTextFormatterVTable;
    DefaultTextFormatter_DTOR((DefaultTextFormatter*)this);
}

void PrePostFixer_print_kcp(const PrePostFixer* const this, const char* text){

    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", this -> pre, text, this -> post);
}

void PrePostFixer_print_lc(const PrePostFixer* const this, long num, char symbol){

    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    if (symbol) {
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", this -> pre, symbol, num, this -> post);
    }
    else {
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", this -> pre, num, this ->  post);
    }
}

char PrePostFixer_getDefaultSymbol(const PrePostFixer* const this){
    return '\0';
}

/*************PrePostDollarFixer***********/

funPtr PrePostDollarFixerVTable[] = {PrePostDollarFixer_DTOR, PrePostFixer_print_kcp,
                                     (funPtr)PrePostDollarFixer_print_lc, (funPtr)PrePostDollarFixer_getDefaultSymbol};

void PrePostDollarFixer_CTOR_kcpkcp(PrePostDollarFixer* const this, const char* prefix, const char* postfix){

    PrePostFixer_CTOR_kcpkcp((PrePostFixer*)this, prefix, postfix);

    this -> prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", prefix, postfix);
}

void PrePostDollarFixer_CTOR_kPrePostDollarFixerp(PrePostDollarFixer* const this, const PrePostDollarFixer* other){

    this -> prePostFixer.pre = other->prePostFixer.pre;
    this -> prePostFixer.post = other->prePostFixer.post;
    DefaultTextFormatter_CTOR_kDefaultTextFormatter((DefaultTextFormatter*)this, (DefaultTextFormatter*)other);

    this -> prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this -> prePostFixer.pre, this -> prePostFixer.post);
}

void PrePostDollarFixer_DTOR(PrePostDollarFixer* const this){

    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", this -> prePostFixer.pre, this -> prePostFixer.post);
    this -> prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostFixerVTable;
    PrePostFixer_DTOR((PrePostFixer*)this);
}

void PrePostDollarFixer_print_ic(const PrePostDollarFixer* const this, int num, char symbol){

    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    this -> prePostFixer.defaultTextFormatter.textFormatter._vptr[2](this, (long)num, symbol);
}

void PrePostDollarFixer_print_lc(const PrePostDollarFixer* const this, long num, char symbol){

    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");

    PrePostFixer_print_lc((PrePostFixer*)this, num, symbol);
}

void PrePostDollarFixer_print_dc(const PrePostDollarFixer* const this, double num, char symbol){

    printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", this -> prePostFixer.pre, symbol, num, this -> prePostFixer.post);
}

char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer* const this){

    return '$';
}

/************PrePostHashFixer**************/

funPtr PrePostHashFixerVTable[] = {PrePostHashFixer_DTOR, PrePostFixer_print_kcp,
                                   (funPtr)PrePostHashFixer_print_lc, (funPtr)PrePostHashFixer_getDefaultSymbol};

void PrePostHashFixer_CTOR_i(PrePostHashFixer* const this, int prc){

    PrePostDollarFixer_CTOR_kcpkcp((PrePostDollarFixer*)this, "===> ", " <===");

    this -> prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostHashFixerVTable;

    this -> precision = prc;

    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", "===> ", " <===", prc);

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", "===> ", '#', prc, 9999.9999, " <===");
}

void PrePostHashFixer_DTOR(PrePostHashFixer* const this){

    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this -> prePostDollarFixer.prePostFixer.pre,
            this -> prePostDollarFixer.prePostFixer.post);

    this -> prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostDollarFixerVTable;
    PrePostDollarFixer_DTOR((PrePostDollarFixer*)this);
}

void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol){

    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this -> prePostDollarFixer.prePostFixer.pre, symbol, this -> precision,
           (double)num, this -> prePostDollarFixer.prePostFixer.post);
}

void PrePostHashFixer_print_lc(const PrePostHashFixer* const this, long num, char symbol){

    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this -> prePostDollarFixer.prePostFixer.pre, symbol, this -> precision,
           (double)num, this -> prePostDollarFixer.prePostFixer.post);
}

char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this){
    return '#';
}

/***********PrePostFloatDollarFixer************/

funPtr PrePostFloatDollarFixerVTable[] = {PrePostFloatDollarFixer_DTOR, PrePostFixer_print_kcp,
                                          (funPtr)PrePostDollarFixer_print_lc, (funPtr)PrePostFloatDollarFixer_getDefaultSymbol};

void PrePostFloatDollarFixer_CTOR_kcpkcp(PrePostFloatDollarFixer* const this, char* prefix, const char* postfix){
    PrePostDollarFixer_CTOR_kcpkcp((PrePostDollarFixer*)this, prefix, postfix);

    this -> prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostFloatDollarFixerVTable;

    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", prefix, postfix);
}

void PrePostFloatDollarFixer_DTOR(PrePostFloatDollarFixer* const this){
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", this -> prePostDollarFixer.prePostFixer.pre,
            this -> prePostDollarFixer.prePostFixer.post);

    this -> prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostDollarFixerVTable;

    PrePostDollarFixer_DTOR((PrePostDollarFixer*)this);
}

void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer* const this, float num){
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");

    PrePostFloatDollarFixer_print_fc(this, num, '@');
}

void PrePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer* const this, float num, char symbol){

    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float, char)]");

    printf("%s%c%.2f%s\n", this -> prePostDollarFixer.prePostFixer.pre, symbol, num, this -> prePostDollarFixer.prePostFixer.post);
}

char PrePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer* const this){
    return '@';
}

/**********PrePostChecker***********/

funPtr PrePostCheckerVTable[] = {PrePostChecker_DTOR, PrePostFixer_print_kcp,
                                 (funPtr)PrePostDollarFixer_print_lc, (funPtr)PrePostFloatDollarFixer_getDefaultSymbol};

void PrePostChecker_CTOR(PrePostChecker* const this){
    PrePostFloatDollarFixer_CTOR_kcpkcp((PrePostFloatDollarFixer*)this, "[[[[ ", " ]]]]");

    this -> prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostCheckerVTable;

    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", "[[[[ ", " ]]]]");
}

void PrePostChecker_DTOR(PrePostChecker* const this){
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.pre,
            this -> prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.post);

    this -> prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter._vptr = PrePostDollarFixerVTable;

    PrePostFloatDollarFixer_DTOR((PrePostFloatDollarFixer*)this);
}

void PrePostChecker_printThisSymbolUsingFunc(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");

    printf("Default symbol is %c\n", ((char(*)())this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter
            .textFormatter._vptr[3])((PrePostFloatDollarFixer*)this));
}

void PrePostChecker_printThisSymbolDirectly(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", '@');
}

void PrePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");

    printf("Default symbol is %c\n", ((char(*)())((PrePostDollarFixer*)this) -> prePostFixer.defaultTextFormatter
            .textFormatter._vptr[3])(this));
}

void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this){

    printf("%-60s | ",  "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_getDefaultSymbol((PrePostDollarFixer*)this));
}

void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker* const this){
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", '$');
}

void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker* const this){

    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", '$');
}

/********Multiplier***************/

funPtr MultiplierVTable[] = {Multiplier_Dtor, Multiplier_print_kcp};

void Multiplier_Dtor(Multiplier* const this){
    printf("--- Multiplier DTOR: times = %d\n", this->times);

    this ->DefaultTextFormatter.textFormatter._vptr = DefaultTextFormatterVTable;

    DefaultTextFormatter_DTOR((DefaultTextFormatter*)this);
}

void Multiplier_print_kcp(const Multiplier* const this, const char* text){
    int i;
    printf("%-60s | ", "[Multiplier::print(const char*)]");

    for (i = 0; i < this -> times; ++i)
        printf("%s", text);

    printf("\n");
}

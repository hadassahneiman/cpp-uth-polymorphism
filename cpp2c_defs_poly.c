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

    this -> _vptr = DefaultTextFormatterVTable;

    this -> id = next_id++;
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this -> id);
}

void DefaultTextFormatter_CTOR_kDefaultTextFormatter(DefaultTextFormatter* const this, const DefaultTextFormatter* other){

    this -> _vptr = TextFormatterVTable;

    this -> id = next_id++;
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other -> id, this -> id);
}

DefaultTextFormatter DefaultTextFormatter_As_kDefaultTextFormatter(DefaultTextFormatter* const this, const DefaultTextFormatter* other){

    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other -> id, this -> id);
    return *this;
}

void DefaultTextFormatter_DTOR(DefaultTextFormatter* const this){

    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this -> id);
    TextFormatter_DTOR((TextFormatter*)this);
}

void DefaultTextFormatter_print_kcp(const DefaultTextFormatter* const this, const char* text){

    printf("%-60s | ", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray(){
    return malloc(sizeof(DefaultTextFormatter)*3);
}

/***********PrePostFixer************/

funPtr PrePostFixerVTable[] = {PrePostFixer_DTOR, PrePostFixer_print_kcp,
                               (funPtr) PrePostFixer_print_lc, (funPtr) PrePostFixer_getDefaultSymbol};

void PrePostFixer_CTOR_kcpkcp(PrePostFixer* const this, const char* prefix, const char* postfix){

    DefaultTextFormatter_CTOR(&this -> defaultTextFormatter);

    this -> _vptr = PrePostFixerVTable;

    this -> pre = prefix;
    this -> post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this -> pre, this -> post);
}

void PrePostFixer_DTOR(PrePostFixer* const this){

    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this -> pre, this -> post);
    DefaultTextFormatter_DTOR(&this -> defaultTextFormatter);
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
        printf("%s%ld%s\n", this -> pre, num,this ->  post);
    }
}

char PrePostFixer_getDefaultSymbol(const PrePostFixer* const this){
    return '\0';
}

/*************PrePostDollarFixer***********/

funPtr PrePostDollarFixerVTable[] = {PrePostDollarFixer_DTOR, PrePostFixer_print_kcp,
                                     (funPtr)PrePostDollarFixer_print_lc, (funPtr)PrePostDollarFixer_getDefaultSymbol};

void PrePostDollarFixer_CTOR_kcpkcp(PrePostDollarFixer* const this, const char* prefix, const char* postfix){

    PrePostFixer_CTOR_kcpkcp(&this -> prePostFixer, prefix, postfix);

    this -> _vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", this -> prePostFixer.pre, this -> prePostFixer.post);
}

void PrePostDollarFixer_CTOR_kPrePostDollarFixerp(PrePostDollarFixer* const this, const PrePostDollarFixer* other){

    this -> prePostFixer.pre = other->prePostFixer.pre;
    this -> prePostFixer.post = other->prePostFixer.post;

    this -> _vptr = PrePostDollarFixerVTable;

    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this -> prePostFixer.pre, this -> prePostFixer.post);
}

void PrePostDollarFixer_DTOR(PrePostDollarFixer* const this){

    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", this -> prePostFixer.pre, this -> prePostFixer.post);
    PrePostFixer_DTOR(&this -> prePostFixer);
}

void PrePostDollarFixer_print_ic(const PrePostDollarFixer* const this, int num, char symbol){

    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    PrePostDollarFixer_print_lc(this, (long)num, symbol);
}

void PrePostDollarFixer_print_lc(const PrePostDollarFixer* const this, long num, char symbol){

    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");

    PrePostFixer_print_lc(&this -> prePostFixer, num, symbol);
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

    this -> _vptr = PrePostHashFixerVTable;

    PrePostDollarFixer_CTOR_kcpkcp(&this -> prePostDollarFixer, "===> ", " <===");
    this -> precision = prc;

    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", "===> ", " <===", prc);

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this -> prePostDollarFixer.prePostFixer.pre, '#', this -> precision,
           9999.9999, this -> prePostDollarFixer.prePostFixer.post);
}

void PrePostHashFixer_DTOR(PrePostHashFixer* const this){

    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this -> prePostDollarFixer.prePostFixer.pre,
            this -> prePostDollarFixer.prePostFixer.post);

    PrePostDollarFixer_DTOR(&this -> prePostDollarFixer);
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

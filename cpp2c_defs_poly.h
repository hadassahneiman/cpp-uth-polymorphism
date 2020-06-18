/*
 Created by hn on 6/18/20.
*/

#ifndef CPP_UTH_POLYMORPHISM_HADASSAHNEIMAN_CPP2C_DEFS_POLY_H
#define CPP_UTH_POLYMORPHISM_HADASSAHNEIMAN_CPP2C_DEFS_POLY_H

#include <stdio.h>

typedef  void (*funPtr)();

/************TextFormatter************/

typedef struct TextFormatter{

    funPtr *_vptr;

}TextFormatter;

funPtr TextFormatterVTable[2];

void TextFormatter_DTOR(TextFormatter* const this);

void TextFormatter_print_kcp(const TextFormatter* const this, const char* text);

/***********DefaultTextFormatter************/

funPtr DefaultTextFormatterVTable[2];

typedef struct DefaultTextFormatter{

    funPtr* _vptr;
    /*const*/ int id;

}DefaultTextFormatter;

typedef struct Ider{

    char padding;

}Ider;

int next_id;

void DefaultTextFormatter_CTOR(DefaultTextFormatter* const this);

void DefaultTextFormatter_CTOR_kDefaultTextFormatter(DefaultTextFormatter* const this, const DefaultTextFormatter*);

DefaultTextFormatter DefaultTextFormatter_As_kDefaultTextFormatter(DefaultTextFormatter* const this, const DefaultTextFormatter*);

void DefaultTextFormatter_DTOR(DefaultTextFormatter* const this);

void DefaultTextFormatter_print_kcp(const DefaultTextFormatter* const this, const char* text);

DefaultTextFormatter* generateFormatterArray();

/**************PrePostFixer*************/

funPtr PrePostFixerVTable[4];

typedef struct PrePostFixer{

    funPtr* _vptr;
    DefaultTextFormatter defaultTextFormatter;
    const char* pre;
    const char* post;

}PrePostFixer;

void PrePostFixer_CTOR_kcpkcp(PrePostFixer* const this, const char* prefix, const char* postfix);

void PrePostFixer_DTOR(PrePostFixer* const this);

void PrePostFixer_print_kcp(const PrePostFixer* const this, const char* text);

void PrePostFixer_print_lc(const PrePostFixer* const this, long num, char symbol);

char PrePostFixer_getDefaultSymbol(const PrePostFixer* const this);

/*****************PrePostDollarFixer**********/

funPtr PrePostDollarFixerVTable[4];

typedef struct PrePostDollarFixer{

    funPtr* _vptr;
    PrePostFixer prePostFixer;

}PrePostDollarFixer;

void PrePostDollarFixer_CTOR_kcpkcp(PrePostDollarFixer* const this, const char* prefix, const char* postfix);

void PrePostDollarFixer_CTOR_kPrePostDollarFixerp(PrePostDollarFixer* const this, const PrePostDollarFixer* other);

void PrePostDollarFixer_DTOR(PrePostDollarFixer* const this);

void PrePostDollarFixer_print_ic(const PrePostDollarFixer* const this, int num, char symbol);

void PrePostDollarFixer_print_lc(const PrePostDollarFixer* const this, long num, char symbol);

void PrePostDollarFixer_print_dc(const PrePostDollarFixer* const this, double num, char symbol);

char PrePostDollarFixer_getDefaultSymbol(const PrePostDollarFixer* const this);

/************PrePostHashFixer************/

funPtr PrePostHashFixerVTable[4];

typedef struct PrePostHashFixer{

    funPtr* _vptr;
    PrePostDollarFixer prePostDollarFixer;
    int precision;

}PrePostHashFixer;

void PrePostHashFixer_CTOR_i(PrePostHashFixer* const this, int prc);

void PrePostHashFixer_DTOR(PrePostHashFixer* const this);

void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol);

void PrePostHashFixer_print_lc(const PrePostHashFixer* const this, long num, char symbol);

char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this);

#endif /*CPP_UTH_POLYMORPHISM_HADASSAHNEIMAN_CPP2C_DEFS_POLY_H*/
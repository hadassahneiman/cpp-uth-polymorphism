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

void TextFormatter_DTOR(TextFormatter* const this);

void TextFormatter_print_kcp(const TextFormatter* const this, const char* text);

/***********DefaultTextFormatter************/

typedef struct DefaultTextFormatter{

    TextFormatter textFormatter;
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

typedef struct PrePostFixer{

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

typedef struct PrePostDollarFixer{

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

typedef struct PrePostHashFixer{

    PrePostDollarFixer prePostDollarFixer;
    int precision;

}PrePostHashFixer;

void PrePostHashFixer_CTOR_i(PrePostHashFixer* const this, int prc);

void PrePostHashFixer_DTOR(PrePostHashFixer* const this);

void PrePostHashFixer_print_ic(const PrePostHashFixer* const this, int num, char symbol);

void PrePostHashFixer_print_lc(const PrePostHashFixer* const this, long num, char symbol);

char PrePostHashFixer_getDefaultSymbol(const PrePostHashFixer* const this);

/************PrePostFloatDollarFixer************/

typedef struct PrePostFloatDollarFixer{

    PrePostDollarFixer prePostDollarFixer;

}PrePostFloatDollarFixer;

void PrePostFloatDollarFixer_CTOR_kcpkcp(PrePostFloatDollarFixer* const this, char* prefix, const char* postfix);

void PrePostFloatDollarFixer_DTOR(PrePostFloatDollarFixer* const this);

void PrePostFloatDollarFixer_print_f(const PrePostFloatDollarFixer* const this, float num);

void PrePostFloatDollarFixer_print_fc(const PrePostFloatDollarFixer* const this, float num, char symbol);

char PrePostFloatDollarFixer_getDefaultSymbol(const PrePostFloatDollarFixer* const this);

/*********PrePostChecker************/

typedef  struct PrePostChecker{

    PrePostFloatDollarFixer prePostFloatDollarFixer;

}PrePostChecker;

void PrePostChecker_CTOR(PrePostChecker* const this);

void PrePostChecker_DTOR(PrePostChecker* const this);

void PrePostChecker_printThisSymbolUsingFunc(const PrePostChecker* const this);

void PrePostChecker_printThisSymbolDirectly(const PrePostChecker* const this);

void PrePostChecker_printDollarSymbolByCastUsingFunc(const PrePostChecker* const this);

void PrePostChecker_printDollarSymbolByScopeUsingFunc(const PrePostChecker* const this);

void PrePostChecker_printDollarSymbolByCastDirectly(const PrePostChecker* const this);

void PrePostChecker_printDollarSymbolByScopeDirectly(const PrePostChecker* const this);

/**************Multiplier***********/

typedef struct Multiplier{

    DefaultTextFormatter DefaultTextFormatter;
    int times;

}Multiplier;

void Multiplier_CTOR_i(Multiplier* const this, int t);

void Multiplier_Dtor(Multiplier* const this);

void Multiplier_print_kcp(const Multiplier* const this, const char*);

#endif /*CPP_UTH_POLYMORPHISM_HADASSAHNEIMAN_CPP2C_DEFS_POLY_H*/
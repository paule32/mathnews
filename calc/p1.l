%{
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <limits.h>
#include <sys/types.h>

#define YYDEBUG 1

#include "p1.tab.h"

enum {
    T_NUMBER = 4,
    T_EQUAL = 5,
};

/**
 * Forward declerations
 **/
void Number ();
void HexaNumber ();

extern int yyerror(const char*);
int line_no = 1;
%}

%option noyywrap

DIGIT       [0-9]
HEXALETTER  [a-fA-F]
HEXANUMBER  [0][x](({DIGIT}|{HEXALETTER})+)
NUM         {DIGIT}+

%x COMMENTS NUM
%x OPADD OPSUB OPDIV OPMOD
%x CREATE_CMD CREATE_FILE CREATE_TABLE
%x NEW_TABLE_STRUCT
%x TABLE_STRUCT_BEG
%x TABLE_STRUCT_END DATA_TYPE PRIMARY_KEY
%x DATA_LENBEG
%x DATA_LENEND PRIKEYS_BEG PRIKEYS_END
%x FILENAME
%x PARAMETER_CMD
%%

\/\/.*            { printf("1c++ comment\n"); BEGIN(INITIAL); }
\/\/.*\n          { printf("2c++ comment\n"); ++line_no; BEGIN(INITIAL); }

\&\&.*            { printf("1dbase comment\n"); BEGIN(INITIAL); }
\*\*.*            { printf("2dbase comment\n"); BEGIN(INITIAL); }

\&\&-*\n          { printf("12dbase comment\n"); ++line_no; BEGIN(INITIAL); }
\*\*.*\n          { printf("22dbase comment\n"); ++line_no; BEGIN(INITIAL); }

\/\*              { printf("c comment on\n"); BEGIN(COMMENTS); }
<COMMENTS>\*\/    {	printf("c comment off\n");BEGIN(INITIAL); }
<COMMENTS>\n      { ++line_no; }
<COMMENTS>.       ;


create                { printf("cmd: create\n"); BEGIN(CREATE_CMD); }
parameter             { printf("ein parameter\n"); BEGIN(INITIAL); }

"^(.*/)?(?:$|(.+?)(?:(\.[^.]*$)|$))?"  { return FILENAME; }

<PARAMETER_CMD>[a-zA-Z_]+[a-zA-Z0-9_]*    {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("para2: -> %s\n",txt);
    free(txt);
    BEGIN(INITIAL);
}
<PARAMETER_CMD>[a-zA-Z_]+[a-zA-Z0-9_]*\,  {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("para1: -> %s\n",txt);
    free(txt);
    BEGIN(PARAMETER_CMD);
}


<CREATE_CMD>"file"      { printf("new: file  \n"); BEGIN(CREATE_FILE); }
<CREATE_CMD>"table"     { printf("new: table \n"); BEGIN(CREATE_TABLE);  }

<CREATE_FILE><FILENAME> {
printf("wwwmos\n");
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("filserl1: -> %s\n",txt);
    free(txt);
    BEGIN(INITIAL);
}
<CREATE_FILE>[a-zA-Z_]+[a-zA-Z0-9_\.]*
printf("ccmos\n");
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("filserl2: -> %s\n",txt);
    free(txt);
    BEGIN(INITIAL);
}

<CREATE_TABLE><FILENAME> {
printf("fos\n");
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("tabsel1: -> %s\n",txt);
    free(txt);
    BEGIN(NEW_TABLE_STRUCT);
}
<CREATE_TABLE>[a-zA-Z_]+[a-zA-Z0-9_\.]* {
printf("mos\n");
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("tabsel2: -> %s\n",txt);
    free(txt);
    BEGIN(NEW_TABLE_STRUCT);
}

<NEW_TABLE_STRUCT>"(" {
    printf("beg\n");
    BEGIN(TABLE_STRUCT_BEG);
}

<TABLE_STRUCT_BEG>[a-zA-Z_]+[a-zA-Z0-9_]*  {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    if (strcmp(txt,"primary") == 0) {
        printf("a key\n");
        BEGIN(PRIMARY_KEY);
    }
    else {
        printf("ident: %s\n",yytext);
        BEGIN(DATA_TYPE);
    }
}
<TABLE_STRUCT_END>")"             { printf("table struct ok.\n"); BEGIN(INITIAL); }

<PRIMARY_KEY>"("   {
    printf(" a key is given...\n");
    BEGIN(PRIKEYS_BEG);
}
<PRIKEYS_BEG>[a-zA-Z_]+[a-zA-Z0-9_]* {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("1prikey: %s\n",txt);
    free(txt);
    BEGIN(PRIKEYS_END);
}
<PRIKEYS_BEG>[a-zA-Z_]+[a-zA-Z0-9_]*\,[ \t]* {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("2prikey: %s\n",txt);
    free(txt);
    BEGIN(PRIKEYS_BEG);
}
<PRIKEYS_END>")"    {
    printf("tabselle has prikeys.\n");
    BEGIN(INITIAL);
}

<DATA_TYPE>("b"|"bool"|"boolean") { printf(" B, \n"); BEGIN(TABLE_STRUCT_END); }
<DATA_TYPE>("l"|"logical")        { printf(" L, \n"); BEGIN(TABLE_STRUCT_END); }
<DATA_TYPE>("n"|"numeric")        { printf(" N, \n"); BEGIN(DATA_LENBEG); }
<DATA_TYPE>("c"|"char")           { printf(" C, \n"); BEGIN(DATA_LENBEG); }
<DATA_TYPE>("d"|"date")           { printf(" D, \n"); BEGIN(TABLE_STRUCT_END); }

<DATA_LENBEG>"("[0-9]+")"   {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("1>numser: %s\n",txt);
    free(txt);
    BEGIN(TABLE_STRUCT_END);
}
<DATA_LENBEG>"("[0-9]+")"[ \t]*\,   {
    char *txt = (char*) malloc(strlen(yytext)+1);
    strcpy(txt,yytext);
    printf("2>numser: %s\n",txt);
    free(txt);
    printf("nax\n");
    BEGIN(TABLE_STRUCT_BEG);
}

HEXANUMBER          { HexaNumber(); return T_NUMBER; }
=                   { return T_EQUAL; }

[ \t]*              { }
[\n]*               { ++line_no; }

<<EOF>>  { return 0; }
.                   ; //{ printf("syntac error."); return 0; }
%%

void Number () {
    yylval.val = atol(yytext);
}

void HexaNumber () {
    yylval.val = (unsigned int) strtol(yytext, (char **)NULL, 16);
}


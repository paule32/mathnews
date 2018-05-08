#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <limits.h>

extern void yyset_in(FILE*);
extern int  yyparse();

int main()
{
    FILE *f = fopen("source.calc","r");
    if (f == nullptr) {
        printf("file:source.calc missing.\n");
        exit(1);
    }

    yyset_in(f);
    yyparse();
    fclose(f);

    return 0;
}


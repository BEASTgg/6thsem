## 1)  Write a YAAC Program to recognize a valid variable, which starts with a letter, followed by any number of letters or digits.
### Codes -

### Lex -

```
%{
#include “y.tab.h”
%}
%%
[a-zA-Z] { return LETTER ;}
[0-9] { return DIGIT ; }
[\n] { return NL ;}
[_] { return UND; }
. { return yytext[0]; }
%%
```

### Yaac -

```
%token DIGIT LETTER NL UND
 %%
 stmt : variable NL { printf(“Valid Identifiers\n”); exit(0);}
 ;
 variable : LETTER alphanumeric
 ;
 alphanumeric: LETTER alphanumeric
 | DIGIT alphanumeric
 | UNDalphanumeric
 | LETTER
 | DIGIT
 | UND
 ;
 %%
int yyerror(char *msg)
 {
 printf(“Invalid Expression\n”);
 exit(0);
 }
 main ()
 {
 printf(“Enter the variable name\n”);
 yyparse();
 }
```

### Output -

```

```

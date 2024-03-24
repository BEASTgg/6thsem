## 1)  Write a YAAC Program to recognize strings ‘aaab’, ‘abbb’, ‘ab’ and ‘a’ using grammar (an b n , n>=0)

### Codes -

### Lex -

```
%{
 #include “y.tab.h”
 %}
 %%
 [aA] { return A; }
 [bB] { return B; }
 \n { return NL ;}
 . { return yytext[0]; }
 %%
```

### Yaac -

```
%token A B NL
 %%
 stmt : s NL { printf(“Valid String\n”); exit(0) ;}
 ;
 s : AsB
 |
 ;
 %%
 int yyerror(char *msg)
 {
 printf(“Invalid String\n”);
 exit(0);
 }
 main ()
 {
printf(“Enter the String\n”);
 yyparse();
 }
```

### Output -

```

```

## 1)  Write a YAAC Program to recognize nested IF control statements and display the levels of nesting

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
 stmt : A A AAAAAAAAsBNL
 {
 Printf(“Valid”); exit(0);
 }
 ;
 s : s A
 |
 ;
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

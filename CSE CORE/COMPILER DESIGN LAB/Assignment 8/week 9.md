## 1)  Write a YAAC Program to check the syntax of a simple expression involving operators +,-, * and /

### Codes -

### Lex -

```
%{
 #include “y.tab.h”
 %}
 %%
 [0-9]+ { return NUMBER; }
 [a-zA-Z][a-zA-Z0-9_]* { return ID; }
 \n { return NL ;}
 . { return yytext[0]; }
 %%
```

### Yaac -

```
%tokenNUMBERIDNL
 %left‘+’‘-‘
 %left‘*’‘/’
 %%
 stmt:expNL{printf(“ValidExpression”);exit(0);}
 ;
 exp:exp‘+’exp
 |exp‘-‘exp
 |exp‘*’exp
 |exp‘/’exp
 |‘(‘exp‘)’
 |ID
 |NUMBER
 ;
 %%
 intyyerror(char*msg)
 {
 printf(“InvalidExpression\n”);
 exit(0);
 }
 main()
{
 printf(“Enter the expression\n”);
 yyparse();
 }
```

### Output -

```

```

## 2)  Write a YAAC Program to evaluate an arithmetic expression involving operating +,-, * and /

### Codes -

### Lex -

```
%{
 #include “y.tab.h”
 extern int yylval;
 %}
 %%
 [0-9]+ { yylval=atoi(yytext); return NUMBER; }
 \n { return NL ;}
 . { return yytext[0]; }
 %%
```

### Yaac -

```
%token NUMBER IDNL
 %left ‘+’ ‘-‘
 %left ‘*’ ‘/’
 %%
 stmt : exp NL { printf(“Value = %d\n”,$1); exit(0);}
 ;
 exp : exp ‘+’ exp { $$=$1+$3; }
 | exp ‘-‘ exp { $$=$1-$3; }
 | exp ‘*’ exp { $$=$1*$3; }
 | exp ‘/’ exp { if($3==0)
 {
 printf(“Cannot divide by 0”);
 exit(0);
 }
 else
 $$=$1/$3;
 }
 | ‘(‘ exp ‘)’ { $$=$2; }
 | ID { $$=$1; }
 | NUMBER{$$=$1; }
 ;
%%
 int yyerror(char *msg)
 {
 printf(“Invalid Expression\n”);
 exit(0);
 }
 main ()
 {
 printf(“Enter the expression\n”);
 yyparse();
 }
```

### Output -

```

```

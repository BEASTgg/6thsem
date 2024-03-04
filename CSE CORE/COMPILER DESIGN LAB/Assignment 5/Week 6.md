## 1) Write a Lex Program to recognize a valid arithmetic expression and identify the identifiers and operators present. Print them separately.

### Codes -

```
%{
#include <stdio.h>
%}

%%
[0-9]+ {
    printf("Number: %s\n", yytext);
}
[a-zA-Z][a-zA-Z0-9]* {
    printf("Identifier: %s\n", yytext);
}
[-+*/=] {
    printf("Operator: %s\n", yytext);
}
[ \t\n] ; // skip whitespace
. {
    printf("Invalid character: %s\n", yytext);
}
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter an arithmetic expression:\n");
    yylex();
    return 0;
}

```

### Output -

```
Enter an arithmetic expression:
5+10
Number: 5
Operator: +
Number: 10
```

## 2) Write a Lex Program to recognize whether a given sentence is simple or compound.

### Codes -

```
%{
#include <stdio.h>
%}

%%
[a-zA-Z0-9 ]+[\.,;?!] {
    printf("It is a Simple Sentence\n");
}
[a-zA-Z0-9 ]+[\.,;?!][a-zA-Z0-9 ]+[\.,;?!] {
    printf("It is a Compound Sentence\n");
}
.|\n ;
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a sentence:\n");
    yylex();
    return 0;
}
```

### Output -

```
Enter a sentence:
I like to swim, and my brother likes to play soccer.
It is a Compound Sentence
```
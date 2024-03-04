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

## 3) Write a lex program to take a user input and valided it , if it is integer calculate factorial or else send some message.

### Code -

```
%{
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int isValid = 1;
%}

DIGIT   [0-9]
INTEGER {DIGIT}+
%%
{INTEGER} {
    if (isValid) {
        int num = atoi(yytext);
        int fact = factorial(num);
        printf("Factorial of %d is %d\n", num, fact);
    }
    else {
        printf("Invalid input\n");
    }
    isValid = 1;
}
. {
    if (isValid) {
        printf("Invalid input\n");
        isValid = 0;
    }
}
%%

int main() {
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
```

### Output -

```
8
Factorial of 8 is 40320

This is a text
Invalid input
```

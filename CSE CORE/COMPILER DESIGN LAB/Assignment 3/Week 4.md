## Week 4 -

### Write a Lex Program to count the number of characters, words, spaces, end of lines in a given input file.

#### Code -

```
%{
#include<stdio.h>
#include<string.h>
int char_count=0,word_count=0,line_count=0;
%}
char [a-zA-Z]
digit [0-9]
CHAR .
word ({char}|{digit})+
WORD [^ \t\n,.:]+
line [\n]
%%
{char} {char_count++;word_count++;}
\. {char_count++;}
{WORD} {word_count++; char_count+= strlen(yytext);}
{line} {line_count++;}
%%
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening file");
        return 1;
    }
    yyin = inputFile;
    yylex();
    printf("\nTotal Character: %d, Total Word: %d, Line Count: %d\n", char_count, word_count, line_count);
    fclose(inputFile);
    return 0;
}
int yywrap() {
    return 1;
}
```

#### Output -

```
a.exe file.txt

Total Character: 33, Total Word: 12, Line Count: 2
```

### Write a Lex Program to count no of: a) +ve and –ve integers b) +ve and –ve fractions.

#### Codes -

```

```

#### Output -

```

```

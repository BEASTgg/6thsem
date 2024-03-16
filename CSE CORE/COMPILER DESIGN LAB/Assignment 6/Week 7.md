## 1) Write a Lex Program to recognize and count the number of identifiers in a given input file.

### Codes -

```
%{
#include <stdio.h>
int identifier_count = 0;
%}

%%
[a-zA-Z][a-zA-Z0-9_]* { identifier_count++; }
.                      { }
%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    yyin = input_file;
    yylex();

    fclose(input_file);

    printf("Number of identifiers: %d\n", identifier_count);
    return 0;
}
int yywrap()
{
	return 1;
}

```

### Output -

```
a.exe a.txt
Number of identifiers: 2
```

## 2) Write a YAAC Program to test the validity of a simple expression involving operators +,-, * and /


### Codes -

```

```

### Output -

```

```
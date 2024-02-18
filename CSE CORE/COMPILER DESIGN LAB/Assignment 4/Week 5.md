## 1) Write a Lex Program to count the no of comment line in a given C program. Also eliminate them and copy that program into separate file.

### Codes -

```
%{
#include<stdio.h>
int m1=0, s1=0;
%}

%%
"/*"[a-zA-Z0-9\n\t ]*"*/" {m1++;}
"//"[a-zA-Z0-9\t ]*"\n" {s1++;}
%%

int main (int argc, char* argv[])
{
	if (argc<2)
	{
		printf("Usage: <a.exe> <sourcefile>\n");
		exit(0);
	}
	yyin = fopen(argv[1],"r");
	yyout = fopen("output.c","w");
	yylex();
	printf("The number of multiline comment = %d\n", m1);
	printf("The number of singleline comment = %d\n", s1);
	fclose(yyin);
	fclose(yyout);
}
int yywrap()
{
	return 1;
}
```

### Output -

```
a.exe a.c
The number of multiline comment = 1
The number of singleline comment = 2
```

## 2) Write a Lex Program to count the no of ‘scanf’ and ‘printf’ statements in a C program. Replace them with ‘readf’ and ‘writef’ statements respectively.

### Codes -

```
%{
#include<stdio.h>
int a=0, b=0;
%}

%%
"scanf" {fprintf(yyout,"readf");b++;}
"printf" {fprintf(yyout,"writef");a++;}
%%

int main (int argc, char* argv[])
{
	if (argc<2)
	{
		printf("Usage: <a.exe> <sourcefile>\n");
		exit(0);
	}
	yyin = fopen(argv[1],"r");
	yyout = fopen("output.c","w");
	yylex();
	printf("Printf statement - %d\n", a);
	printf("Scanf statement - %d\n", b);
	fclose(yyin);
	fclose(yyout);
}
int yywrap()
{
	return 1;
}
```

### Output -

```
a.exe a.c
Printf statement - 1
Scanf statement - 1
```

## 3) Write a program to find the number is prime or not and reverse the number.

### Codes -

```
%{
#include<stdio.h>
int i,j;
%}

%%
[0-9]+ {i=atoi(yytext);
		for(j=2; j<i/2; j++)
		{
			if(i%j==0)
			{
				printf("Not Prime");
				exit(0);
			}
			else
				continue;
		}
		printf("Prime\n");
		while(i)
		{
			printf("%d",i%10);
			i /= 10;
		}
		exit(0);
	}
%%

int main()
{
	printf("Enter the number: \n");
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}
```

### Output -

```
a.exe
Enter the number:
23
Prime
32
```

## 4) Write a program to check if a given number is ODD or EVEN.

### Codes -

```
%{
#include<stdio.h>
int i;
%}

%%
[0-9]+ {i=atoi(yytext);
		if(i%2==0)
			printf("Even");
		else
			printf("Odd");}
%%

int main()
{
	printf("Enter the number: \n");
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}
```

### Output -

```
a.exe
Enter the number:
3
Odd
```
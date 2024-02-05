-- 1) Write a C program to evaluate an arithmetic expression which is given as a string. Consider the input has no parentheses and contains the following operators only:+, -, *, /.

Code -

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 100

double evaluateExpression(char expression[MAX_EXPRESSION_LENGTH]);

int main() {
    char expression[MAX_EXPRESSION_LENGTH];

    printf("Enter an arithmetic expression: ");
    fgets(expression, MAX_EXPRESSION_LENGTH, stdin);

    double result = evaluateExpression(expression);
    printf("Result: %lf\n", result);

    return 0;
}

double evaluateExpression(char expression[MAX_EXPRESSION_LENGTH]) {
    double result = 0.0;
    double number;
    char operatorr;
    int i = 0;
    int operatorCount = 0;

    sscanf(expression, "%lf", &result);

    while (expression[i] != '\0') {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            operatorCount++;
            if(operatorCount >= 2) {
                printf("Error: Invalid expression. Multiple operators in a row.\n");
                exit(EXIT_FAILURE);
            }
            operatorr = expression[i];
            i++;

            sscanf(expression + i, "%lf", &number);

            switch (operatorr) {
                case '+':
                    result += number;
                    break;
                case '-':
                    result -= number;
                    break;
                case '*':
                    result *= number;
                    break;
                case '/':
                    if (number != 0) {
                        result /= number;
                    } else {
                        printf("Error: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                default:
                    break;
            }

            while (isdigit(expression[i]) || expression[i] == '.') {
                i++;
            }
        } else {
            i++;
            operatorCount = 0; // Reset operator count if non-operator character is encountered
        }
    }

    return result;
}

Output -

Enter an arithmetic expression: 5+6
Result 11.000000

-- 2) Write a Lex Program to count the number of vowels and consonants in a given string.

Code -

%{
    int vow_count=0;
    int const_count =0;
%}
 
%%
[aeiouAEIOU] {vow_count++;}
[a-zA-Z] {const_count++;}
%%
int yywrap(){}
int main()
{
    printf("Enter the string of vowels and consonants:");
    yylex();
    printf("Number of vowels are:  %d\n", vow_count);
    printf("Number of consonants are:  %d\n", const_count);
    return 0;
} 

Output -

Enter the string of vowels and consonents : GoodDay

The number of vowels are : 3
The number of consonants are : 4
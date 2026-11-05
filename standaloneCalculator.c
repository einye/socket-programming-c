//STANDALONE CALCULATOR PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int num1, num2;
    char op;
    int consumed;

    /*Prompt user for an arithmetic expression (e.g., "5 + 3").
    Read input and parse into two integers (num1, num2) and an operator (op).*/
    printf("Enter expression (e.g., 5 + 3): ");
    consumed = scanf("%d %c %d", &num1, &op, &num2);

    //If parsing fails (fewer than 3 components), display error: "Invalid input format".
    if (consumed != 3) {
        printf("Invalid input format. Use: <int> <operator> <int>\n");
        return 1;
    }

    // Check if operator is valid
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        printf("Invalid operator. Use one of +, -, *, /\n");
        return 1;
    }

    // Handle division by zero
    if (op == '/' && num2 == 0) {
        printf("%d / 0 = Error: Division by zero\n", num1);
        return 1;
    }

    // Perform the calculation
    int result;
    switch (op) {
        case '+':
            result = num1 + num2;
            printf("%d + %d = %d\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%d - %d = %d\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%d * %d = %d\n", num1, num2, result);
            break;
        case '/':
            result = num1 / num2;
            printf("%d / %d = %d\n", num1, num2, result);
            break;
    }

    return 0;
}

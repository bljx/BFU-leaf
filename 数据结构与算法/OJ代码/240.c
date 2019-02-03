// http://www.bjfuacm.com/problem/240/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 100
#define OVERFLOW (12)
#define DENIED (13)

struct SqStack;
struct SqStack {
    int top;
    int capacity;
    void* array;
};
typedef struct SqStack* Stack;

Stack CreateValStack(Stack S) {
    S = calloc(1, sizeof(struct SqStack));
    S->array = calloc(MAXN, sizeof(double));
    S->top = -1;
    S->capacity = MAXN;
    return S;
}

Stack CreateOpStack(Stack S) {
    S = calloc(1, sizeof(struct SqStack));
    S->array = calloc(MAXN, sizeof(char));
    S->top = -1;
    S->capacity = MAXN;
    return S;
}

int IsFull(Stack S) {
    return S->top + 1 == S->capacity;
}

int IsEmpty(Stack S) {
    return S->top == -1;
}

void PushVal(Stack S, double e) {
    if (IsFull(S)) exit(OVERFLOW);
    *((double *)S->array + (++S->top)) = e;
}

void PushOp(Stack S, char e) {
    if (IsFull(S)) exit(OVERFLOW);
    *((char *)S->array + (++S->top)) = e;
}

char TopOp(Stack S) {
    if (!IsEmpty(S)) return *((char *)S->array + S->top);
    exit(DENIED);
}

double TopVal(Stack S) {
    if (!IsEmpty(S)) return *((double *)S->array + S->top);
    exit(DENIED);
}

char TopAndPopOp(Stack S) {
    if (!IsEmpty(S)) return *((char *)S->array + S->top--);
    exit(DENIED);
}

double TopAndPopVal(Stack S) {
    if (!IsEmpty(S)) return *((double *)S->array + S->top--);
    exit(DENIED);
}

void Pop(Stack S) {
    if (IsEmpty(S)) exit(DENIED);
    S->top -= 1;
}

void EmptyStack(Stack S) {
    S->top = -1;
}

double getvalue(char** in) {
    return strtod(*in, &(*in));
}

char precede(char in_stack, char out) {
    if (in_stack == '(' && out == ')') {
        /************************
         * 1. ENCLOSE "()" PAIR *
         * 2. THE END OF STR    *
         ************************/
        return '=';
    } else if (in_stack == '(' || in_stack == '#' || out == '(' ||
               /************************************
                * 3. ONLY "(" THEN EXPRESSION      *
                * 4. AT THE BEGIN OF STR           *
                * 5. THEN TO PUSH "(" THEN TO (1)  *
                * 6. REAL PRECEDE                  *
                ************************************/
               ((in_stack == '+' || in_stack == '-') &&
                (out == '*' || out == '/'))) {
        return '<';
        // continue PUSH value or operator
    } else {
        return '>';
        // CALCULATE value
        // out == ')' will go to (1) until str in () is calculated
    }
}

double calculate(char op, double b, double a) {
    /*******************************
     * THERE IS A LARGE TRAP HERE: *
     *******************************/
    // e.g function(f1(), f2()) {}
    // gcc calc param f2() then f1()
    // while others call f1() then to f2()
    // thus this order impacts on stack pop order

    switch (op) {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/': return b / a;
    }
}

int main() {
    Stack V; // value stack 1, 2, 3...
    Stack Op; // operator stack +, -, *, /
    V = CreateValStack(V);
    Op = CreateOpStack(Op);
    char* in;
    char* out;
    while (1) {
        in = (char *)calloc(MAXN, sizeof(char));
        out = in;
        scanf("%s", in);
        if (in[0] == '=' && in[1] == '\0') break;
        PushOp(Op, '#');
        while (1) {
            if (*in == '=') {
                while (TopOp(Op) != '#') {
                    PushVal(V, calculate(TopAndPopOp(Op),
                                         TopAndPopVal(V), TopAndPopVal(V)));
                }
                break;
            }
            if (isdigit(*in)) {
                PushVal(V, getvalue(&in));
            } else {
                switch (precede(TopOp(Op), *in)) {
                    case '<':
                        // continue push
                        PushOp(Op, *in);
                        in += 1;
                        break;
                    case '>':
                        // do calculate before (*in)
                        PushVal(V, calculate(TopAndPopOp(Op),
                                             TopAndPopVal(V), TopAndPopVal(V)));
                        break;
                    case '=':
                        // in_stack == '(' && out == ')'
                        Pop(Op);
                        in += 1;
                    default: break;
                }
            }
        }
        printf("%.2lf\n", TopVal(V));
        EmptyStack(V);
        EmptyStack(Op);
        free(out);
    }
}



/******************************************************************************************************************
 * HTTPS://STACKOVERFLOW.COM/QUESTIONS/13421424/HOW-TO-EVALUATE-AN-INFIX-EXPRESSION-IN-JUST-ONE-SCAN-USING-STACKS *
 *                              HTTPS://WWW.GEEKSFORGEEKS.ORG/EXPRESSION-EVALUATION/                              *
 *                                             STACK IMPLEMENTATION:                                              *
 *                                                     ARRAY                                                      *
 *                    HTTPS://WWW.GEEKSFORGEEKS.ORG/STACK-DATA-STRUCTURE-INTRODUCTION-PROGRAM/                    *
 *                                            REGULAR EXPRESSION IN C:                                            *
 *                 HTTPS://STACKOVERFLOW.COM/QUESTIONS/1085083/REGULAR-EXPRESSIONS-IN-C-EXAMPLES                  *
 ******************************************************************************************************************/

/** Elegant solution:
 * use regular pattern for matching float in string
 * let atof() in stdlib.h convert string to float ( or not... F****** INPUT format
 * use union to fit different type in struct
 * create multiple functions with multiple return type
 * Tricky solution in Python 2.7 at the end of file ( function: eval()
 */

/*
 * Tricky Solve Python 2.7:
 * while True:
 *     s = str(raw_input())
 *     if (s == '='):
 *         break
 *     print ("%.2f" % eval(s[:-1]))
 */

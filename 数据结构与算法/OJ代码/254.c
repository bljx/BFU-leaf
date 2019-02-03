// http://www.bjfuacm.com/problem/254/

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
    S->array = calloc(MAXN, sizeof(int));
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

void PushVal(Stack S, int e) {
    if (IsFull(S)) exit(OVERFLOW);
    *((int *)S->array + (++S->top)) = e;
}

void PushOp(Stack S, char e) {
    if (IsFull(S)) exit(OVERFLOW);
    *((char *)S->array + (++S->top)) = e;
}

char TopOp(Stack S) {
    if (!IsEmpty(S)) return *((char *)S->array + S->top);
    exit(DENIED);
}

int TopVal(Stack S) {
    if (!IsEmpty(S)) return *((int *)S->array + S->top);
    exit(DENIED);
}

char TopAndPopOp(Stack S) {
    if (!IsEmpty(S)) return *((char *)S->array + S->top--);
    exit(DENIED);
}

int TopAndPopVal(Stack S) {
    if (!IsEmpty(S)) return *((int *)S->array + S->top--);
    exit(DENIED);
}

void Pop(Stack S) {
    if (IsEmpty(S)) exit(DENIED);
    S->top -= 1;
}

void EmptyStack(Stack S) {
    S->top = -1;
}

int getvalue(char** in) {
    return strtod(*in, &(*in));
}

char precede(char in_stack, char out) {
    if (in_stack == '(' && out == ')') {
        return '=';
    } else if (in_stack == '(' || in_stack == '#' || out == '(' ||
               ((in_stack == '+' || in_stack == '-') &&
                (out == '*' || out == '/'))) {
        return '<';
    } else {
        return '>';
    }
}

int calculate(char op, int b, int a) {
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
    /*******************************************
     * INFIX TO SUFFIX DO NOT NEED VALUE STACK *
     *******************************************/
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
                    // PushVal(V, calculate(TopAndPopOp(Op),
                    //                      TopAndPopVal(V), TopAndPopVal(V)));
                    printf("%c", TopAndPopOp(Op));
                }
                break;
            }
            if (isdigit(*in)) {
                printf("%d", getvalue(&in));
            } else {
                switch (precede(TopOp(Op), *in)) {
                    case '<':
                        // continue push
                        PushOp(Op, *in);
                        in += 1;
                        break;
                    case '>':
                        // do calculate before (*in)
                        // PushVal(V, calculate(TopAndPopOp(Op),
                        //                      TopAndPopVal(V), TopAndPopVal(V)));
                        printf("%c", TopAndPopOp(Op));
                        break;
                    case '=':
                        // in_stack == '(' && out == ')'
                        Pop(Op);
                        in += 1;
                    default: break;
                }
            }
        }
        printf("\n");
        EmptyStack(V);
        EmptyStack(Op);
        free(out);
    }
}


// http://www.bjfuacm.com/problem/244/

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

double calculate(char op, double b, double a) {
    switch (op) {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/': return b / a;
    }
}

int main() {
    Stack V;
    Stack Op;
    V = CreateValStack(V);
    Op = CreateOpStack(Op);
    /****************************************************
     * CALCULATE SUFFIX EXPRESSION DO NOT NEED OP STACK *
     ****************************************************/
    char* in;
    char* out;
    size_t len = 80;
    while (1) {
        in = (char *)calloc(MAXN, sizeof(char));
        out = in;
        getline(&in, &len, stdin);
        if (in[0] == '=') break;
        /**********************************
         * USE GETLINE HERE in[1] != '\0' *
         **********************************/
        while (1) {
            if (*in == '=') break;
            if (isdigit(*in)) {
                PushVal(V, getvalue(&in));
            } else if (*in == ' ') {
                in++;
                continue;
            } else {
                PushVal(V, calculate(*in,
                                     TopAndPopVal(V), TopAndPopVal(V)));
                in++;
            }
        }
        printf("%.2lf\n", TopVal(V));
        EmptyStack(V);
        free(out);
    }
}

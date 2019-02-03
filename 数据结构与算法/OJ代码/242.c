// http://www.bjfuacm.com/problem/242/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType char
#define OVERFLOW (12)
#define DENIED (13)
#define EmptyTOS (-1)

struct StackRecord;
typedef struct StackRecord* Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndTop(Stack S);

struct StackRecord {
    int Capacity;
    int TopOfStack;
    ElementType* Array;
};

Stack
CreateStack(int MaxElements) {
    Stack S;
    S = malloc(sizeof(struct StackRecord));
    if (S == NULL) exit(OVERFLOW);
    S->Array = malloc(sizeof(ElementType) * MaxElements);
    if (S->Array == NULL) exit(OVERFLOW);
    S->Capacity = MaxElements;
    MakeEmpty(S);
    return S;
}

void
DisposeStack(Stack S) {
    if (S != NULL) {
        free(S->Array);
        free(S);
    }
}

int
IsEmpty(Stack S) {
    return S->TopOfStack == EmptyTOS;
}

int
IsFull(Stack S) {
    return S->TopOfStack == S->Capacity - 1;
}

void
MakeEmpty(Stack S) {
    S->TopOfStack = EmptyTOS;
}

void
Push(ElementType X, Stack S) {
    if (IsFull(S)) exit(OVERFLOW);
    S->Array[++S->TopOfStack] = X;
}

ElementType
Top(Stack S) {
    if (!IsEmpty(S)) return S->Array[S->TopOfStack];
    exit(DENIED);
}

void
Pop(Stack S) {
    if (!IsEmpty(S)) {
        S->TopOfStack -= 1;
    } else {
        exit(DENIED);
    }
}

ElementType
TopAndTop(Stack S) {
    if (!IsEmpty(S)) {
        return S->Array[S->TopOfStack--];
    } else {
        exit(DENIED);
    }
}

int IsPalindrome(Stack S, char* in) {
    int i;
    for (i = 0; i < strlen(in) / 2; i++) Push(in[i], S);
    if (strlen(in) % 2 == 1) i += 1;
    while (!IsEmpty(S)) {
        if (Top(S) != in[i]) return 0;
        Pop(S);
        i += 1;
    }
    return 1;
}


int main() {
    Stack S;
    S = CreateStack(50);

    while (1) {
        char *in = (char *)calloc(100, sizeof(char));
        scanf("%s", in);
        if (in[0] == '0' && in[1] == '\0') break;
        int ans = IsPalindrome(S, in);
        printf("%s\n", (ans == 1) ? "YES" : "NO");
        free(in);
        MakeEmpty(S); // in case stack no empty
    }
    DisposeStack(S);
}

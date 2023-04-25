#pragma once
#include "Header.h"
#include "Goods_Struct.h"
struct Stack {
    DS_s_VT**a;
    int top ;
    int capacity;
    Stack(int size) {       
        capacity = size;
        a = new DS_s_VT *[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] a;
    }
};
bool isEmpty(Stack& s) {
    return s.top == -1;
}
void push(Stack &s, DS_s_VT* x) {
    if (s.capacity-1==s.top) {
        cout << " Stack is overflow";
    }
    else {
        s.a[++s.top] = x;
    }
}
DS_s_VT* pop(Stack& s) {
    if (s.top == -1) {
        cout << " Stack is empty";
        return NULL;
    }   
    return s.a[s.top--];
    
}
struct StackVT {
    DS_VatTu** a;
    int top;
    int capacity;
    StackVT(int size) {
        capacity = size;
        a = new DS_VatTu * [capacity];
        top = -1;
    }

    ~StackVT() {

        delete[] a;
    }
};
bool isEmpty(StackVT& s) {
    return s.top == -1;
}
void push(StackVT& s, DS_VatTu* x) {
    if (s.capacity - 1 == s.top) {
        cout << " Stack is overflow";
    }
    else {
        s.a[++s.top] = x;
    }
}
DS_VatTu* pop(StackVT& s) {
    if (s.top == -1) {
        cout << " Stack is empty";
        return NULL;
    }
    return s.a[s.top--];

}

